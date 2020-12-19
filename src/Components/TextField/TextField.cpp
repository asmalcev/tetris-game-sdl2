#include "TextField.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>

TextField::TextField(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h,
  std::string placeholderText,
  std::function<void(std::string&, SDL_Event&, int&)> funcPtr
) : renderer(renderer),
    box({x, y, w, h}),
    tfs(TextFieldState::UNFOCUSED),
    m_funcPtr(funcPtr),
    timer(0),
    letterOffset(0)
{
  SDL_Surface * textSurf, * surf = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0xF5F5F5);
  SDL_Rect dst = {1, 1, box.w - 2, box.h - 2};
  SDL_FillRect(surf, &dst, 0x212121);
  int tw, th;
  textSurf = renderText(
    placeholderText,
    {158, 158, 158},
    16, "docs/RobotoMono-Regular.ttf",
    &tw, &th
  );
  placeholderWidth = tw;
  textBox = {4, (box.h - th) / 2, placeholderWidth, th};

  placeholderTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  fieldTexture       = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(textSurf);
  SDL_FreeSurface(surf);
}

TextField::~TextField() {
  SDL_DestroyTexture(placeholderTexture);
  SDL_DestroyTexture(fieldTexture);
}

void TextField::render() {
  if (tfs == TextFieldState::FOCUSED) {
    SDL_Rect outlineBox = { box.x - 2, box.y - 2, box.w + 4, box.h + 4 };
    SDL_SetRenderDrawColor(renderer, 229, 57, 53, 255);
    SDL_RenderDrawRect(renderer, &outlineBox);
  }

  SDL_Rect displacedBox = { box.x, box.y, box.w, box.h };
  SDL_RenderCopy(renderer, fieldTexture, NULL, &displacedBox);

  if (!value.empty()) {
    SDL_Surface * textSurf;
    SDL_Texture * textTexture;
    int tw, th;
    textSurf = renderText(
      value.c_str(),
      {245, 245, 245},
      16, "docs/RobotoMono-Regular.ttf",
      &tw, &th
    );

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
    SDL_FreeSurface(textSurf);

    textBox.w = tw;
    SDL_RenderCopy(renderer, textTexture, NULL, &textBox);

    SDL_DestroyTexture(textTexture);
  } else {
    textBox.w = placeholderWidth;
    SDL_RenderCopy(renderer, placeholderTexture, NULL, &textBox);
  }

  if (tfs == TextFieldState::FOCUSED) {
    int tw, th;
    textSize(
      value.substr(0, value.size() - 1 + letterOffset).c_str(),
      16, "docs/RobotoMono-Regular.ttf",
      &tw, &th
    );
    SDL_Rect line = { textBox.x + 4 + tw, textBox.y - 1, 1, th + 1};
    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
    SDL_RenderDrawRect(renderer, &line);
  }
}

void TextField::update() {
  render();
}

bool TextField::hover(int x, int y) {
  if (
    x >= box.x && x <= box.x + box.w &&
    y >= box.y && y <= box.y + box.h
  ) {
    return true;
  }
  return false;
}

bool TextField::click(int x, int y) {
  if (
    x >= box.x && x <= box.x + box.w &&
    y >= box.y && y <= box.y + box.h
  ) {
    tfs = TextFieldState::FOCUSED;
    return true;
  }
  tfs = TextFieldState::UNFOCUSED;
  return false;
}

void TextField::keyEvent(SDL_Event& e) {
  if (tfs == TextFieldState::FOCUSED) {
    m_funcPtr(value, e, letterOffset);
  }
}

void TextField::displaceBox(int x, int y) {
  box.x = x;
  box.y = y;
  textBox.x = x + 4;
  textBox.y = y + (box.h - textBox.h) / 2;
}

std::string TextField::getValue() {
  return value;
}