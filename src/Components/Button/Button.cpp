#include "Button.hpp"
#include "../../Utils/Utils.hpp"

Button::Button(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h,
  std::string text,
  std::function<void()> funcPtr
) : renderer(renderer),
    box({x, y, w, h}),
    transitionTimer(0),
    bs(ButtonState::NORMAL),
    dTimer(16. / 200 * 100),
    m_funcPtr(funcPtr),
    offset(4)
{
  SDL_Surface * textSurf, * surf = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0xF5F5F5);
  SDL_Rect dst = {1, 1, box.w - 2, box.h - 2};
  SDL_FillRect(surf, &dst, 0x212121);
  int tw, th;
  textSurf = renderText(text, {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  dst.x = (box.w - tw) / 2;
  dst.y = (box.h - th) / 2;
  SDL_BlitSurface( textSurf, NULL, surf, &dst);

  btnTexture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(textSurf);
  SDL_FreeSurface(surf);
}

Button::~Button() {
  SDL_DestroyTexture(btnTexture);
}

SDL_Rect Button::getRect(void) {
  return box;
}

void Button::render() {
  SDL_SetRenderDrawColor( renderer, 245, 245, 245, 255 );
  SDL_RenderFillRect( renderer, &box );

  offset = 4 + 6.0 / 100 * transitionTimer;
  SDL_Rect displacedBox = { box.x - offset, box.y - offset, box.w, box.h };
  SDL_RenderCopy(renderer, btnTexture, NULL, &displacedBox);
}

void Button::update() {
  if (bs != ButtonState::NORMAL && transitionTimer < 100) transitionTimer += dTimer;
  if (bs == ButtonState::NORMAL && transitionTimer > 0) transitionTimer -= dTimer;

  render();
}

bool Button::hover(int x, int y) {
  if (
    (x >= box.x && x <= box.x + box.w &&
     y >= box.y && y <= box.y + box.h) ||
    (x >= box.x - offset && x <= box.x + box.w - offset &&
     y >= box.y - offset && y <= box.y + box.h - offset)
  ) {
    bs = ButtonState::HOVERED;
    return true;
  }
  bs = ButtonState::NORMAL;
  return false;
}

bool Button::click(int x, int y) {
  if (
    (x >= box.x && x <= box.x + box.w &&
     y >= box.y && y <= box.y + box.h) ||
    (x >= box.x - offset && x <= box.x + box.w - offset &&
     y >= box.y - offset && y <= box.y + box.h - offset)
  ) {
    if (m_funcPtr != nullptr) m_funcPtr();
    bs = ButtonState::CLICKED;
    return true;
  }
  bs = ButtonState::NORMAL;
  return false;
}