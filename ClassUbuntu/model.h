#ifndef MODEL_H
#define MODEL_H
#include <coord.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <map.h>
#include <controlsnake.h>
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
