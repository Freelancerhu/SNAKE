#include "SingleView.h"

#include <sstream>

SingleView::SingleView(const Coord &crd) {
  coord_ = crd;
}

SingleView::~SingleView() {};

ViewInterface &SingleView::SetMap(const Map &map) {
  single_view_map_ = map.CopyMap();
  return *this;
}

//View& SingleView::SetInfo(int sco, std::string &infoStr) {
//  return *this;
//}

ViewInterface &SingleView::SyncRefresh(ViewInterface *view) {
  if (player_view_ != view) {
    player_view_ = view;
    player_view_->SyncRefresh(this);
  }
  return *this;
}

template <class T>
class TempSwitch {
 public:
  TempSwitch(T &var, const T &val) : var_(var), temp_(var) {
    var = val;
  }
  
  T &Get() {
    return temp_;
  }
  
  const T &Get() const {
    return temp_;
  }
  
  ~TempSwitch() {
    var_ = temp_;
  }
  
 private:
  T &var_;
  T temp_;
};

ViewInterface &SingleView::Refresh() {
  PrintMap();

  if (player_view_ != nullptr) {
    TempSwitch<ViewInterface *> guard(player_view_, nullptr);
    guard.Get()->Refresh();
  }
  
  return *this;
}

ViewInterface &SingleView::SetScore(int score) {
  score_ = score;
}

void SingleView::PrintMap() {
  int row = 0;
  for (int i = 0; i < single_view_map_.size(); ++i) {
	Cursor::Get().PoseCursor(i + coord_.x, coord_.y);
    for (int j = 0; j < single_view_map_[0].size(); ++j) {
      if (single_view_map_[i][j] == 0)
        Cursor::Get().InsertCh('.');
      else if (single_view_map_[i][j] == 1)
        Cursor::Get().InsertCh('#');
      else
        Cursor::Get().InsertCh('@');
    }
    Cursor::Get().InsertCh('\n');
    row = i + coord_.x;
  }
  ++row;
	Cursor::Get().InsertStringAt(row, coord_.y, "length of your snake : ");
  
  std::ostringstream format;
  format << score_;
	Cursor::Get().InsertStringAt(row, coord_.y + 24, format.str().c_str());
  Cursor::Get().InsertCh('\n');
  Cursor::Get().Refresh();
}
