#ifndef MAP_H
#define MAP_H
#include <coord.h>
#include <vector>
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

private:
  std::vector<std::vector<int>> game_map_;
};

#endif // MAP_H
