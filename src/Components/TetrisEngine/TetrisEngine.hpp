#pragma once
#include "Field.hpp"
#include <functional>

constexpr int SHAPES_COUNT = 16;

struct shape {
  bool matrix[4][4];
  int x, y;
  int size;
  int color;
};

class TetrisEngine {
private:
  Field * field;
  shape cur;
  shape next;
  int curHeight;
  int startHeightIndex;
  bool paused;
  bool finished;
  bool isSpeedUp;
  int score;
  std::function<void()> callbackStep;
  std::function<void()> callbackLose;

  shape reverseCols(shape s);
  shape transpose(shape s);
  bool check(shape s);

  shape blocks[SHAPES_COUNT] = {
    {{{0, 0, 1, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // L BLOCK
    {{{1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // Z BLOCK
    {{{1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 4, 0},  // I BLOCK
    {{{1, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // J BLOCK
    {{{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 2, 0},  // O BLOCK
    {{{0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // S BLOCK
    {{{0, 1, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // T BLOCK
    {{{1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // CUSTOM 1 BLOCK
    {{{1, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 1, 0},  // CUSTOM 2 BLOCK
    {{{1, 0, 0, 0},
      {1, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // CUSTOM 3 BLOCK
    {{{1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 2, 0},  // CUSTOM 4 BLOCK
    {{{1, 0, 0, 0},
      {1, 1, 1, 0},
      {1, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // CUSTOM 5 BLOCK
    {{{1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 2, 0},  // CUSTOM 6 BLOCK
    {{{1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 2, 0},  // CUSTOM 7 BLOCK
    {{{1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // CUSTOM 8 BLOCK
    {{{1, 1, 0, 0},
      {0, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}}, 3, 3, 3, 0},  // CUSTOM 9 BLOCK
  };

public:
  TetrisEngine(
    int x,
    int y,
    std::function<void()> callbackStep,
    std::function<void()> callbackLose
  );
  ~TetrisEngine();
  bool update();
  void rotate();
  Field * getField();
  shape getCur();
  shape getNext();
  void displaceCur(int);
  void togglePause();
  int realSizeX(shape s, int * startIndex);
  int realSizeY(shape s, int * startIndex);
  int getScore();
  void slideDown();
  bool toggleSpeedUp();

  int stepDelay;
};