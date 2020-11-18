#include "TetrisEngine.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

TetrisEngine::TetrisEngine(
  int x,
  int y
) : field(new Field(x, y)), paused(false) {
  srand(time(0));
  cur = blocks[rand() % 7];
  cur.color = rand() % 4;

  curHeight = realSizeY(cur, &startHeightIndex);
}

TetrisEngine::~TetrisEngine() {
  delete field;
}

shape TetrisEngine::reverseCols(shape s) {
  shape tmp = s;
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size / 2; j++) {
      bool t = s.matrix[i][j];
      tmp.matrix[i][j] = s.matrix[i][s.size - j - 1];
      tmp.matrix[i][s.size - j - 1] = t;
    }
  }
  return tmp;
}

shape TetrisEngine::transpose(shape s) {
  shape tmp = s;
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      tmp.matrix[i][j] = s.matrix[j][i];
    }
  }
  return tmp;
}

void TetrisEngine::update() {
  if (paused) return;
  if (cur.y + curHeight + startHeightIndex < (int) field->getY()) cur.y++;
}

void TetrisEngine::togglePause() {
  paused = !paused;
}

void TetrisEngine::rotate() {
  if (paused) return;
  /*
   *
   * 1ST WAY
   * ban rotation if doesn't fit in field
   * 
  */
  // shape tmp = reverseCols(transpose(cur));
  // int rs, si;
  // rs = realSizeX(tmp, &si);
  // if (0 <= tmp.x + si && tmp.x + si + rs <= (int) field->getX()) {
  //   cur = tmp;
  // }
  /*
   *
   * 2ND WAY
   * rotate and then move
   * 
  */
  shape tmp = reverseCols(transpose(cur));
  int rs, si;
  rs = realSizeX(tmp, &si);
  if (0 > tmp.x + si) {
    tmp.x -= tmp.x + si;
  }
  if (tmp.x + si + rs > (int) field->getX()) {
    tmp.x = (int) field->getX() - (si + rs);
  }
  // std::cout << "width: " << rs << " ";
  rs = realSizeY(tmp, &si);
  if (tmp.y + rs + si < (int) field->getY()) {
    cur = tmp;
    curHeight = rs;
    startHeightIndex = si;
    // std::cout << "height: " << rs << std::endl;
  }
}

Field TetrisEngine::getField() {
  return *field;
}

shape TetrisEngine::getCur() {
  return cur;
}

shape TetrisEngine::getNext() {
  return next;
}

void TetrisEngine::displaceCur(int diff) {
  if (paused) return;
  int rs, si;
  rs = realSizeX(cur, &si);
  if (0 <= cur.x + diff + si && cur.x + diff + si + rs <= (int) field->getX()) {
    cur.x += diff;
  }
}

int TetrisEngine::realSizeY(shape s, int* startIndex) {
  int i, j, sI = -1, eI;
  for (i = 0; i < s.size; i++) {
    for (j = 0; j < s.size; j++) {
      if (s.matrix[i][j]) {
        if (sI == -1) {
          sI = i;
          *startIndex = sI;
        }
        eI = i;
      }
    }
  }
  return eI - sI + 1;
}

int TetrisEngine::realSizeX(shape s, int* startIndex) {
  int i, j, sI = -1, eI;
  for (i = 0; i < s.size; i++) {
    for (j = 0; j < s.size; j++) {
      if (s.matrix[j][i]) {
        if (sI == -1) {
          sI = i;
          *startIndex = sI;
        }
        eI = i;
      }
    }
  }
  return eI - sI + 1;
}