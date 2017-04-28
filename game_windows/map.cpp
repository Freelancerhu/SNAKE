#include "map.h"

void Map::Reset_Map() {
  for (int  i = 0; i < gamemap_.size(); ++i) {
      for (int j = 0; j < gamemap_[0].size(); ++j) {
          gamemap_[i][j] = 0;
        }
    }
}

void Map::Snk_On_Map(const std::vector<coord> &snavec_) {
  for (auto z : snavec_) {
    gamemap_[z.x][z.y] = 1;
  }
}

void Map::Egg_On_Map(const std::vector<coord> &eggvec_) {
  for (auto z : eggvec_) {
    gamemap_[z.x][z.y] = 2;
  }
}

void Map::Init_Map(int x, int y) {
  for (int i = 0; i < y; ++i) {
      std::vector<int> temp;
    for (int j = 0; j < x; ++j) {
      temp.push_back(0);
    }
    gamemap_.push_back(temp);
  }
}

int Map::Map_Row() const {
  return gamemap_.size();
}

int Map::Map_column() const {
  return gamemap_[0].size();
}

int Map::Map_Val(int &x, int &y) const {
  return gamemap_[x][y];
}
