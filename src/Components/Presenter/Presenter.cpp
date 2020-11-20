#include "Presenter.hpp"
#include "../TetrisEngine/Field.hpp"
#include <iostream>
#include "../../Utils/Utils.hpp"

constexpr int FIELD_WIDTH = 18;
constexpr int FIELD_HEIGHT = 26;
constexpr int CELL_SIZE = 15;
constexpr int NEXT_SHAPE_CELL_SIZE = 7;
constexpr int NEXT_SHAPE_SIZE = NEXT_SHAPE_CELL_SIZE * CELL_SIZE;

Presenter::Presenter(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : Window(renderer, x, y, w, h), counter(0), fieldTexture(nullptr) {
  fieldBox = {48, 72, FIELD_WIDTH * CELL_SIZE, FIELD_HEIGHT * CELL_SIZE};

  nshape = new NextShape(
    renderer,
    box.w - 48 - NEXT_SHAPE_SIZE,
    72,
    NEXT_SHAPE_SIZE,
    NEXT_SHAPE_SIZE
  );

  tetris = new TetrisEngine(FIELD_WIDTH, FIELD_HEIGHT, [&]{
    fillFieldTexture();
    fillShapeTexture();
  });
  fillFieldTexture();
  fillShapeTexture();
}

Presenter::~Presenter() {
  delete backBtn;
  delete tetris;
  SDL_DestroyTexture(fieldTexture);
  delete nshape;
}

void Presenter::render() {
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  SDL_Rect curBox = {fieldBox.x - 1, fieldBox.y - 1, fieldBox.w + 2, fieldBox.h + 2};
  SDL_RenderDrawRect(renderer, &curBox);

  SDL_RenderCopy(renderer, fieldTexture, NULL, &fieldBox);
  curBox = {0, 0, CELL_SIZE, CELL_SIZE};
  shape s = tetris->getCur();
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      if (s.matrix[i][j]) {
        curBox.x = fieldBox.x + (s.x + j) * CELL_SIZE;
        curBox.y = fieldBox.y + (s.y + i) * CELL_SIZE;
        SDL_SetRenderDrawColor(
          renderer,
          colors[s.color].r,
          colors[s.color].g,
          colors[s.color].b, 255
        );
        SDL_RenderFillRect(renderer, &curBox);
        SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
        SDL_RenderDrawRect(renderer, &curBox);
      }
    }
  }
}

void Presenter::update() {
  counter++;
  if (!(counter % 12)) tetris->update();
  // if (!(counter % 24)) tetris->update();

  backBtn->update();
  nshape->render();
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
  case SDLK_ESCAPE:
    tetris->togglePause();
    break;
  }
}

void Presenter::reload() {
  delete tetris;
  tetris = new TetrisEngine(FIELD_WIDTH, FIELD_HEIGHT, [&]{
    fillFieldTexture();
    fillShapeTexture();
  });
  
  fillFieldTexture();
  fillShapeTexture();
}

void Presenter::fillFieldTexture() {
  if (fieldTexture != nullptr) SDL_DestroyTexture(fieldTexture);
  SDL_Surface * surf = SDL_CreateRGBSurface(0, fieldBox.w, fieldBox.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0x212121);

  uchar curCell;
  SDL_Rect curBox = {0, 0, CELL_SIZE, CELL_SIZE};
  Field * field = tetris->getField();
  for (int i = 0; i < field->getY(); i++) {
    for (int j = 0; j < field->getX(); j++) {
      curCell = field->matrix[field->getX() * i + j];
      if (curCell) {
        curBox.x = j * CELL_SIZE;
        curBox.y = i * CELL_SIZE;
        SDL_FillRect(surf, &curBox, 0x212121);
        curBox = {curBox.x + 1, curBox.y + 1, CELL_SIZE - 2, CELL_SIZE - 2};
        SDL_FillRect(surf, &curBox, createRGB(colors[curCell - 1]));
        curBox.w = curBox.h = CELL_SIZE;
      }
    }
  }

  fieldTexture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
}

void Presenter::fillShapeTexture() {
  SDL_Rect box = nshape->getBox();
  SDL_Surface * surf = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0x212121);

  SDL_Rect curBox = {0, 0, CELL_SIZE, CELL_SIZE};
  shape s = tetris->getNext();
  int xsize, ysize, xdisplace, ydisplace;
  xsize = tetris->realSizeX(s, &xdisplace);
  ysize = tetris->realSizeY(s, &ydisplace);
  xdisplace = (NEXT_SHAPE_CELL_SIZE - xsize) / 2;
  ydisplace = (NEXT_SHAPE_CELL_SIZE - ysize) / 2;
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      if (s.matrix[i][j]) {
        curBox.x = (xdisplace + j) * CELL_SIZE;
        curBox.y = (ydisplace + i) * CELL_SIZE;
        SDL_FillRect(surf, &curBox, 0x212121);
        curBox = {curBox.x + 1, curBox.y + 1, CELL_SIZE - 2, CELL_SIZE - 2};
        SDL_FillRect(surf, &curBox, createRGB(colors[s.color]));
        curBox.w = curBox.h = CELL_SIZE;
      }
    }
  }

  SDL_Texture * shapeTexture = SDL_CreateTextureFromSurface(renderer, surf);
  nshape->update(shapeTexture);
  SDL_FreeSurface(surf);
}