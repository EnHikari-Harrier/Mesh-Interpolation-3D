/***********************************************************************
* defines basis structs and constants
***********************************************************************/

#ifndef __BASESTRUCT_H_
#define __BASESTRUCT_H_
#define NC 8

struct MyNode {
  int i, j, k;
  double Pos[3];
  double vv[NC];
  struct MyCell* atCell;    //Which THINCELL am i in?
};

struct MyCell {
  int i, j, k;
  double vv[NC];            //fluid varibles
  double Center[3];         //center coordinate of cell
  struct MyNode* Node[8];
  struct MyNode* FaceNode[6][4];
};
/*Node Def
        2------3
       /|     /|
      6-+----7 |
      | 0----+-1
      |/     |/
      4------5
*/
#endif // __BASESTRUCT_H_
