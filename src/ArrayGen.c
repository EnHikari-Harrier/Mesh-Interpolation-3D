/***********************************************************************
* Memory allocte & file input/output
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include "BaseStruct.h"

struct MyCell*** CellAllocP(int ni, int nj, int nk) {
  struct MyCell*** Cell0;
  int ni0 = ni - 1, nj0 = nj - 1, nk0 = nk - 1;
  int i, j;
  Cell0 = (struct MyCell***)malloc(ni0 * sizeof(struct MyCell**));
  Cell0[0] = (struct MyCell**)malloc(ni0*nj0 * sizeof(struct MyCell*));
  Cell0[0][0] = (struct MyCell*)malloc(ni0*nj0*nk0 * sizeof(struct MyCell));
  if ((Cell0 != NULL) && (Cell0[0] != NULL) && (Cell0[0][0] != NULL)) {
    for (i = 0; i < ni0; i++) {
      Cell0[i] = Cell0[0] + i;
      for (j = 0; j < nj0; j++) {
        Cell0[i][j] = Cell0[i][0] + j;
      }
    }
  return Cell0;
  }
  else {
    return NULL;
  }
}

struct MyNode*** NodeAllocP(int ni, int nj, int nk) {
  struct MyNode*** Node0;
  int i, j;
  Node0 = (struct MyNode***)malloc(ni * sizeof(struct MyNode**));
  Node0[0] = (struct MyNode**)malloc(ni*nj * sizeof(struct MyNode*));
  Node0[0][0] = (struct MyNode*)malloc(ni*nj*nk * sizeof(struct MyNode));
  if ((Node0 != NULL) && (Node0[0] != NULL) && (Node0[0][0] != NULL)) {
    for (i = 0; i < ni; i++) {
      Node0[i] = Node0[0] + i;
      for (j = 0; j < nj; j++) {
        Node0[i][j] = Node0[i][0] + j;
      }
    }
  return Node0;
  }
  else {
    return NULL;
  }
}

int CellConfig(struct MyCell*** Cell0, struct MyNode*** Node0, int ni, int nj, int nk) {
  int SetFaceNode(struct MyCell* Cell0);
  int ni0 = ni - 1; int nj0 = nj - 1; int nk0 = nk - 1;
  int i, j, k, n;
  for (i = 0; i < ni; i++) {
    for (j = 0; j < nj; j++) {
      for (k = 0; k < nk; k++) {
        Node0[i][j][k].i = i;
        Node0[i][j][k].j = j;
        Node0[i][j][k].k = k;
      }
    }
  }
  for (i = 0; i < ni0; i++) {
    for (j = 0; j < nj0; j++) {
      for (k = 0; k < nk0; k++) {
        Cell0[i][j][k].i = i;
        Cell0[i][j][k].j = j;
        Cell0[i][j][k].k = k;
        int ii, jj, kk;
        int nn = 0;
        for (kk = 0; kk < 2; kk++) {
          for (jj = 0; jj < 2; jj++) {
            for (ii = 0; ii < 2; ii++) {
              Cell0[i][j][k].Node[nn] = &Node0[i + ii][j + jj][k + kk];
              nn++;
            }
          }
        }
      }
    }
  }
  return 0;
}

int MemAlloc(struct MyCell*** Cell0, struct MyNode*** Node0, int ni, int nj, int nk) {
  int SetFaceNode(struct MyCell*);
  int ni0 = ni - 1, nj0 = nj - 1, nk0 = nk - 1;
  int n, i, j, k;
  Node0 = (struct MyNode***)malloc(ni * sizeof(struct MyNode**));
  Node0[0] = (struct MyNode**)malloc(ni*nj * sizeof(struct MyNode*));
  Node0[0][0] = (struct MyNode*)malloc(ni*nj*nk * sizeof(struct MyNode));
  if ((Node0 != NULL) && (Node0[0] != NULL) && (Node0[0][0] != NULL)) {
    for (i = 0; i < ni; i++) {
      Node0[i] = Node0[0] + i;
      for (j = 0; j < nj; j++) {
        Node0[i][j] = Node0[i][0] + j;
        for (k = 0; k < nk; k++) {
          Node0[i][j][k].i = i;
          Node0[i][j][k].j = j;
          Node0[i][j][k].k = k;
        }
      }
    }
  }
  else {
    return 1;
  }
  Cell0 = (struct MyCell***)malloc(ni0 * sizeof(struct MyCell**));
  Cell0[0] = (struct MyCell**)malloc(ni0*nj0 * sizeof(struct MyCell*));
  Cell0[0][0] = (struct MyCell*)malloc(ni0*nj0*nk0 * sizeof(struct MyCell));
  if ((Cell0 != NULL) && (Cell0[0] != NULL) && (Cell0[0][0] != NULL)) {
    for (i = 0; i < ni0; i++) {
      Cell0[i] = Cell0[0] + i;
      for (j = 0; j < nj0; j++) {
        Cell0[i][j] = Cell0[i][0] + j;
        for (k = 0; k < nk0; k++) {
          int ii, jj, kk;
          int nn = 0;
          Cell0[i][j][k].i = i;
          Cell0[i][j][k].j = j;
          Cell0[i][j][k].k = k;
          for (kk = 0; kk < 2; kk++) {
            for (jj = 0; jj < 2; jj++) {
              for (ii = 0; ii < 2; ii++) {
                Cell0[i][j][k].Node[nn] = &Node0[i + ii][j + jj][k + kk];
                nn++;
              }
            }
          }
          SetFaceNode(&Cell0[i][j][k]);
        }
      }
    }
  }
  else {
    return 2;
  }
  return 0;
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

int SetFaceNode(struct MyCell* Cell0) {
  //Face i-
  Cell0->FaceNode[0][0] = Cell0->Node[0];
  Cell0->FaceNode[0][1] = Cell0->Node[2];
  Cell0->FaceNode[0][2] = Cell0->Node[4];
  Cell0->FaceNode[0][3] = Cell0->Node[6];
  //Face i+
  Cell0->FaceNode[1][0] = Cell0->Node[1];
  Cell0->FaceNode[1][1] = Cell0->Node[3];
  Cell0->FaceNode[1][2] = Cell0->Node[5];
  Cell0->FaceNode[1][3] = Cell0->Node[7];
  //Face j-
  Cell0->FaceNode[2][0] = Cell0->Node[0];
  Cell0->FaceNode[2][1] = Cell0->Node[4];
  Cell0->FaceNode[2][2] = Cell0->Node[1];
  Cell0->FaceNode[2][3] = Cell0->Node[5];
  //Face j+
  Cell0->FaceNode[3][0] = Cell0->Node[2];
  Cell0->FaceNode[3][1] = Cell0->Node[6];
  Cell0->FaceNode[3][2] = Cell0->Node[3];
  Cell0->FaceNode[3][3] = Cell0->Node[7];
  //Face k-
  Cell0->FaceNode[4][0] = Cell0->Node[0];
  Cell0->FaceNode[4][1] = Cell0->Node[1];
  Cell0->FaceNode[4][2] = Cell0->Node[2];
  Cell0->FaceNode[4][3] = Cell0->Node[3];
  //Face k+
  Cell0->FaceNode[5][0] = Cell0->Node[4];
  Cell0->FaceNode[5][1] = Cell0->Node[5];
  Cell0->FaceNode[5][2] = Cell0->Node[6];
  Cell0->FaceNode[5][3] = Cell0->Node[7];
  return 0;
}

int ReadConfig() {

  return 0;
}

int ReadMesh(char* FileName, struct MyCell*** Cell0, struct MyNode*** Node0,
  int ni, int nj, int nk) {
  FILE *LoadMesh;
  int i, j, k, n;
  int temp; double tempf;
  printf("%p\n", &Cell0[2][2][2]);
#ifdef _WIN32
  fopen_s(&LoadMesh, FileName, "r");
  //LoadMesh = fopen(FileName, "r");
  //for (i = 0; i < 11; i++) {
  //  fscanf_s(LoadMesh);
  //}
  for (n = 0; n < 3; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          //fscanf(LoadMesh, "%lf", &Node0[i][j][k].Pos[n]);
          printf("%d\t%d\t%d\n", Cell0[i][j][k].i, Cell0[i][j][k].j, Cell0[i][j][k].k);
          fscanf(LoadMesh, "%lf", &tempf);
          printf("%lf\n", tempf);
          Node0[i][j][k].Pos[n] = tempf;
          getchar();
        }
      }
    }
  }
  fscanf_s(LoadMesh, "%d\t%d\t%d", &ni, &nj, &nk);
  //printf("%d\t%d\t%d\t%d\n", temp, ni, nj, nk);
#else
  LoadMesh = fopen(FileName, "rb");
  fscanf(FileName, "%d", &temp);
  fscanf(FileName, "%d\t%d\t%d", &ni, &nj, &nk);
  printf("%d\t%d\t%d\t%d\n", temp, ni, nj, nk);
#endif // _WIN32
  return 0;
}