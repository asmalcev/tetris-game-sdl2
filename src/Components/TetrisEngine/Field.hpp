#pragma once
#include "../LinkedList/LinkedList.hpp"

typedef unsigned char uchar;

struct Field {

  Field(
    uchar x,
    uchar y
  );
  ~Field();
  uchar getX();
  uchar getY();
  uchar& get(int xcoord, int ycoord);
  int fixCompletedLines();
  void recolorize();

private:
  uchar x;
  uchar y;
  LinkedList * matrix;
};