#include "model.h"



Model::~Model() {
  snavec_.clear();
  eggvec_.clear();
}

  void Model::Gene_Snake() {
    snavec_.push_back(coord(5, 7));
    snavec_.push_back(coord(5, 6));
    snavec_.push_back(coord(5, 5));
    snavec_.push_back(coord(5, 4));
    snavec_.push_back(coord(5, 3));
    map_.Snk_On_Map(snavec_);
  }
  void Model::Gene_Egg() {
    if (eggvec_.empty()){
      for (;;) {
        int vx = rand() % 19 + 0;
        int vy = rand() % 19 + 0;
        int i = 0;
        for (auto z : snavec_) {
          if (z.x == vx && z.y == vy) {
            ++i;
          }
        }
        if (i == 0) {
          eggvec_.push_back(coord(vx, vy));
          map_.Egg_On_Map(eggvec_);
          return;
        }
      }
    }
  }

  void Model::Set_Map(int x, int y) {
    map_.Init_Map(x, y);
  }

  bool Model::Run(char &index) {
    system("cls");
    Gene_Egg();
    map_.Reset_Map();
    map_.Snk_On_Map(snavec_);
    map_.Egg_On_Map(eggvec_);
    printmap_.Print_Map(map_);
    std::cout << "Length of your Snake : " << snavec_.size() << std::endl;
    std::chrono::duration<double, std::milli> ms(100);
    std::this_thread::sleep_for(ms);
    if (_kbhit()) {
      char tempIndex = _getch();
      switch (tempIndex) {
        case 'w':
          if (snavec_[1].x - snavec_[0].x != -1)
            index = tempIndex;
          break;
        case 's':
          if (snavec_[1].x - snavec_[0].x != 1)
            index = tempIndex;
          break;
        case 'a':
          if (snavec_[1].y - snavec_[0].y != -1)
            index = tempIndex;
          break;
        case 'd':
          if (snavec_[1].y - snavec_[0].y != 1)
            index = tempIndex;
          break;
        default:
          ;
      }
      if (controlsnake_.Control_Snake(snavec_, eggvec_, index)) {
          return true;
      } else {
          return false;
      }
    } else {
      if (controlsnake_.Control_Snake(snavec_, eggvec_, index)) {
          return true;
      } else {
          return false;
      }
    }
  }
