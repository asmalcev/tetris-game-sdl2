#pragma once
#include <SDL2/SDL.h>

class Window {
protected:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;

public:
  Window(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  ) : renderer(renderer),
      box({x, y, w, h}) {}
  virtual ~Window() {};
  virtual void render() = 0;
  virtual void update() = 0;
  virtual void click(int x, int y) = 0;
  virtual void hover(int x, int y) = 0;
};