#ifndef _SNAKE_CONTROLSNAKE_H
#define _SNAKE_CONTROLSNAKE_H

#include <coord.h>
#include <vector>

#include "control-snake.h"

class ControlSnake {
public:
  bool Control(std::vector<Coord> &snake, std::vector<Coord> &egg, char index);
};

#endif // _SNAKE_CONTROLSNAKE_H
