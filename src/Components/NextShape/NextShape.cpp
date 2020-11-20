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
  if (shapeTexture != nullptr) SDL_DestroyTexture(shapeTexture);
}

void NextShape::render() {
  if (shapeTexture != nullptr) SDL_RenderCopy(renderer, shapeTexture, NULL, &box);
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  SDL_RenderDrawRect(renderer, &box);
}

void NextShape::update(SDL_Texture * texture) {
  if (shapeTexture != nullptr) SDL_DestroyTexture(shapeTexture);
  shapeTexture = texture;
}

SDL_Rect NextShape::getBox() {
  return box;
}