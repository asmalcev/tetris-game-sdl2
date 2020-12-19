#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <functional>

enum TextFieldState {
  UNFOCUSED,
  FOCUSED
};

class TextField {
private:
  SDL_Renderer * renderer = nullptr;
  SDL_Texture  * fieldTexture;
  SDL_Texture  * placeholderTexture;
  SDL_Rect box;
  SDL_Rect textBox;
  TextFieldState tfs;
  std::function<void(std::string&, SDL_Event&, int&)> m_funcPtr;
  std::string value;
  std::string placeholder;
  int timer;
  int letterOffset;
  int placeholderWidth;

public:
  TextField(
    SDL_Renderer * renderer,
    int x,
    int y,
    int w,
    int h,
    std::string placeholderText = "Text...",
    std::function<void(std::string&, SDL_Event&, int&)> funcPtr = nullptr
  );
  ~TextField();
  void render();
  void update();
  bool hover(int x, int y);
  bool click(int x, int y);
  void keyEvent(SDL_Event&);
  std::string getValue();
  void displaceBox(int x, int y);

};