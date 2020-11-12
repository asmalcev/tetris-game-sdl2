#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Components/Button/Button.hpp"
#include "Components/Menu/Menu.hpp"

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;

int main() {
  /*
   *
   * Init systems
   *
   *
  */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  if (TTF_Init() == -1) {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(2);
  }

  SDL_Window * window;
  SDL_Renderer * renderer;
  if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
    std::cout << "Failed at SDL_CreateWindowAndRenderer" << std::endl;
    SDL_Quit();
    return 1;
  }
  SDL_SetWindowTitle(window, "Tetris");
  // SDL_ShowCursor(1); -- use in future to change cursor mb

  /*
   *
   * Runtime
   *
   *
  */
  SDL_Event e;
  bool running = true;
  Menu menu(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  
  constexpr int BUTTON_WIDTH = 160;
  constexpr int BUTTON_HEIGHT = 36;
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 164, BUTTON_WIDTH, BUTTON_HEIGHT, "START"));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 212, BUTTON_WIDTH, BUTTON_HEIGHT, "LEADERBOARD"));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 260, BUTTON_WIDTH, BUTTON_HEIGHT, "AUTHOR"));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 308, BUTTON_WIDTH, BUTTON_HEIGHT, "QUIT", [&running]() {
    running = false;
  }));

  while (running) {
    SDL_SetRenderDrawColor( renderer, 33, 33, 33, 255 );
    SDL_RenderClear(renderer);
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        menu.click(e.motion.x, e.motion.y);
      }
      if (e.type == SDL_MOUSEMOTION) {
        menu.hover(e.motion.x, e.motion.y);
      }
    }
    menu.update();

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  /*
   *
   * Free systems
   *
   *
  */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}