/***********************************************************************
* some frequently used functions
***********************************************************************/
#include <stdbool.h>
#include "BaseStruct.h"

_Bool IsInCell(struct MyCell Cell0, struct MyNode Node0) {
  //Cell0.Node[0]->Pos[0] = 5;
  return true;
}

_Bool IsOverLine(double Point1[3], double Point2[3], double Point0[3]) {
  double a, b, c;
  a = Point1[1] - Point2[1];
  b = Point1[0] - Point2[0];
  c = -Point1[0] * Point2[1] + Point2[0] * Point1[1];
  return (a * Point0[0] + b * Point0[1] + c > 0);
}
