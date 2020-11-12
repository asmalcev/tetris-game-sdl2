#include "Author.hpp"
#include "../../Utils/Utils.hpp"

Author::Author(
  SDL_Renderer* renderer,
  int x,
  int y,
  int w,
  int h
) : renderer(renderer),
    box({x, y, w, h})
{
  int tw, th;
  SDL_Surface * textSurf = renderText("Author", {245, 245, 245}, 48, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 30, tw, th};
  SDL_Texture * AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);

  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
}

void Author::click(int x, int y) {

}