#include "TetrisEngine.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

TetrisEngine::TetrisEngine(
  int x,
  int y
) : field(new Field(x, y)) {
  srand(time(0));
  cur = blocks[rand() % 7];
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

}

void TetrisEngine::rotate() {
  cur = reverseCols(transpose(cur));
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
  int rs, si;
  rs = realSizeX(cur, &si);
  if (0 <= cur.x + diff + si && cur.x + diff + si + rs <= (int) field->getX()) {
    cur.x += diff;
  }
}

int TetrisEngine::realSizeX(shape s, int* startIndex) {
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
