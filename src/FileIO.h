#ifndef __FILEIO_H_
#define __FILEIO_H_
int ReadConfig(char* FileName);
int ReadMeshInfo(char* FileNameT, char* FileNameD);
int ReadMesh(char* FileName, struct MyCell*** Cell0, struct MyNode*** Node0);
#endif // !__FILEIO_H_
