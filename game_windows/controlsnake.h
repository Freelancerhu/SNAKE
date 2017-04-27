#ifndef CONTROLSNAKE_H
#define CONTROLSNAKE_H
#include <vector>
#include <coord.h>
class controlSnake {
public:
  bool Control_Snake(std::vector<coord> &A, std::vector<coord> &eggVec, char index);
};
#endif // CONTROLSNAKE_H
