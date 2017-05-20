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
  player_view_ = view;
  return *this;
}

ViewInterface &SingleView::Refresh() {
  PrintMap();

  if (player_view_ != nullptr) {
    auto temp = player_view_;
    player_view_ = nullptr;
    temp->Refresh();
    player_view_ = temp;
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
