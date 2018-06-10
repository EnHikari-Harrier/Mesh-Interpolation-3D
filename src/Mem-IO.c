/***********************************************************************
* Memory allocte & file input/output
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "BaseStruct.h"
#include "Functions.h"

int MemAlloc(struct MyCell*** Cell0, struct MyNode*** Node0, int ni, int nj, int nk) {
  int ni0 = ni - 1; int nj0 = nj - 1; int nk0 = nk - 1;
  int n, i, j, k;
  int err = 1;
  Cell0 = (struct MyCell***)malloc(ni0 * sizeof(struct MyCell**));
  Cell0[0] = (struct MyCell**)malloc(ni0*nj0 * sizeof(struct MyCell*));
  Cell0[0][0] = (struct MyCell*)malloc(ni0*nj0*nk0 * sizeof(struct MyCell));
  if ((Cell0 != NULL) && (Cell0[0] != NULL) && (Cell0[0][0] != NULL)) {
    for (i = 0; i < ni0; i++) {
      Cell0[i] = Cell0[0] + i * nj0;
      for (j = 0; j < nj0; j++) {
        Cell0[i][j] = Cell0[i][0] + j * nk0;
      }
    }
    err = 1;
  }
  Node0 = (struct MyNode***)malloc(ni * sizeof(struct MyNode**));
  Node0[0] = (struct MyNode**)malloc(ni*nj * sizeof(struct MyNode*));
  Node0[0][0] = (struct MyNode*)malloc(ni*nj*nk * sizeof(struct MyNode));
  if ((Node0 != NULL) && (Node0[0] != NULL) && (Node0[0][0] != NULL)) {
    for (i = 0; i < ni; i++) {
      Node0[i] = Node0[0] + i * nj;
      for (j = 0; j < nj; j++) {
        Node0[i][j] = Node0[i][0] + j * nk;
      }
    }
    err = 0;
  }
  return err;
}

int MemFree(struct MyCell*** Cell0, struct MyNode*** Node0) {
  free(Cell0[0][0]);
  free(Cell0[0]);
  free(Cell0);
  free(Node0[0][0]);
  free(Node0[0]);
  free(Node0);
  return 0;
}