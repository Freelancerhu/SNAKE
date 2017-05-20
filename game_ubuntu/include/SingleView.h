#ifndef _SNAKE_SINGLE_VIEW_H
#define _SNAKE_SINGLE_VIEW_H
#include "ViewInterface.h"
#include <string>
#include <coord.h>
#include "map.h"
#include <vector>
#include "cursor.h"
class SingleView : public ViewInterface {
 public:
  explicit SingleView(const Coord &crd);
  
  SingleView(const SingleView &single_view) = delete;
  SingleView(SingleView &&single_view) = default;

  ~SingleView();
  
  SingleView &operator=(const SingleView &single_view) = delete;
  SingleView &operator=(SingleView &&single_view) = delete;

  ViewInterface &SetMap(const Map &map) override;

  //View& SetInfo(int sco, const std::string &infoStr);

  ViewInterface &SyncRefresh(ViewInterface *view) override;

  ViewInterface &Refresh() override;

  ViewInterface &SetScore(int score) override;

 private:
  void PrintMap();
  
  std::vector<std::vector<int>> single_view_map_;
  Coord coord_;
  ViewInterface *player_view_ = nullptr;
  int score_ = 0;
};

#endif // _SNAKE_SINGLE_VIEW_H
