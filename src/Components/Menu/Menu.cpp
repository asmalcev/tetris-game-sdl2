#include "Menu.hpp"
#include "../../Utils/Utils.hpp"

Menu::Menu(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : renderer(renderer),
    box({x, y, w, h})
{
  int tw, th;
  SDL_Surface * textSurf = renderText("MENU", {245, 245, 245}, 32, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 30, tw, th};
  menuTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_FreeSurface(textSurf);
}

Menu::~Menu() {
  SDL_DestroyTexture(menuTexture);
  for (auto btn : btns) {
    delete btn;
  }
}

void Menu::render() {
  SDL_RenderCopy(renderer, menuTexture, NULL, &textPos);
}

void Menu::update() {
  render();

  for (auto btn : btns) {
    btn->update();
  }
}

void Menu::click(int x, int y) {
  for (auto btn : btns) {
    if (btn->click(x, y)) break;
  }
}

void Menu::hover(int x, int y) {
  for (auto btn : btns) {
    if (btn->hover(x, y)) break;
  }
}