#ifndef _SNAKE_SINGLE_VIEW_H
#define _SNAKE_SINGLE_VIEW_H
#include "ViewInterface.h"
#include <string>
#include <coord.h>
#include "map.h"
#include <vector>
#include "cursor.h"
class SingleView : public View{
public://SingleView();  

  SingleView(Coord &crd_);

  ~SingleView();

  View& SetMap(const Map& map_);

  //View& SetInfo(int sco, const std::string &infoStr);

  View& SyncRefresh(View *view_);

  View& Refresh();
	
  void PrintMap();

  void SetScore(const int &player_score_);

  SingleView(const SingleView &single_view_) = delete;

  SingleView(SingleView &&single_view_) = default;

  SingleView &operator=(const SingleView &single_view_) = delete;

  SingleView &operator=(SingleView &&single_view_) = delete;

private:
  std::vector<std::vector<int>> single_view_map_;
  Coord coord_;
  View *player_view_ = nullptr;
  int score_ = 0;
};

#endif // _SNAKE_SINGLE_VIEW_H
