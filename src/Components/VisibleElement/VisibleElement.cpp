#include "VisibleElement.hpp"

VisibleElement::VisibleElement(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  ) : renderer(renderer),
      box({x, y, w, h}) {}

VisibleElement::~VisibleElement() {
  if (elementTexture != nullptr) SDL_DestroyTexture(elementTexture);
}

void VisibleElement::render() {
  if (elementTexture != nullptr) SDL_RenderCopy(renderer, elementTexture, NULL, &box);
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  SDL_RenderDrawRect(renderer, &box);
}

void VisibleElement::update(SDL_Texture * texture) {
  if (elementTexture != nullptr) SDL_DestroyTexture(elementTexture);
  elementTexture = texture;
}

SDL_Rect VisibleElement::getBox() {
  return box;
}