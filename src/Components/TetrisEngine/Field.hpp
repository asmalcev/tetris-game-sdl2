#pragma once

typedef unsigned char uchar;

struct Field {
  uchar * matrix;

  Field(
    uchar x,
    uchar y
  );
  ~Field();
  uchar getX();
  uchar getY();

private:
  uchar x;
  uchar y;
};