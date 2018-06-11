/***********************************************************************
* some frequently used functions
***********************************************************************/
#include <stdbool.h>
#include "BaseStruct.h"

bool IsInCell(struct MyNode Node0, struct MyCell Cell0) {
  //Cell0.Node[0]->Pos[0] = 5;
  return true;
}

bool IsOverLine(double Point1[3], double Point2[3], double Point0[3]) {
  double a, b, c;
  a = Point1[1] - Point2[1];
  b = Point1[0] - Point2[0];
  c = -Point1[0] * Point2[1] + Point2[0] * Point1[1];
  return (a * Point0[0] + b * Point0[1] + c > 0);
}

int Node2Face(struct MyNode Node0, struct MyCell Cell0, int FaceID) {
  struct MyNode NodeList[3];
  double a, b, c, d;
  double result;
  int n;
  for (n = 0; n < 4; n++) {
    NodeList[n] = *Cell0.FaceNode[FaceID][n];
  }
  a = (NodeList[1].Pos[1] - NodeList[0].Pos[1])*(NodeList[2].Pos[2] - NodeList[0].Pos[2])
    - (NodeList[1].Pos[2] - NodeList[0].Pos[2])*(NodeList[2].Pos[1] - NodeList[0].Pos[1]);
  b = (NodeList[1].Pos[2] - NodeList[0].Pos[2])*(NodeList[2].Pos[0] - NodeList[0].Pos[0])
    - (NodeList[1].Pos[0] - NodeList[0].Pos[0])*(NodeList[2].Pos[2] - NodeList[0].Pos[2]);
  c = (NodeList[1].Pos[0] - NodeList[0].Pos[0])*(NodeList[2].Pos[1] - NodeList[0].Pos[1])
    - (NodeList[1].Pos[1] - NodeList[0].Pos[1])*(NodeList[2].Pos[0] - NodeList[0].Pos[0]);
  d = -(a * NodeList[0].Pos[0] + b * NodeList[0].Pos[1] + c * NodeList[0].Pos[2]);
  result = a * Node0.Pos[0] + b * Node0.Pos[1] + c * Node0.Pos[2] + d;
  if (result > 0.f)
    return 1;
  else if (result < 0.f)
    return -1;
  else
    return 0;
}


//a = ((p2.y - p1.y)*(p3.z - p1.z) - (p2.z - p1.z)*(p3.y - p1.y));
//b = ((p2.z - p1.z)*(p3.x - p1.x) - (p2.x - p1.x)*(p3.z - p1.z));
//c = ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x));
//d = (0 - (a*p1.x + b * p1.y + c * p1.z));
//a*x+b*y+c*z+d