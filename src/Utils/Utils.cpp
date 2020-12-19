#include "Utils.hpp"
#include <iostream>

SDL_Surface * renderText(
  const std::string text,
  SDL_Color color,
  uint fontSize,
  const std::string fileFont,
  int* textWidth,
  int* textHeight
) {
  TTF_Font * fnt = TTF_OpenFont(fileFont.c_str(), fontSize);
  if (fnt == nullptr) {
    std::cout << "Failed to open font" << std::endl;
    return nullptr;
  }

  if (textWidth != nullptr && textHeight != nullptr) {
    TTF_SizeText(fnt, text.c_str(), textWidth, textHeight);
  }

  SDL_Surface * surf = TTF_RenderText_Blended(fnt, text.c_str(), color);
  if (surf == nullptr) {
    TTF_CloseFont(fnt);
    std::cout << "Failed to create surface" << std::endl;
    return nullptr;
  }

  TTF_CloseFont(fnt);
  return surf;
}

int openURL(const char *url) {
  #ifdef _WIN32
    HINSTANCE res;
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    res = ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    CoUninitialize();
    return (res > (HINSTANCE)32);
  #else
    char buf[1024];
    snprintf(buf, sizeof(buf), "xdg-open %s", url);
    return (system(buf) != -1);
  #endif
}

Uint32 createRGB(int r, int g, int b) {  
  return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

Uint32 createRGB(SDL_Color color) {
  return ((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff);
}

void textSize(
  const std::string text,
  uint fontSize,
  const std::string fileFont,
  int* textWidth,
  int* textHeight
) {
  TTF_Font * fnt = TTF_OpenFont(fileFont.c_str(), fontSize);
  if (fnt == nullptr) {
    std::cout << "Failed to open font" << std::endl;
    return;
  }

  TTF_SizeText(fnt, text.c_str(), textWidth, textHeight);
  TTF_CloseFont(fnt);
}