#ifndef _SNAKE_VIEW_H
#define _SNAKE_VIEW_H

#include <coord.h>
#include <vector>
#include <string>

#include "map.h"

class ViewInterface {
public:
  ViewInterface() {}
  virtual ~ViewInterface() {};
  virtual ViewInterface& SetMap(const Map& map) = 0;
  //virtual ViewInterface& SetInfo(int sco, const std::string &infoStr) = 0;
  virtual ViewInterface& SyncRefresh(ViewInterface *view) = 0;
  virtual ViewInterface& Refresh() = 0;
  virtual ViewInterface& SetScore(int socre) = 0;
};

#endif // _SNAKE_VIEW_H
