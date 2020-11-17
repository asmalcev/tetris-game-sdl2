#pragma once
#include "../Window/Window.hpp"
#include <vector>
#include "../Button/Button.hpp"
#include "FallingPoint.hpp"

class Menu : public Window {
private:
  SDL_Rect textPos;
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
  void render() override;
  void update() override;
  void click(int x, int y) override;
  void hover(int x, int y) override;
  void keyEvent(SDL_Event&) override {};
};