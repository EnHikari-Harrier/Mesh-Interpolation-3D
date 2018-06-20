/***********************************************************************
* A mesh interpolation program
* to rebuild an exist single block flowfield to dense mesh
* tecplot ascii inputs are required
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "BaseStruct.h"
#include "ArrayGen.h"
struct MyCell*** ThinCell, *** DenseCell;
struct MyNode*** ThinNode, *** DenseNode;
int ReadConfig(char* FileName);
int niThin, njThin, nkThin;
int niDense, njDense, nkDense;
int MeshInitial(); int MeshRemove();
char DataFileName[150], OutFileName[150];
char ThinFileName[150], DenseFileName[150];
int SkipLine, MirrorMesh;

int main() {
#ifdef _DEBUG
  printf("DEBUG MODE\n");
#endif
  ReadConfig("./input/Configure");
  MeshInitial();

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

int ReadConfig(char* FileName) {
  FILE *ConfigFile;
  int size = 150;
  char *buff = (char*)malloc(size);
  char *buffp;
#ifdef _WIN32
  fopen_s(&ConfigFile, FileName, "r");
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_s(buff, "\n", &buffp); //cut tail :)
  snprintf(ThinFileName, sizeof(ThinFileName), "%s%s", "./input/", buff);
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_s(buff, "\n", &buffp); //cut tail :)
  snprintf(DenseFileName, sizeof(DenseFileName), "%s%s", "./input/", buff);
  //snprintf(OutFileName, sizeof(OutFileName), "%s%s%s", "./output/", buff, "out.dat");
#else
  ConfigFile = fopen(FileName, "r");
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_r(buff, "\n", &buffp); //cut tail :)
  snprintf(ThinFileName, sizeof(DataFileName), "%s%s", "./input/", buff);
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_r(buff, "\n", &buffp); //cut tail :)
  snprintf(DenseFileName, sizeof(DataFileName), "%s%s", "./input/", buff);
#endif // _WIN32
  fclose(ConfigFile);
  free(buff);
  printf("Read Config OK\n");
  return 0;
}