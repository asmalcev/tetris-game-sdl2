#pragma once
#include <SDL2/SDL.h>

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
  void update(SDL_Texture *);
  SDL_Rect getBox();
};