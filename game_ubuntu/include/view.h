#ifndef _SNAKE_VIEW_H
#define VIEW_H
#include <coord.h>
#include <vector>
class Map;

class View {
public:
  static void PrintMap(const Map &map);
	static void PrintMapSplit(const Map &map1,const std::vector<Coord> snake_1, const Map &map2, const std::vector<Coord> snake_2);
};

#endif // _SNAKE_VIEW_H
