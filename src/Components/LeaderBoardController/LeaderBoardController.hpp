#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../LinkedList/SortedFileList.hpp"

constexpr int NAME_LENGTH = 12;
struct ResultNote {
  char name[NAME_LENGTH];
  int score;

  ResultNote() : score(0) {}

  ResultNote(const char * m_name, int score)
  : score(score) {
    memcpy(name, m_name, NAME_LENGTH);
  }

  ResultNote(const ResultNote& other) {
    score = other.score;
    memcpy(name, other.name, NAME_LENGTH);
  }

  ResultNote& operator=(const ResultNote& other) {
    score = other.score;
    memcpy(name, other.name, NAME_LENGTH);
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
  void addResult(const char *, int);
  SDL_Surface * getBoard(SDL_Rect);
};