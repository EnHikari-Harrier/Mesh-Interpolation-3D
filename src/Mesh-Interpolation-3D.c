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
struct MyCell*** ThinCell,*** DenseCell;
struct MyNode*** ThinNode,*** DenseNode;
int ReadConfig(char* FileName);
int niThin = 76, njThin = 51, nkThin = 2;
int niDense = 31, njDense = 31, nkDense = 41;
int MeshInitial(); int MeshRemove();
char DataFileName[150], OutFileName[150];
int SkipLine, MirrorMesh;

int main() {
  ReadConfig("./input/Configure");
  MeshInitial();

  MeshRemove();
  return 0;
}

int MeshInitial() {
  ThinNode = NodeAllocP(niThin, njThin, nkThin);
  ThinCell = CellAllocP(niThin, njThin, nkThin);
  CellConfig(ThinCell, ThinNode, niThin, njThin, nkThin);
  DenseNode = NodeAllocP(niDense, njDense, nkDense);
  DenseCell = CellAllocP(niDense, njDense, nkDense);
  CellConfig(DenseCell, DenseNode, niDense, njDense, nkDense);
  ReadMesh0("./input/testhead2.x", ThinCell, ThinNode);
  ReadMesh("./input/gridt.dat", ThinCell, ThinNode,
    niThin, njThin, nkThin);
  //ReadMesh(DataFileName, MeshCell, MeshNode, niMesh, njMesh, nkMesh);
  //CalcuPara(MeshCell, ScanPlane, niMesh, njMesh, nkMesh);
  //TecOut(OutFileName, ScanPlane, niMesh);
  MeshRemove();
  printf("Calculation Done\n");
  return 0;
}

int MeshRemove() {
  MemFree(ThinCell, ThinNode);
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
  snprintf(DataFileName, sizeof(DataFileName), "%s%s%s", "./input/", buff, ".dat");
  snprintf(OutFileName, sizeof(OutFileName), "%s%s%s", "./output/", buff, "out.dat");
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  fscanf_s(ConfigFile, "%d\n", &SkipLine);
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  //fscanf_s(ConfigFile, "%d%d%d\n", &niMesh, &njMesh, &nkMesh);
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  fscanf_s(ConfigFile, "%d\n", &MirrorMesh);
#else
  ConfigFile = fopen(FileName, "r");
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_r(buff, "\n", &buffp); //cut tail :)
  snprintf(DataFileName, sizeof(DataFileName), "%s%s%s", "./input/", buff, ".dat");
  snprintf(OutFileName, sizeof(OutFileName), "%s%s%s", "./output/", buff, "out.dat");
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  fscanf(ConfigFile, "%d\n", &SkipLine);
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  fscanf(ConfigFile, "%d%d%d\n", &niMesh, &njMesh, &nkMesh);
  //---------------------------------------------------
  fgets(buff, size, ConfigFile);  //skipline
  fscanf(ConfigFile, "%d\n", &MirrorMesh);
#endif // _WIN32
  fclose(ConfigFile);
  free(buff);
  printf("Read Config OK\n");
  return 0;
}