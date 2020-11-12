#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "../Button/Button.hpp"
#include "FallingPoint.hpp"

class Menu {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box, textPos;
  SDL_Texture* menuTexture;
  std::vector<FallingPoint*> points;

public:
  std::vector<Button*> btns;
  
  Menu(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~Menu();
  void render();
  void update();
  void click(int x, int y);
  void hover(int x, int y);
};