#include "Field.hpp"
#include <iostream>

Field::Field(
  uchar x,
  uchar y
) : x(x), y(y) {
  matrix = new LinkedList();
  uchar * line;
  for (int i = 0; i < y; i++) {
    line = new uchar[x];
    for (int j = 0; j < x; j++) {
      line[j] = 0;
    }
    matrix->unshift(line);
  }
}

Field::~Field() {
  delete matrix;
}

uchar Field::getX() {
  return x;
}

uchar Field::getY() {
  return y;
}

uchar& Field::get(int xcoord, int ycoord) {
  Node * cur = matrix->head;
  for (int i = 0; i < ycoord - 1; i++, cur = cur->next);
  uchar * line = cur->data;
  return line[xcoord];
}

int Field::fixCompletedLines() {
  int countDeletedLines = 0;
  Node * cur = matrix->head;
  uchar * line;
  bool flag;
  for (int i = 0; i < y; i++, cur = cur->next) {
    if (cur == nullptr) {
      return countDeletedLines;
    }
    line = cur->data;
    flag = true;
    for (int j = 0; j < x; j++) {
      if (!line[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      if (!countDeletedLines) {
        recolorize();
      }
      countDeletedLines++;
      matrix->remove(line);
      line = new uchar[x];
      for (int j = 0; j < x; j++) {
        line[j] = 0;
      }
      matrix->unshift(line);
    }
  }
  return countDeletedLines;
}

void Field::recolorize() {
  Node * cur = matrix->head;
  uchar * line;
  for (int i = 0; i < y; i++, cur = cur->next) {
    if (cur == nullptr) {
      return;
    }
    line = cur->data;
    for (int j = 0; j < x; j++) {
      if (line[j]) {
        line[j] = (line[j] + 1) % 5 + 1;
      }
    }
  }
}