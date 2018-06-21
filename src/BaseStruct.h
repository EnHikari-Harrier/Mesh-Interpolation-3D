/***********************************************************************
* defines basis structs and constants
***********************************************************************/

#ifndef __BASESTRUCT_H_
#define __BASESTRUCT_H_
#define _ColMax 4
#define NS 1

struct MyNode {
  int i, j, k;
  double Pos[3];
  double PM[NS];
  struct MyCell* atCell;    //Which THINCELL am i in?
};

struct MyCell {
  int i, j, k;
  double PM[NS];            //fluid varibles
  double Center[3];         //center coordinate of cell
  struct MyNode* Node[8];
  struct MyNode* FaceNode[6][4];
};
/*Node Def
        j
        |
        2------3
       /|     /|
      6-+----7 |
      | 0----+-1-i
      |/     |/
      4------5
     /
    k
*/
#endif // __BASESTRUCT_H_
