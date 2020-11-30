#include "LeaderBoard.hpp"
#include "../../Utils/Utils.hpp"

LeaderBoard::LeaderBoard(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  ) : Window(renderer, x, y, w, h)
{
  int tw, th;
  SDL_Surface * textSurf = renderText("LEADERBOARD", {245, 245, 245}, 48, "docs/RobotoMono-Bold.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 30, tw, th};
  leaderBoardTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_FreeSurface(textSurf);
}

LeaderBoard::~LeaderBoard() {
  SDL_DestroyTexture(leaderBoardTexture);
}

void LeaderBoard::render() {
  SDL_RenderCopy(renderer, leaderBoardTexture, NULL, &textPos);
}

void LeaderBoard::update() {
  render();

  backBtn->update();
}

void LeaderBoard::click(int x, int y) {
  backBtn->click(x, y);
}

void LeaderBoard::hover(int x, int y) {
  backBtn->hover(x, y);
}