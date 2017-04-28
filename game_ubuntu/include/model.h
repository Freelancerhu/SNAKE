#ifndef _SNAKEMODEL_H
#define _SNAKEMODEL_H

#include <cstdlib>

#include <vector>

#include "map.h"
#include "control-snake.h"
#include "coord.h"

class Model {
public:
  Model() = default;
  ~Model() = default;

  void GeneSnake();

  void GeneEgg();

  void SetMap(int x, int y);

  bool Run(char &index);

private:
  Map map_;
  ControlSnake control_snake_;
  std::vector<Coord> snake_;
  std::vector<Coord> egg_;
};

#endif // MODEL_H
