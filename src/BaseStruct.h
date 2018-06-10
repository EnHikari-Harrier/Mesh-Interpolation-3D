/***********************************************************************
* defines basis structs and constants
***********************************************************************/

#ifndef __BASESTRUCT_H_
#define __BASESTRUCT_H_

struct MyNode
{
  int i, j;
  double Pos[2];
  struct MyCell* atCell;    //Which THINCELL am i in?
};

struct MyCell
{
  int i, j;
  double Center[2];         //center coordinate of cell
  double vv[8];             //fluid varibles
  struct MyNode* Node[4];
};

#endif // __BASESTRUCT_H_
