#ifndef _SNAKEMAP_H
#define _SNAKEMAP_H

#include <vector>

#include "coord.h"

class Map {
public:
  Map();

  ~Map();

  void ResetMap();

  void SnkOnMap(const std::vector<Coord> &snavec_);

  void EggOnMap(const std::vector<Coord> &eggvec_);

  void InitMap(int x, int y);

  int MapRow() const;

  int MapColumn() const;

  int MapVal(int &x, int &y) const;

  std::vector<std::vector<int>> CopyMap() const;
private:
  std::vector<std::vector<int>> game_map_;
};

#endif // _SNAKEMAP_H
