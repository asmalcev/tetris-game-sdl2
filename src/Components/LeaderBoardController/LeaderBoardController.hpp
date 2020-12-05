#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../LinkedList/SortedFileList.hpp"

struct ResultNote {
  char name[30];
  int score;

  ResultNote() : score(0) {}

  ResultNote(char * m_name, int score)
  : score(score) {
    memcpy(name, m_name, 30);
  }

  ResultNote(const ResultNote& other) {
    score = other.score;
    memcpy(name, other.name, 30);
  }

  ResultNote& operator=(const ResultNote& other) {
    score = other.score;
    memcpy(name, other.name, 30);
  }
};

class LeaderBoardController {
private:
  static LeaderBoardController * instance;
  LeaderBoardController();
  SortedFileList<ResultNote> * sflp;

public:
  ~LeaderBoardController();
  static LeaderBoardController * getInstance();
  void addResult(char *, int);
  SDL_Surface * getBoard(SDL_Rect);
};