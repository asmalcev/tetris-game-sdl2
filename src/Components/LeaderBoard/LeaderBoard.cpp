#include "LeaderBoard.hpp"
#include "../../Utils/Utils.hpp"
#include "../LeaderBoardController/LeaderBoardController.hpp"

LeaderBoard::LeaderBoard(
    SDL_Renderer* renderer,
    int x,
    int y,
    int w,
    int h
  ) : Window(renderer, x, y, w, h),
      boardTexture(nullptr)
{
  int tw, th;
  SDL_Surface * textSurf = renderText("LEADERBOARD", {245, 245, 245}, 48, "docs/RobotoMono-Bold.ttf", &tw, &th);
  textPos = { (box.w - tw) / 2, 30, tw, th};
  textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
  SDL_FreeSurface(textSurf);
  
  int boardWidth = 300;
  int boardHeight = box.h - 54 - th;
  dataPos = { (box.w - boardWidth) / 2, 42 + th, boardWidth, boardHeight };
  load();
}

LeaderBoard::~LeaderBoard() {
  SDL_DestroyTexture(textTexture);
}

void LeaderBoard::render() {
  SDL_RenderCopy(renderer, textTexture, NULL, &textPos);
  SDL_RenderCopy(renderer, boardTexture, NULL, &dataPos);
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

void LeaderBoard::load() {
  if (boardTexture) SDL_DestroyTexture(boardTexture);
  SDL_Surface * boardSurface = LeaderBoardController::getInstance()->getBoard(dataPos);
  boardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
  SDL_FreeSurface(boardSurface);
}
