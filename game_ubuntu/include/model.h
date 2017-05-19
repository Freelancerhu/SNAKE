#ifndef _SNAKEMODEL_H
#define _SNAKEMODEL_H

#include <cstdlib>

#include <vector>

#include "map.h"
#include "control-snake.h"
#include "coord.h"
#include "ViewInterface.h"
#include "SingleView.h"

class Model {
public:
  Model() = default;
  ~Model() = default;

  void GeneSnake();

  void GeneEgg();

  void SetMap(int x, int y);
  
  int PlayerScore();

  bool Run(char &index);

  void SetCoord(int x, int y);
private:
  Map map_;
  Coord coord_;
  ControlSnake control_snake_;
  std::vector<Coord> snake_;
  std::vector<Coord> egg_;
};

#endif // MODEL_H
