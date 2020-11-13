#pragma once
#include <SDL2/SDL.h>
#include "../../Utils/Utils.hpp"

class Link {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  const char * link;

public:
  Link(
    SDL_Renderer* renderer,
    int x,
    int y,
    int textSize,
    const char * link,
    const char * text
  );
  bool click(int x, int y);
};