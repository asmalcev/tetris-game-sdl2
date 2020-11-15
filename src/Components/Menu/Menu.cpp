#include "Menu.hpp"
#include "../../Utils/Utils.hpp"
#include <cmath>
#include <time.h>

Menu::Menu(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : Window(renderer, x, y, w, h)
{
  int tw, th;
  SDL_Surface * textSurf = renderText("MENU", {245, 245, 245}, 48, "docs/RobotoMono-Bold.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 30, tw, th};
  menuTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_FreeSurface(textSurf);

  srand(time(0));
  for (int i = 0; i < 20; i++) {
    points.push_back(
      new FallingPoint(renderer, rand() % box.w, -(rand() % box.h), 2)
    );
  }
}

Menu::~Menu() {
  SDL_DestroyTexture(menuTexture);
  for (auto btn : btns) {
    delete btn;
  }
  for (auto point : points) {
    delete point;
  }
}

void Menu::render() {
  SDL_RenderCopy(renderer, menuTexture, NULL, &textPos);
}

void Menu::update() {
  render();

  for (auto point : points) {
    point->update();
  }

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