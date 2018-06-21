/***********************************************************************
* File input/output
***********************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "BaseStruct.h"
#include "FileIO.h"
extern int niThin, njThin, nkThin;
extern int niDense, njDense, nkDense;
extern char ThinFileName[150], DenseFileName[150], ThinResultName[150];
extern int SkipLine;

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
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_s(buff, "\n", &buffp); //cut tail :)
  snprintf(ThinResultName, sizeof(ThinResultName), "%s%s", "./input/", buff);
  fgets(buff, size, ConfigFile);  //skipline
  fscanf_s(ConfigFile, "%d", &SkipLine);
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
  fgets(buff, size, ConfigFile);  //skipline
  fgets(buff, size, ConfigFile);
  strtok_r(buff, "\n", &buffp); //cut tail :)
  snprintf(ThinResultName, sizeof(ThinResultName), "%s%s", "./input/", buff);
  fgets(buff, size, ConfigFile);  //skipline
  fscanf(ConfigFile, "%d\n", SkipLine);
#endif // _WIN32
  fclose(ConfigFile);
  free(buff);
  printf("Read Config OK\n");
  return 0;
}

int ReadMeshInfo(char* FileNameT, char* FileNameD) {
  FILE *MeshFileT, *MeshFileD;
  int size = 150;
  int nBlock, nNode[3];
#ifdef _WIN32
  fopen_s(&MeshFileT, FileNameT, "rb");
  fopen_s(&MeshFileD, FileNameD, "rb");
#else
  MeshFileT = fopen(FileNameT, "rb");
  MeshFileD = fopen(FileNameD, "rb");
#endif
  fread(&nBlock, sizeof(int), 1, MeshFileT);
  fread(nNode, sizeof(int), 3, MeshFileT);
  niThin = nNode[0]; njThin = nNode[1]; nkThin = nNode[2];
  fread(&nBlock, sizeof(int), 1, MeshFileD);
  fread(nNode, sizeof(int), 3, MeshFileD);
  niDense = nNode[0]; njDense = nNode[1]; nkDense = nNode[2];
  fclose(MeshFileT);
  fclose(MeshFileD);
  printf("MeshThin\t%s\nni=%d\tnj=%d\tnk=%d\n", FileNameT, niThin, njThin, nkThin);
  printf("MeshDense\t%s\nni=%d\tnj=%d\tnk=%d\n", FileNameD, niDense, njDense, nkDense);
  return 0;
}

int ReadMesh(char* FileName, struct MyCell*** Cell0, struct MyNode*** Node0) {
#ifdef _DEBUG
  int WriteMesh(char* FileName, struct MyNode*** Node0,
    int ni, int  nj, int nk); //to Write Verify Mesh
#endif // _DEBUG
  FILE *MeshFile;
  int nBlock, nNode[3];
  int ni, nj, nk;
  int i, j, k, n;
#ifdef _WIN32
  fopen_s(&MeshFile, FileName, "rb");
#else
  MeshFile = fopen(FileName, "rb");
#endif
  fread(&nBlock, sizeof(int), 1, MeshFile);
  fread(nNode, sizeof(int), 3, MeshFile);
  ni = nNode[0]; nj = nNode[1]; nk = nNode[2];
  for (n = 0; n < 3; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          fread(&Node0[i][j][k].Pos[n], sizeof(double), 1, MeshFile);
        }
      }
    }
  }
  fclose(MeshFile);
#ifdef _DEBUG
  WriteMesh(FileName, Node0, ni, nj, nk);
#endif // _DEBUG
  return 0;
}

int ReadThinResult(char* FileName, struct MyCell*** Cell0, int ni, int nj, int nk) {
  FILE *TecFile;
  int ni0 = ni - 1, nj0 = nj - 1, nk0 = nk - 1;
  int i, j, k, n;
  int size = 150;
  double temp;
  char *buff = (char*)malloc(size);
#ifdef _WIN32
  fopen_s(&TecFile, FileName, "r");
  for (n = 0; n < SkipLine; n++) {
    fgets(buff, size, TecFile);  //skipline
  }
  for (n = 0; n < 3; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          fscanf_s(TecFile, "%lf", &temp); //skip coorde
        }
      }
    }
  }
  for (n = 0; n < NS; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          fscanf_s(TecFile, "%lf", &Cell0[i][j][k].PM[n]);
        }
      }
    }
  }
#endif // _WIN32
  fclose(TecFile);
  return 0;
}

#ifdef _DEBUG
int WriteMesh(char* FileName, struct MyNode*** Node0,
  int ni, int  nj, int nk) {
  FILE *TecFile;
  int i, j, k, n;
  int Col = 0;
  char FileName0[150];
  snprintf(FileName0, sizeof(FileName0), "%s.dat", FileName);
#ifdef _WIN32
  fopen_s(&TecFile, FileName0, "w");
  fprintf_s(TecFile, "VARIABLES = \"x\"\n\"y\"\n\"z\"\n");
  fprintf_s(TecFile, "ZONE I=%d, J=%d, K=%d\n", ni, nj, nk);
  fprintf_s(TecFile, "DATAPACKING=BLOCK\n");
  for (n = 0; n < 3; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          fprintf_s(TecFile, "%lf", Node0[i][j][k].Pos[n]);
          if (++Col < _ColMax) {
            fprintf_s(TecFile, "\t");
          }
          else {
            fprintf_s(TecFile, "\n");
            Col = 0;
          }
        }
      }
    }
  }
#else
  TecFile = fopen(FileName0, "w");
  fprintf(TecFile, "VARIABLES = \"x\"\n\"y\"\n\"z\"\n");
  fprintf(TecFile, "ZONE I=%d, J=%d, K=%d\n", ni, nj, nk);
  fprintf(TecFile, "DATAPACKING=BLOCK\n");
  for (n = 0; n < 3; n++) {
    for (k = 0; k < nk; k++) {
      for (j = 0; j < nj; j++) {
        for (i = 0; i < ni; i++) {
          fprintf(TecFile, "%lf", Node0[i][j][k].Pos[n]);
          if (++Col < _ColMax) {
            fprintf(TecFile, "\t");
          }
          else {
            fprintf(TecFile, "\n");
            Col = 0;
          }
        }
      }
    }
  }
#endif // _WIN32
  fclose(TecFile);
  return 0;
}
#endif // _DEBUG
