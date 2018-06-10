/***********************************************************************
* A mesh interpolation program
* to rebuild an exist single block flowfield to dense mesh
* tecplot ascii inputs are required
***********************************************************************/
#include <stdio.h>
#include "BaseStruct.h"
#include "Mem-IO.h"
struct MyCell** ThinCell, DenseCell;
struct MyNode** ThinNode, DenseNode;
int niThin=51, njThin=51;
int niDense, njDense;

int main() {
  MemAlloc(ThinCell, ThinNode, niThin, njThin);
  return 0;
}