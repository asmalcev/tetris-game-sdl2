#pragma once
#include <SDL2/SDL.h>
#include "../Link/Link.hpp"

class Author {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  Link * githubLink;

public:
  Author(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  void click(int x, int y);
};