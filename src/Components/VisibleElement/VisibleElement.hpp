#pragma once
#include <SDL2/SDL.h>

class VisibleElement {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  SDL_Texture * elementTexture;

public:
  VisibleElement(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~VisibleElement();
  void render();
  void update(SDL_Texture *);
  SDL_Rect getBox();
};