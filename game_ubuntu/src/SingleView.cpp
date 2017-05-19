#include "SingleView.h"
#include <iostream>
//ingleView::SingleView() {}

SingleView::SingleView(Coord &crd_) {
  coord_ = crd_;
}

SingleView::~SingleView() {};

View& SingleView::SetMap(const Map& map_) {
  single_view_map_ = map_.CopyMap();
  return *this;
}

//View& SingleView::SetInfo(int sco, std::string &infoStr) {
//  return *this;
//}

View& SingleView::SyncRefresh(View *view_) {
  player_view_ = view_;
  return *this;
}

View& SingleView::Refresh() {
  Cursor::Get().Refresh();
  if (player_view_ != nullptr) {
    player_view_->Refresh();
  }
  return *this;
}

void SingleView::SetScore(const int &player_score_) {
  score_ = player_score_;
}

void SingleView::PrintMap() {
	//Cursor::Get().Clear();
	char STR[] = "length of your snake : ";
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
	Cursor::Get().InsertStringAt(row, coord_.y, STR);
	Cursor::Get().InsertChAt(row, coord_.y + 24, score_+ '0');
  this->Refresh();
}
