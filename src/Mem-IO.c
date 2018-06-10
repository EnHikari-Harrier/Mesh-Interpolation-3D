/***********************************************************************
* Memory allocte & file input/output
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "BaseStruct.h"
#include "Functions.h"

int MemAlloc(struct MyCell** Cell0, struct MyNode** Node0, int ni, int nj) {
  int ni0 = ni - 1; int nj0 = nj - 1;
  int n, i, j;
  Cell0 = (struct MyCell**)malloc(ni0 * sizeof(struct MyCell*));
  Cell0[0] = (struct MyCell*)malloc(ni0*nj0 * sizeof(struct MyCell));
  for (i = 1; i < ni0; i++) {
    Cell0[i] = Cell0[i - 1] + nj0;
  }
  Node0 = (struct MyNode**)malloc(ni * sizeof(struct MyNode*));
  Node0[0] = (struct MyNode*)malloc(ni*nj * sizeof(struct MyNode));
  for (i = 1; i < ni; i++) {
    Node0[i] = Node0[i - 1] + nj;
  }
  for (i = 0; i < ni0; i++) {
    for (j = 0; j < nj0; j++) {
      Cell0[i][j].i = i; Cell0[i][j].j = j;
      Cell0[i][j].Node[0] = &Node0[i][j];
      Cell0[i][j].Node[1] = &Node0[i + 1][j];
      Cell0[i][j].Node[2] = &Node0[i][j + 1];
      Cell0[i][j].Node[3] = &Node0[i + 1][j + 1];
    }
  }
  for (i = 0; i < ni; i++) {
    for (j = 0; j < nj; j++) {
      Node0[i][j].i = i; Node0[i][j].j = j;
      Node0[i][j].atCell = NULL;
    }
  }
  return 0;
}

int MemFree(struct MyCell** Cell0, struct MyNode** Node0) {
  free(Cell0[0]);
  free(Cell0);
  free(Node0[0]);
  free(Node0);
  return 0;
}