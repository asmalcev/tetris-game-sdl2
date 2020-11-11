#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

SDL_Surface* renderText(
  const std::string text,
  SDL_Color color,
  uint fontSize,
  const std::string fileFont,
  int* textWidth = nullptr,
  int* textHeight = nullptr
);