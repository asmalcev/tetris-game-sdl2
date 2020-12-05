#include "LeaderBoardController.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>

LeaderBoardController::LeaderBoardController() {
  sflp = new SortedFileList<ResultNote>("./docs/leader.bin", [](ResultNote rn, ResultNote rn2)->int {
    int diff = rn.score > rn2.score;
    return (0 < diff) - (diff < 0);
  }, 10);
}

LeaderBoardController::~LeaderBoardController() {
  delete sflp;
}

LeaderBoardController * LeaderBoardController::getInstance() {
  if (!instance) {
    instance = new LeaderBoardController();
  }
  return instance;
}

void LeaderBoardController::addResult(char * name, int score) {
  sflp->addData(ResultNote(name, score));
  sflp->save();
}

SDL_Surface * LeaderBoardController::getBoard(SDL_Rect box) {
  int tw, th;
  SDL_Surface * textSurf,
              * boardSurface = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
  SDL_Rect textPos = { 0, 0, tw, th};

  if (!boardSurface) {
    std::cout << "Failed at SDL_CreateRGBSurface -- LeaderBoardController::getBoard" << std::endl;
    return nullptr;
  }
  SDL_FillRect(boardSurface, NULL, 0x212121);

  sflp->restart();
  ResultNote * rnp = sflp->getCur();
  while (rnp) {
    if (rnp) {
      textSurf = renderText(
        rnp->name, 
        {245, 245, 245}, 16,
        "docs/RobotoMono-Regular.ttf",
        &tw, &th
      );
      SDL_BlitSurface(textSurf, NULL, boardSurface, &textPos);
      SDL_FreeSurface(textSurf);

      textSurf = renderText(
        std::to_string(rnp->score), 
        {245, 245, 245}, 16,
        "docs/RobotoMono-Regular.ttf",
        &tw, &th
      );
      textPos.x = box.w - tw;
      SDL_BlitSurface(textSurf, NULL, boardSurface, &textPos);
      SDL_FreeSurface(textSurf);

      textPos.x = 0;
      textPos.y += th + 12;
    }
    rnp = sflp->next();
  }

  return boardSurface;
}

LeaderBoardController * LeaderBoardController::instance = 0;