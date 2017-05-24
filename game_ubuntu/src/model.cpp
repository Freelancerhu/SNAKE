
#include "model.h"

#include <cassert>

#include <iostream>
#include <memory>
#include <thread>

#include "cursor.h"


void Model::GeneSnake() {
  snake_.push_back(Coord(5, 7));
  snake_.push_back(Coord(5, 6));
  snake_.push_back(Coord(5, 5));
  snake_.push_back(Coord(5, 4));
  snake_.push_back(Coord(5, 3));
  map_.SnkOnMap(snake_);
}

void Model::GeneEgg() {
  if (egg_.empty()){
    for (;;) {
      int vx = rand() % 19 + 0;
      int vy = rand() % 19 + 0;
      int i = 0;
      for (auto z : snake_) {
        if (z.x == vx && z.y == vy) {
          ++i;
        }
      }
      if (i == 0) {
        egg_.push_back(Coord(vx, vy));
        map_.EggOnMap(egg_);
        return;
      }
    }
  }
}

void Model::SetMap(int x, int y) {
  map_.InitMap(x, y);
}

int Model::PlayerScore() {
  return snake_.size();
}

void Model::SetCoord(int x, int y) {
  coord_.x = x;
  coord_.y = y;
}

using TwoViews = std::pair<std::unique_ptr<ViewInterface>,
                           std::unique_ptr<ViewInterface> >;


TwoViews InitTwoView() {
  auto view1 = std::make_unique<SingleView>(Coord(0, 0));
  auto view2 = std::make_unique<SingleView>(Coord(0, 40));
  
  view1->SyncRefresh(view2.get());
  return {std::move(view1), std::move(view2)};
}

void SetViews(TwoViews &views, const Map &map1, const Map &map2, int score1,
              int score2) {
  views.first->SetScore(score1).SetMap(map1);
  views.second->SetScore(score2).SetMap(map2).Refresh();
}

void Model::Run(char &index) {
  auto views = InitTwoView();
  
  Map peer_map;
  peer_map.InitMap(20, 20);
  
  c_1_.ConnectToServer("127.0.0.1");
  
  Connection::ListType list;

  for (;;) {
    GeneEgg();
    map_.ResetMap();
    map_.SnkOnMap(snake_);
    map_.EggOnMap(egg_);

    c_1_.SendMap(map_);
    c_1_.ReceiveMaps(list);
    //assert(list.size() == 1);
    if (!list.empty())
      peer_map = list.back().first;
    
    SetViews(views, map_, peer_map, PlayerScore(), PlayerScore());

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    char tempIndex = Cursor::Get().GetInput();
    switch (tempIndex) {
      case 'w':
        if (snake_[1].x - snake_[0].x != -1)
          index = tempIndex;
        break;
      case 's':
        if (snake_[1].x - snake_[0].x != 1)
          index = tempIndex;
        break;
      case 'a':
        if (snake_[1].y - snake_[0].y != -1)
          index = tempIndex;
        break;
      case 'd':
        if (snake_[1].y - snake_[0].y != 1)
          index = tempIndex;
        break;
      default:
        ;
    }
    if (control_snake_.Control(snake_, egg_, index) == false)
      break;
  }
}
