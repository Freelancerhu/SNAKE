#include "model.h"
#include <iostream>
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

bool Model::Run(char &index) {
  GeneEgg();
  map_.ResetMap();
  map_.SnkOnMap(snake_);
  map_.EggOnMap(egg_);
  SetCoord(0, 0);
  SingleView SV(coord_);
  SetCoord(0, 40);
  SingleView SV2(coord_);
  View *view = &SV;
  View *view2 = &SV2;
  view->SetMap(map_);
  view2->SetMap(map_);
  SV.SetScore(PlayerScore());
  SV2.SetScore(PlayerScore());
  SV.PrintMap();
  SV2.PrintMap();
  view->SyncRefresh(view2);
  view2->SyncRefresh(view);
  //view->Refresh();
  Cursor::Get().InsertCh('\n');
  std::chrono::duration<double, std::milli> ms(100);
  std::this_thread::sleep_for(ms);
  char tempIndex = Cursor::Get().GetInput();
  if (tempIndex != ERR) {
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
    if (control_snake_.Control(snake_, egg_, index)) {
        return true;
    } else {
        return false;
    }
  } else {
    if (control_snake_.Control(snake_, egg_, index)) {
        return true;
    } else {
        return false;
    }
  }
}
