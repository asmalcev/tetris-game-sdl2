#include "Field.hpp"
#include <cstring>

Field::Field(
  uchar x,
  uchar y
) : x(x), y(y), matrix(new uchar[x * y]) {
  for (int i = 0; i < x * y; i++) {
    matrix[i] = 0;
  }
}

Field::~Field() {
  delete[] matrix;
}

uchar Field::getX() {
  return x;
}

uchar Field::getY() {  
  return y;
}