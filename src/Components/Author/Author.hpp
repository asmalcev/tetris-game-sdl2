#pragma once
#include <SDL2/SDL.h>

class Author {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box, textPos;

public:
  Author(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~Author() {}
  void click(int x, int y);
};