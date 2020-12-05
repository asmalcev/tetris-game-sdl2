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
  SDL_Surface * textSurf = renderText("About", {245, 245, 245}, 48, "docs/RobotoMono-Bold.ttf", &tw, &th);
  SDL_Rect textPos = { (box.w - tw) / 2, 30, tw, th};
  SDL_Texture * AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
  textSurf = renderText("Rules:", {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 110, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
  textSurf = renderText("Use arrow keys to move figure and space to rotate", {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 130, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
  textSurf = renderText("The figure's falling speed doubles", {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 170, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
  textSurf = renderText("when you earn 1000 points", {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 190, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);

  textSurf = renderText("Author", {245, 245, 245}, 48, "docs/RobotoMono-Bold.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 300, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);
  textSurf = renderText("Made by Alexander Malcev", {245, 245, 245}, 16, "docs/RobotoMono-Regular.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 380, tw, th};
  AuthorTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_RenderCopy(renderer, AuthorTexture, NULL, &textPos);
  SDL_FreeSurface(textSurf);
  SDL_DestroyTexture(AuthorTexture);

  githubLink = new Link(renderer, 190, 400, 16, "https://github.com/qzerrty", "GitHub: github.com/qzerrty");
}

void Author::click(int x, int y) {
  githubLink->click(x, y);
}