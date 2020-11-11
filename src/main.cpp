#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Components/Button/Button.hpp"

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

  Button btn(renderer, 20, 20, 160, 36, "START");
  Button btn2(renderer, 20, 68, 160, 36, "LEADERBOARD");
  Button btn3(renderer, 20, 116, 160, 36, "AUTHOR");
  Button btn4(renderer, 20, 164, 160, 36, "QUIT", [&running]() {
    running = false;
  });

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
        btn.click(e.motion.x, e.motion.y);
        btn2.click(e.motion.x, e.motion.y);
        btn3.click(e.motion.x, e.motion.y);
        btn4.click(e.motion.x, e.motion.y);
        
      }
      if (e.type == SDL_MOUSEMOTION) {
        btn.hover(e.motion.x, e.motion.y);
        btn2.hover(e.motion.x, e.motion.y);
        btn3.hover(e.motion.x, e.motion.y);
        btn4.hover(e.motion.x, e.motion.y);
      }
    }

    btn.update();
    btn2.update();
    btn3.update();
    btn4.update();

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