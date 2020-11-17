#pragma once
#include "../Window/Window.hpp"
#include "../Button/Button.hpp"
#include "../TetrisEngine/TetrisEngine.hpp"

class Presenter : public Window {
private:
  TetrisEngine * tetris;
  SDL_Rect fieldBox;

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
  void keyEvent(SDL_Event&) override;
};