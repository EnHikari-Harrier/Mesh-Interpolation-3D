/***********************************************************************
* some frequently used functions
***********************************************************************/
#include <stdbool.h>
#include "BaseStruct.h"
#include "Functions.h"

int Node2Face(double CenterP[3], struct MyCell Cell0, int FaceID) {
  struct MyNode NodeList[4];
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
  result = a * CenterP[0] + b * CenterP[1] + c * CenterP[2] + d;
  if (result > 0.f)
    return 1;
  else if (result < 0.f)
    return -1;
  else
    return 0;
}

bool IsInCell(struct MyNode Node0, struct MyCell Cell0) {
  int n;
  int sign0, sign1;
  for (n = 0; n < 6; n++) {
    sign0 = Node2Face(Node0.Pos, Cell0, n);
    sign1 = Node2Face(Cell0.Center, Cell0, n);
    if (sign0*sign1 < 0.f) {
      return false;
    }
  }
  return true;
}

bool IsOverLine(double Point1[3], double Point2[3], double Point0[3]) {
  double a, b, c;
  a = Point1[1] - Point2[1];
  b = Point1[0] - Point2[0];
  c = -Point1[0] * Point2[1] + Point2[0] * Point1[1];
  return (a * Point0[0] + b * Point0[1] + c > 0);
}

int Cell2Node(struct MyNode* Node) {
  int n;
  for (n = 0; n < NC; n++) {
    Node->vv[n] = Node->atCell->vv[n];
  }
  return 0;
}

int Node2Cell(struct MyCell * Cell) {
  double vvtemp[NC];
  int n;
  int ii, jj, kk;
  for (n = 0; n < NC; n++) {
    vvtemp[n] = 0.f;
    int nn = 0;
    for (kk = 0; kk < 2; kk++) {
      for (jj = 0; jj < 2; jj++) {
        for (ii = 0; ii < 2; ii++) {
          vvtemp[n] = Cell->Node[nn]->vv[n];
          nn++;
        }
      }
    }
    Cell->vv[n] = vvtemp[n] / 8;
  }
  return 0;
}


//a = ((p2.y - p1.y)*(p3.z - p1.z) - (p2.z - p1.z)*(p3.y - p1.y));
//b = ((p2.z - p1.z)*(p3.x - p1.x) - (p2.x - p1.x)*(p3.z - p1.z));
//c = ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x));
//d = (0 - (a*p1.x + b * p1.y + c * p1.z));
//a*x+b*y+c*z+d