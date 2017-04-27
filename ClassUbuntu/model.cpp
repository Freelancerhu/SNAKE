#include "model.h"


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

bool Model::Run(char &index) {
  GeneEgg();
  map_.ResetMap();
  map_.SnkOnMap(snake_);
  map_.EggOnMap(egg_);
  View::PrintMap(map_);
  Cursor::Get().InsertCh('\n');
  std::cout << "Length of your Snake : " << snake_.size() << std::endl;
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

