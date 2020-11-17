#include "Presenter.hpp"
#include "../TetrisEngine/Field.hpp"
#include <iostream>

constexpr int FIELD_WIDTH = 20;
constexpr int FIELD_HEIGHT = 30;
constexpr int CELL_SIZE = 10;

Presenter::Presenter(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : Window(renderer, x, y, w, h) {
  tetris = new TetrisEngine(FIELD_WIDTH, FIELD_HEIGHT);

  fieldBox = {100, 100, FIELD_WIDTH * CELL_SIZE, FIELD_HEIGHT * CELL_SIZE};
}

Presenter::~Presenter() {
  delete backBtn;
  delete tetris;
}

void Presenter::render() {
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  SDL_RenderDrawRect(renderer, &fieldBox);

  // Field field = tetris->getField();
  // for (int i = 0; i < field.getX(); i++) {
  //   for (int j = 0; j < field.getY(); j++) {

  //   }
  // }
  shape s = tetris->getCur();
  SDL_Rect curBox = {0, 0, CELL_SIZE, CELL_SIZE};
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      if (s.matrix[i][j]) {
        curBox.x = fieldBox.x + (s.x + i) * CELL_SIZE;
        curBox.y = fieldBox.y + (s.y + j) * CELL_SIZE;
        SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
        SDL_RenderFillRect(renderer, &curBox);
        SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
        SDL_RenderDrawRect(renderer, &curBox);
      }
    }
  }
}

void Presenter::update() {
  tetris->update();
  backBtn->update();

  render();
}

void Presenter::click(int x, int y) {

  backBtn->click(x, y);
}

void Presenter::hover(int x, int y) {

  backBtn->hover(x,y);
}

void Presenter::keyEvent(SDL_Event& e) {
  switch (e.key.keysym.sym) {
  case SDLK_LEFT:
    tetris->displaceCur(-1);
    break;
  case SDLK_RIGHT:
    tetris->displaceCur(1);
    break;
  case SDLK_SPACE:
    tetris->rotate();
    break;
  }
}