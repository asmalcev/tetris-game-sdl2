#include "Field.hpp"
#include <cstring>

Field::Field(
  uchar x,
  uchar y
) : x(x), y(y), matrix(new uchar[x * y]) {}

Field::~Field() {
  delete[] matrix;
}

Field::Field(const Field& field) {
  x = field.x;
  y = field.y;
  memcpy(matrix, field.matrix, sizeof(uchar) * x * y);
}

uchar Field::getX() {
  return x;
}

uchar Field::getY() {  
  return y;
}