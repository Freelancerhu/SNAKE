#ifndef _SNAKE_COORD_H
#define _SNAKE_COORD_H

struct Coord {
  Coord();
  Coord(int x1, int y1);
  
  int x = 0;
  int y = 0;
 
  Coord(const Coord &coord_) = default;

  Coord &operator=(const Coord &coord_) {
    (*this).x = coord_.x;
    (*this).y = coord_.y;
  }
};

#endif // _SNAKE_COORD_H
