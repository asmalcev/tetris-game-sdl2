#include "FallingPoint.hpp"
#include "../../include.hpp"

#include <iostream>

FallingPoint::FallingPoint(
  SDL_Renderer* renderer,
  int x,
  int y,
  int size
) : renderer(renderer),
    box({x, y, size, size}),
    startY(y) {
}

void FallingPoint::render() {
  if (box.y + box.h < 0) return;
  SDL_SetRenderDrawColor( renderer, 245, 245, 245, 255 );
  SDL_RenderFillRect(renderer, &box);
}

void FallingPoint::update() {
  box.y++;
  if (box.y > (int) WINDOW_HEIGHT) box.y = startY;

  render();
}