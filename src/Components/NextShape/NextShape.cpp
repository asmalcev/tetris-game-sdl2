#include "NextShape.hpp"

NextShape::NextShape(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  ) : renderer(renderer),
      box({x, y, w, h}) {}

NextShape::~NextShape() {

}

void NextShape::render() {
  SDL_RenderCopy(renderer, shapeTexture, NULL, &box);
}

void NextShape::update(shape s) {

}