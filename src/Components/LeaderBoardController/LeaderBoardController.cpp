#include "LeaderBoardController.hpp"

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
}

SDL_Texture * LeaderBoardController::getBoard() {
  sflp->restart();
  ResultNote * rnp = sflp->getCur();
  while (rnp) {
    if (rnp != nullptr) {
      std::cout << rnp->name << " " << rnp->score << std::endl;
    }
    rnp = sflp->next();
  }
}

LeaderBoardController * LeaderBoardController::instance = 0;