#include "printmap.h"


void printMap::Print_Map(const Map &map) {
  for (int i = 0; i < map.Map_Row(); ++i) {
    for (int j = 0; j < map.Map_column(); ++j) {
      std::cout << map.Map_Val(i, j);
    }
    std::cout << std::endl;
  }
}
