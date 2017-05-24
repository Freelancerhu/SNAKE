#include "map.h"

#include <cstddef>

#include <fstream>
#include <sstream>

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

std::vector<std::vector<int>> Map::CopyMap() const {
  return game_map_;
}

std::string Map::Serialize() const {
  std::ostringstream format;
  format << 'M' << game_map_.size() << ' ';
  for (auto &row : game_map_) {
    format << row.size() << ' ';
    for (auto ele : row)
      format << ele << ' ';
  }
  format << 'E';
  return format.str();
}

void Map::Deserialize(const std::string &str) {
  std::vector<std::vector<int>> temp_map;
  
  std::istringstream format(str);
  if(format.get() != 'M')
    throw std::runtime_error("Deserialize map failed, code 1");
  
  int rows = 0;
  format >> rows;
  temp_map.resize(rows);

  for (auto &row : temp_map) {
    int cols = 0;
    format >> cols;
    row.resize(cols);
    
    for (auto &ele : row)
      format >> ele;
  }
  
  if (!format)
    throw std::runtime_error("Deserialize map failed, code 2");
  game_map_ = std::move(temp_map);
}