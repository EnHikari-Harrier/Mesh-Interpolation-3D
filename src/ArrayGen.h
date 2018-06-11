#ifndef __ARRAYGEN_H_
#define __ARRAYGEN_H_
struct MyCell*** CellAllocP(int ni, int nj, int nk);
struct MyNode*** NodeAllocP(int ni, int nj, int nk);
int CellConfig(struct MyCell*** Cell0, struct MyNode*** Node0, int ni, int nj, int nk);
//int MemAlloc(struct MyCell***, struct MyNode***, int, int, int);
int MemFree(struct MyCell***, struct MyNode***);
int ReadMesh(char*, struct MyCell***, struct MyNode***, int, int, int);
#endif // !__ARRAY_GEN_H_
