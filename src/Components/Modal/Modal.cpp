#include "Modal.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include "../../include.hpp"

Modal::Modal(
    SDL_Renderer * renderer,
    int w,
    int h,
    std::string msg,
    Button    * btn,
    TextField * textField
  ) : Window(renderer, 0, 0, w, h),
      backBtn(btn),
      textField(textField)
{
  box.x = (WINDOW_WIDTH - box.w) / 2;
  box.y = (WINDOW_HEIGHT - box.h) / 2;
  SDL_Surface * textSurf, * surf
    = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0xF5F5F5);
  SDL_Rect dst = {1, 1, box.w - 2, box.h - 2};
  SDL_FillRect(surf, &dst, 0x212121);
  int tw, th;
  textSurf = renderText(
    msg,
    {245, 245, 245},
    16, "docs/RobotoMono-Regular.ttf",
    &tw, &th
  );
  dst.x = (box.w - tw) / 2;
  dst.y = 36;
  SDL_BlitSurface(textSurf, NULL, surf, &dst);

  modalTexture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(textSurf);
  SDL_FreeSurface(surf);

  backBtn->displaceBox(box.x + box.w - 86, box.y + box.h - 72);
  textField->displaceBox(box.x + 36, box.y + box.h - 72);
}

Modal::~Modal() {
  delete backBtn;
  delete textField;
  SDL_DestroyTexture(modalTexture);
};

void Modal::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
  SDL_RenderFillRect(renderer, NULL);

  SDL_RenderCopy(renderer, modalTexture, NULL, &box);
}

void Modal::update() {
  render();
  backBtn->update();
  textField->update();
}

void Modal::click(int x, int y) {
  if (backBtn->click(x, y)) return;
  textField->click(x, y);
}

void Modal::hover(int x, int y) {
  if (backBtn->hover(x, y)) return;
}

void Modal::keyEvent(SDL_Event& e) {
  textField->keyEvent(e);
}