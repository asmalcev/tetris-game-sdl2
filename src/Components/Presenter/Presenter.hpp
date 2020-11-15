#pragma once
#include "../Window/Window.hpp"
#include "../Button/Button.hpp"

class Presenter : public Window {
private:

public:
  Button * backBtn = nullptr;

  Presenter(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  );
  ~Presenter();
  void render() override;
  void update() override;
  void click(int x, int y) override;
  void hover(int x, int y) override;
};