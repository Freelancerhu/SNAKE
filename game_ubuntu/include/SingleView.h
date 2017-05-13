#ifndef _SNAKE_SINGLE_VIEW_H
#define _SNAKE_SINGLE_VIEW_H
#include "ViewInterface.h"
#include <string>
#include <coord.h>
#include "map.h"
#include <vector>
#include "cursor.h"
class SingleView : public View{
public:
  SingleView();
  ~SingleView();
  View& SetMap(const Map& map_);
  //View& SetInfo(int sco, const std::string &infoStr);
  // View& SyncRefresh(View &)
  View& Refresh();
	
  void PrintMap();
  void SetScore(const std::vector<Coord> snake_);

private:
  std::vector<std::vector<int>> single_view_map_;
  int score_ = 0;
};

#endif // _SNAKE_SINGLE_VIEW_H
