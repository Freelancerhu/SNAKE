#include "controlsnake.h"

bool controlSnake::Control_Snake(std::vector<coord> &A, std::vector<coord> &eggVec, char index) {
  int dx = 0, dy = 0;
  static int delta[][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}};
  int direction = 0;
  switch (index) {
    case 'w':
      direction = 0;
      break;
    case 's':
      direction = 1;
      break;
    case 'a':
      direction = 2;
      break;
    case 'd':
      direction = 3;
      break;
    default:
      ;
  }
  dx = delta[direction][0];
  dy = delta[direction][1];
  if (A[0].x+dx<0 || A[0].y+dy<0 ||
      A[0].x+dx>=20 || A[0].y+dy>=20)
    return false;

  for (int i = A.size() - 1; i > 0; --i) {
    A[i].x = A[i - 1].x;
    A[i].y = A[i - 1].y;
  }
  A[0].x = A[0].x + dx;
  A[0].y = A[0].y + dy;
  for (int i = 1; i < A.size(); ++i) {
      if (A[0].x == A[i].x && A[0].y == A[i].y)
          return false;
  }

  if (A[0].x == eggVec[0].x && A[0].y == eggVec[0].y) {
    eggVec.clear();
    int tempX = A.back().x, tempY = A.back().y;
    A.push_back(coord(tempX, tempY));
  }
  return true;
}
