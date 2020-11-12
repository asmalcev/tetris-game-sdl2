#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

SDL_Surface* renderText(
  const std::string text,
  SDL_Color color,
  uint fontSize,
  const std::string fileFont,
  int* textWidth = nullptr,
  int* textHeight = nullptr
);

int openURL(const char *url);