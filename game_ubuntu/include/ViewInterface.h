#ifndef _SNAKE_VIEW_H
#define _SNAKE_VIEW_H
#include <coord.h>
#include <vector>
#include <string>
#include "map.h"
#include "cursor.h"

class View {
public:
  View() {}
  virtual ~View() {};
  virtual View& SetMap(const Map& map_) = 0;
  //virtual View& SetInfo(int sco, const std::string &infoStr) = 0;
  virtual View& SyncRefresh(View *view_) = 0;
  virtual View& Refresh() = 0;
  View *player_view_;
};

#endif // _SNAKE_VIEW_H
