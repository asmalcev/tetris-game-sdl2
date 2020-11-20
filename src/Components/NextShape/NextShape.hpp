#pragma once
#include <SDL2/SDL.h>

struct shape {
  bool matrix[4][4];
  int x, y;
  int size;
  int color;
};

class NextShape {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  SDL_Texture * shapeTexture;

public:
  NextShape(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~NextShape();
  void render();
  void update(shape);
};