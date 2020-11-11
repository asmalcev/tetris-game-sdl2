#include "Utils.hpp"
#include <iostream>

SDL_Surface* renderText(
  const std::string text,
  SDL_Color color,
  uint fontSize,
  const std::string fileFont,
  int* textWidth,
  int* textHeight
) {
  TTF_Font* fnt = TTF_OpenFont(fileFont.c_str(), fontSize);
  if (fnt == nullptr) {
    std::cout << "Failed to open font" << std::endl;
    return nullptr;
  }

  if (textWidth != nullptr && textHeight != nullptr) {
    TTF_SizeText(fnt, text.c_str(), textWidth, textHeight);
  }

  SDL_Surface* surf = TTF_RenderText_Blended(fnt, text.c_str(), color);
  if (surf == nullptr) {
    TTF_CloseFont(fnt);
    std::cout << "Failed to create surface" << std::endl;
    return nullptr;
  }

  TTF_CloseFont(fnt);
  return surf;
}