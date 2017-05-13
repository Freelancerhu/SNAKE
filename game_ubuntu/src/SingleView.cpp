#include "SingleView.h"
#include <iostream>
SingleView::SingleView() {}

SingleView::~SingleView() {};

View& SingleView::SetMap(const Map& map_) {
  single_view_map_ = map_.CopyMap();
  return *this;
}

//View& SingleView::SetInfo(int sco, std::string &infoStr) {
//  return *this;
//}

//virtual View& SingleView::SyncRefresh(ViewInterfave &view) {
  //if (view
//}

View& SingleView::Refresh() {
  Cursor::Get().Refresh();
  return *this;
}

void SingleView::SetScore(const int &player_score_) {
  score_ = player_score_;
}

void SingleView::PrintMap() {
	Cursor::Get().Clear();
	char STR[] = "length of your snake : ";
  int row = 0;
  for (int i = 0; i < single_view_map_.size(); ++i) {
	Cursor::Get().PoseCursor(i, 6);
    for (int j = 0; j < single_view_map_[0].size(); ++j) {
      if (single_view_map_[i][j] == 0)
        Cursor::Get().InsertCh('.');
      else if (single_view_map_[i][j] == 1)
        Cursor::Get().InsertCh('#');
      else
        Cursor::Get().InsertCh('@');
    }
    Cursor::Get().InsertCh('\n');
    row = i;
  }
  ++row;
	Cursor::Get().InsertStringAt(row, 6, STR);
	Cursor::Get().InsertChAt(row, 30, score_+ '0');
  this->Refresh();
}
