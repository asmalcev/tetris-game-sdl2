#include "Link.hpp"
#include "../../Utils/Utils.hpp"

Link::Link(
  SDL_Renderer* renderer,
  int x,
  int y,
  int textSize,
  const char * link,
  const char * text
) : renderer(renderer),
    box({x, y, 0, 0}),
    link(link)
{
  int tw, th;
  SDL_Surface * textSurf = renderText(text, {245, 245, 245}, textSize, "docs/RobotoMono-Regular.ttf", &tw, &th);
  box.w = tw;
  box.h = th;
  SDL_Texture * LinkTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, LinkTexture, NULL, &box);

  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(LinkTexture);
}

bool Link::click(int x, int y) {
  if (x >= box.x && x <= box.x + box.w &&
      y >= box.y && y <= box.y + box.h)
  {
    openURL(link);
    return true;
  }
  return false;
}