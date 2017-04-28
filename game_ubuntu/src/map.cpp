#include "map.h"

#include <cstddef>

Map::Map() {}

Map::~Map() = default;

void Map::ResetMap() {
  for (size_t i = 0; i < game_map_.size(); ++i) {
    for (size_t j = 0; j < game_map_[0].size(); ++j) {
        game_map_[i][j] = 0;
      }
  }
}

void Map::SnkOnMap(const std::vector<Coord> &snavec_) {
  for (auto z : snavec_) {
    game_map_[z.x][z.y] = 1;
  }
}

void Map::EggOnMap(const std::vector<Coord> &eggvec_) {
  for (auto z : eggvec_) {
    game_map_[z.x][z.y] = 2;
  }
}

void Map::InitMap(int x, int y) {
  for (int i = 0; i < y; ++i) {
      std::vector<int> temp;
    for (int j = 0; j < x; ++j) {
      temp.push_back(0);
    }
    game_map_.push_back(temp);
  }
}

int Map::MapRow() const {
  return game_map_.size();
}

int Map::MapColumn() const {
  return game_map_[0].size();
}

int Map::MapVal(int &x, int &y) const {
  return game_map_[x][y];
}