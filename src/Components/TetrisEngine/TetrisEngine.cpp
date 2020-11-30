#include "TetrisEngine.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

TetrisEngine::TetrisEngine(
  int x,
  int y,
  std::function<void()> callbackStep,
  std::function<void()> callbackLose
) : field(new Field(x, y)),
    paused(false),
    finished(false),
    callbackStep(callbackStep),
    callbackLose(callbackLose),
    score(0)
{
  srand(time(0));
  cur = blocks[rand() % SHAPES_COUNT];
  cur.color = rand() % 5;
  cur.x = (x - cur.size) / 2;

  next = blocks[rand() % SHAPES_COUNT];
  next.color = rand() % 5;
  next.x = (x - next.size) / 2;
  next.y = 0;

  curHeight = realSizeY(cur, &startHeightIndex);
  cur.y = 0;
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
  if (paused || finished) return;

  shape tmp = cur;
  tmp.y++;
  if (check(tmp) && cur.y + curHeight + startHeightIndex < (int) field->getY()) {
    cur.y++;
  } else {
    for (int i = 0; i < cur.size; i++) {
      for (int j = 0; j < cur.size; j++) {
        if (cur.matrix[i][j]) {
          field->get(cur.x + j, cur.y + i) = cur.color + 1;
        }
      }
    }
    score += cur.size * 2 + field->fixCompletedLines() * 30;
    if (!check(next)) {
      callbackLose();
      finished = true;
      return;
    }
    cur = next;
    curHeight = realSizeY(cur, &startHeightIndex);


    next = blocks[rand() % SHAPES_COUNT];
    next.color = rand() % 5;
    next.x = ((int) field->getX() - next.size) / 2;
    next.y = 0;
    callbackStep();
  }
}

void TetrisEngine::togglePause() {
  paused = !paused;
}

bool TetrisEngine::check(shape s) {
  for (int i = 0; i < s.size; i++) {
    for (int j = 0; j < s.size; j++) {
      if (s.matrix[i][j] &&
        field->get(s.x + j, s.y + i)) {
        return false;
      }
    }
  }
  return true;
}

void TetrisEngine::rotate() {
  if (paused || finished) return;

  shape tmp = reverseCols(transpose(cur));
  int rs, si;
  rs = realSizeX(tmp, &si);
  if (0 > tmp.x + si) {
    tmp.x -= tmp.x + si;
  }
  if (tmp.x + si + rs > (int) field->getX()) {
    tmp.x = (int) field->getX() - (si + rs);
  }
  rs = realSizeY(tmp, &si);
  if (check(tmp) && tmp.y + rs + si < (int) field->getY()) {
    cur = tmp;
    curHeight = rs;
    startHeightIndex = si;
  }
}

Field * TetrisEngine::getField() {
  return field;
}

shape TetrisEngine::getCur() {
  return cur;
}

shape TetrisEngine::getNext() {
  return next;
}

void TetrisEngine::displaceCur(int diff) {
  if (paused || finished) return;
  int rs, si;
  rs = realSizeX(cur, &si);
  shape tmp = cur;
  tmp.x += diff;
  if (
    0 <= cur.x + diff + si &&
    cur.x + diff + si + rs <= (int) field->getX() &&
    check(tmp)
  ) {
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

int TetrisEngine::getScore() {
  return score;
}