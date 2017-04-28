#ifndef MAP_H
#define MAP_H
#include <coord.h>
#include <vector>
class Map {
public:
  Map() {}

  ~Map() {
    gamemap_.clear();
  }

  void Reset_Map();

  void Snk_On_Map(const std::vector<coord> &snavec_);

  void Egg_On_Map(const std::vector<coord> &eggvec_);

  void Init_Map(int x, int y);

  int Map_Row() const;

  int Map_column() const;

  int Map_Val(int &x, int &y) const;

private:
  std::vector<std::vector<int>> gamemap_;
};
#endif // MAP_H
