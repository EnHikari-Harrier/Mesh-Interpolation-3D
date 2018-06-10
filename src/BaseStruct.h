/***********************************************************************
* defines basis structs and constants
***********************************************************************/

#ifndef __BASESTRUCT_H_
#define __BASESTRUCT_H_

struct MyNode
{
  int i, j, k;
  double Pos[3];
  struct MyCell* atCell;    //Which THINCELL am i in?
};

struct MyCell
{
  int i, j, k;
  double Center[3];         //center coordinate of cell
  double vv[8];             //fluid varibles
  struct MyNode* Node[8];
};

#endif // __BASESTRUCT_H_
