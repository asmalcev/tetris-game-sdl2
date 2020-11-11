#pragma once
#include <SDL2/SDL.h>
#include <string>

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

public:
  Button(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h,
    std::string text
  );
  SDL_Rect getRect(void);
  void render();
  void update();
  bool hover(int, int);
  bool click(int, int);

};