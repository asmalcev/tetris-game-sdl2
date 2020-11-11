#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <functional>

enum ButtonState {
  NORMAL,
  CLICKED,
  HOVERED
};

class Button {
private:
  SDL_Renderer* renderer = nullptr;
  SDL_Rect box;
  float transitionTimer;
  float dTimer;
  ButtonState bs;
  SDL_Texture* btnTexture;
  std::function<void()> m_funcPtr;
  int offset;

public:
  Button(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h,
    std::string text,
    std::function<void()> funcPtr = nullptr
  );
  ~Button();
  SDL_Rect getRect();
  void render();
  void update();
  bool hover(int x, int y);
  bool click(int x, int y);

};