/***********************************************************************
* A mesh interpolation program
* to rebuild an exist single block flowfield to dense mesh
* tecplot ascii inputs are required
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "BaseStruct.h"
#include "ArrayGen.h"
#include "FileIO.h"
struct MyCell*** ThinCell, *** DenseCell;
struct MyNode*** ThinNode, *** DenseNode;
int MeshInitial(); int MeshRemove();
int niThin, njThin, nkThin;
int niDense, njDense, nkDense;
char ThinFileName[150], DenseFileName[150];
int SkipLine, MirrorMesh;

int main() {
#ifdef _DEBUG
  printf("DEBUG MODE\n");
#endif
  ReadConfig("./input/Configure");
  MeshInitial();
  //

  //
  printf("Calculation Done\n");
  MeshRemove();
  return 0;
}

int MeshInitial() {
  ReadMeshInfo(ThinFileName, DenseFileName);
  //
  ThinNode = NodeAllocP(niThin, njThin, nkThin);
  ThinCell = CellAllocP(niThin, njThin, nkThin);
  CellConfig(ThinCell, ThinNode, niThin, njThin, nkThin);
  ReadMesh(ThinFileName, ThinCell, ThinNode);
  //
  DenseNode = NodeAllocP(niDense, njDense, nkDense);
  DenseCell = CellAllocP(niDense, njDense, nkDense);
  CellConfig(DenseCell, DenseNode, niDense, njDense, nkDense);
  ReadMesh(DenseFileName, DenseCell, DenseNode);
  return 0;
}

int MeshRemove() {
  MemFree(ThinCell, ThinNode);
  MemFree(DenseCell, DenseNode);
  return 0;
}
