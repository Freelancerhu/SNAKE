#ifndef CONTROLSNAKE_H
#define CONTROLSNAKE_H
#include <coord.h>
#include <vector>
class ControlSnake {
public:
  bool Control(std::vector<Coord> &snake, std::vector<Coord> &egg, char index);
};
#endif // CONTROLSNAKE_H
