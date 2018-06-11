/***********************************************************************
* A mesh interpolation program
* to rebuild an exist single block flowfield to dense mesh
* tecplot ascii inputs are required
***********************************************************************/
#include <stdio.h>
#include "BaseStruct.h"
#include "ArrayGen.h"
struct MyCell*** ThinCell, DenseCell;
struct MyNode*** ThinNode, DenseNode;
static int niThin = 76, njThin = 51, nkThin = 2;
int niDense, njDense;
int MeshInitial();

int main() {
  MeshInitial();

  MemFree(ThinCell, ThinNode);
  return 0;
}

int MeshInitial() {
  ThinNode = NodeAllocP(niThin, njThin, nkThin);
  ThinCell = CellAllocP(niThin, njThin, nkThin);
  CellConfig(ThinCell, ThinNode, niThin, njThin, nkThin);
  printf("done\n");

  //ReadMesh("./input/gridt.dat", ThinCell, ThinNode,
  //  niThin, njThin, nkThin);
  return 0;
}