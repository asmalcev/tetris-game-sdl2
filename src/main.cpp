#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "include.hpp"
#include "Components/Button/Button.hpp"
#include "Components/Menu/Menu.hpp"
#include "Components/Presenter/Presenter.hpp"
#include "Components/Author/Author.hpp"

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
   * 2nd window for author section
   * 
  */
  SDL_Window * window2 = nullptr;
  SDL_Renderer * renderer2 = nullptr;
  // SDL_OpenUrl

  /*
   *
   * Runtime
   *
   *
  */
  SDL_Event e;
  bool running = true;
  Window * currentWindow = nullptr;
  Menu menu(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  Presenter pres(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  Author * auth = nullptr;
  
  constexpr int BUTTON_WIDTH = 160;
  constexpr int BUTTON_HEIGHT = 36;
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 164, BUTTON_WIDTH, BUTTON_HEIGHT, "START",
    [&currentWindow, &pres]() {
      if (currentWindow != &pres) {
        currentWindow = &pres;
        pres.reload();
      }
    }));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 212, BUTTON_WIDTH, BUTTON_HEIGHT, "LEADERBOARD"));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 260, BUTTON_WIDTH, BUTTON_HEIGHT, "AUTHOR",
    [&window2, &renderer2, &auth]() {
      if (window2 == nullptr) {
        if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window2, &renderer2) < 0) {
          std::cout << "Failed at SDL_CreateWindowAndRenderer" << std::endl;
          SDL_Quit();
          return 1;
        }
        SDL_SetWindowTitle(window2, "Author");

        SDL_SetRenderDrawColor( renderer2, 33, 33, 33, 255 );
        SDL_RenderClear(renderer2);
        auth = new Author(renderer2, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        SDL_RenderPresent(renderer2);
      }
    }));
  menu.btns.push_back(new Button(renderer, (WINDOW_WIDTH - BUTTON_WIDTH) / 2, 308, BUTTON_WIDTH, BUTTON_HEIGHT, "QUIT", [&running]() {
    running = false;
  }));

  pres.backBtn = new Button(renderer, 24, 24, 50, BUTTON_HEIGHT, "BACK",
    [&currentWindow, &menu]() {
      if (currentWindow != &menu) {
        currentWindow = &menu;
      }
  });

  // currentWindow = &menu;
  currentWindow = &pres;

  while (running) {
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
    SDL_RenderClear(renderer);
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
        break;
      }
      if (SDL_GetWindowID(window) == e.window.windowID) {
        if (e.type == SDL_WINDOWEVENT) {
          if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
            running = false;
            break;
          }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          currentWindow->click(e.motion.x, e.motion.y);
        }
        if (e.type == SDL_MOUSEMOTION) {
          currentWindow->hover(e.motion.x, e.motion.y);
        }
        if (e.type == SDL_KEYUP) {
          currentWindow->keyEvent(e);
        }
      } else if (window2 != nullptr) {
        if (e.type == SDL_WINDOWEVENT) {
          if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
            SDL_DestroyRenderer(renderer2);
            SDL_DestroyWindow(window2);
            delete auth;
            renderer2 = nullptr;
            window2 = nullptr;
            auth = nullptr;
          }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          auth->click(e.motion.x, e.motion.y);
        }
      }
    }
    currentWindow->update();

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
  if (window2 != nullptr) {
    SDL_DestroyRenderer(renderer2);
    SDL_DestroyWindow(window2);
    delete auth;
  }
  TTF_Quit();
  SDL_Quit();
}