#include "Presenter.hpp"
#include <iostream>
#include "../TetrisEngine/Field.hpp"
#include "../../Utils/Utils.hpp"

constexpr int FIELD_WIDTH = 13;
constexpr int FIELD_HEIGHT = 26;
constexpr int CELL_SIZE = 15;
constexpr int HORIZONTAL_PADDING = 128;
constexpr int NEXT_SHAPE_CELL_SIZE = 7;
constexpr int NEXT_SHAPE_SIZE = NEXT_SHAPE_CELL_SIZE * CELL_SIZE;
constexpr int COUNTER_HIEGHT = 54;

Presenter::Presenter(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : Window(renderer, x, y, w, h),
    timer(0),
    fieldTexture(nullptr),
    isModalOpened(false),
    isDownBtnPressed(false) {
  fieldBox = {
    HORIZONTAL_PADDING,
    72,
    FIELD_WIDTH * CELL_SIZE,
    FIELD_HEIGHT * CELL_SIZE
  };

  nshape = new VisibleElement(
    renderer,
    box.w - HORIZONTAL_PADDING - NEXT_SHAPE_SIZE,
    72,
    NEXT_SHAPE_SIZE,
    NEXT_SHAPE_SIZE
  );
  counter = new VisibleElement(
    renderer,
    box.w - HORIZONTAL_PADDING - NEXT_SHAPE_SIZE,
    84 + NEXT_SHAPE_SIZE,
    NEXT_SHAPE_SIZE,
    COUNTER_HIEGHT
  );

  tetris = new TetrisEngine(FIELD_WIDTH, FIELD_HEIGHT, [&]{
    fillFieldTexture();
    fillShapeTexture();
    fillCounterTexture();
  }, [&]{
    isModalOpened = true;
    modalWindow->setLastScoreResult(tetris->getScore());
  });
  fillFieldTexture();
  fillShapeTexture();
  fillCounterTexture();
}

Presenter::~Presenter() {
  delete backBtn;
  delete modalWindow;
  delete tetris;
  SDL_DestroyTexture(fieldTexture);
  delete nshape;
  delete counter;
}

void Presenter::render() {
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  SDL_Rect curBox = {fieldBox.x - 1, fieldBox.y - 1, fieldBox.w + 2, fieldBox.h + 2};
  SDL_RenderDrawRect(renderer, &curBox);

  SDL_RenderCopy(renderer, fieldTexture, NULL, &fieldBox);
  curBox = {0, 0, CELL_SIZE, CELL_SIZE};
  shape s = tetris->getCur();
  SDL_Rect verticalLine = {0, fieldBox.y, CELL_SIZE, fieldBox.h};
  bool filledLine[s.size] = {false};
  const int offsetY =
    CELL_SIZE - (int) ((timer % tetris->stepDelay) * 1.0 / tetris->stepDelay * CELL_SIZE);

  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      if (s.matrix[i][j]) {
        curBox.x = fieldBox.x + (s.x + j) * CELL_SIZE;
        curBox.y = fieldBox.y + (s.y + i) * CELL_SIZE - offsetY;

        if (!filledLine[j]) {
          filledLine[j] = true;
          verticalLine.x = curBox.x;
          SDL_SetRenderDrawColor(renderer, 245, 245, 245, 16);
          SDL_RenderFillRect(renderer, &verticalLine);
        }
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
  backBtn->update();
  nshape->render();
  counter->render();
  render();
  
  if (isModalOpened && modalWindow) {
    modalWindow->update();
  } else {
    timer++;
    if (!(timer % tetris->stepDelay)) tetris->update();
  }
}

void Presenter::click(int x, int y) {
  if (isModalOpened && modalWindow) {
    modalWindow->click(x, y);
  } else {
    backBtn->click(x, y);
  }
}

void Presenter::hover(int x, int y) {
  if (isModalOpened && modalWindow) {
    modalWindow->hover(x, y);
  } else {
    backBtn->hover(x,y);
  }
}

void Presenter::keyEvent(SDL_Event& e) {
  if (e.type == SDL_KEYUP) {
    if (isModalOpened && modalWindow) {
      modalWindow->keyEvent(e);
    } else {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT: {
          tetris->displaceCur(-1);
          break;
        }
        case SDLK_RIGHT: {
          tetris->displaceCur(1);
          break;
        }
        case SDLK_DOWN: {
          if (
            e.key.keysym.mod == KMOD_LCTRL ||
            e.key.keysym.mod == KMOD_RCTRL
          ) {
            tetris->slideDown();
          } else {
            if (isDownBtnPressed) {
              tetris->toggleSpeedUp();
              isDownBtnPressed = false;
            }
          }
          break;
        }
        case SDLK_SPACE: {
          tetris->rotate();
          break;
        }
        case SDLK_ESCAPE: {
          tetris->togglePause();
          break;
        }
      }
    }
  } else if (e.type == SDL_KEYDOWN) {
    if (
      e.key.keysym.sym == SDLK_DOWN &&
      e.key.keysym.mod == KMOD_NONE &&
      !isDownBtnPressed
    ) {
      tetris->toggleSpeedUp();
      isDownBtnPressed = true;
    }
  }
}

void Presenter::reload() {
  delete tetris;
  tetris = new TetrisEngine(FIELD_WIDTH, FIELD_HEIGHT, [&]{
    fillFieldTexture();
    fillShapeTexture();
    fillCounterTexture();
  }, [&]{
    isModalOpened = true;
    modalWindow->setLastScoreResult(tetris->getScore());
  });
  
  fillFieldTexture();
  fillShapeTexture();
  fillCounterTexture();
  isModalOpened    = false;
  isDownBtnPressed = false;
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
      curCell = field->get(j,i);
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

void Presenter::fillCounterTexture() {
  SDL_Rect box = counter->getBox();
  SDL_Surface * textSurf, * surf = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_FillRect(surf, NULL, 0x212121);

  SDL_Rect dst = {1, 1, 0, 0};
  int tw, th;
  textSurf = renderText(
    "Score",
    {245, 245, 245}, 16,
    "docs/RobotoMono-Regular.ttf", &tw, &th);
  dst.x = (box.w - tw) / 2;
  dst.y = 4;
  SDL_BlitSurface(textSurf, NULL, surf, &dst);
  SDL_FreeSurface(textSurf);

  textSurf = renderText(
    std::to_string(tetris->getScore()).c_str(),
    {245, 245, 245}, 16,
    "docs/RobotoMono-Regular.ttf", &tw, &th);
  dst.x = (box.w - tw) / 2;
  dst.y = 4 + th;
  SDL_BlitSurface(textSurf, NULL, surf, &dst);

  SDL_Texture * counterTexture = SDL_CreateTextureFromSurface(renderer, surf);
  counter->update(counterTexture);
  SDL_FreeSurface(textSurf);
  SDL_FreeSurface(surf);
}