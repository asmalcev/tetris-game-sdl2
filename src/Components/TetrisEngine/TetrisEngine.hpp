#pragma once
#include "Field.hpp"
#include <functional>

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
  std::function<void()> callback;

  shape reverseCols(shape s);
  shape transpose(shape s);
  int realSizeX(shape s, int * startIndex);
  int realSizeY(shape s, int * startIndex);
  bool check(shape s);

  shape blocks[7] = {
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
  };

public:
  TetrisEngine(
    int x,
    int y,
    std::function<void()> callback
  );
  ~TetrisEngine();
  void update();
  void rotate();
  Field * getField();
  shape getCur();
  shape getNext();
  void displaceCur(int);
  void togglePause();
};