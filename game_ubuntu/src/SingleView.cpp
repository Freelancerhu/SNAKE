#include "SingleView.h"
#include <iostream>
SingleView::SingleView() {}

SingleView::~SingleView() {};

View& SingleView::SetMap(const Map& map_) {
  if (single_view_map_.empty()) {
    for (int i = 0; i < map_.MapRow(); ++i) {
    std::vector<int> temp_;
    for (int j = 0; j < map_.MapColumn(); ++j) {
      if (map_.MapVal(i, j) == 0)
        temp_.push_back(0);
      else if (map_.MapVal(i, j) == 1)
        temp_.push_back(1);
      else
        temp_.push_back(2);
      }
      single_view_map_.push_back(temp_);
    }
  } else {
    for (int i = 0; i < map_.MapRow(); ++i) {
      for (int j = 0; j < map_.MapColumn(); ++j) {
        if (map_.MapVal(i, j) == 0)
          single_view_map_[i][j] = 0;
        else if (map_.MapVal(i, j) == 1)
          single_view_map_[i][j] = 1;
        else
          single_view_map_[i][j] = 2;
      }
    }
  }
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

void SingleView::SetScore(const std::vector<Coord> snake_) {
  score_ = snake_.size();
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
