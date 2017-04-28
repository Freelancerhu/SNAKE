#ifndef _SNAKE_COORD_H
#define _SNAKE_COORD_H

struct Coord {
  Coord(int x1, int y1) : x(x1), y(y1){}
  
  int x = 0;
  int y = 0;
};

#endif // _SNAKE_COORD_H
