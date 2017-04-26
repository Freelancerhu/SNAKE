#include <iostream>
#include <list>
#include <vector>
#include <curses.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <memory>

// std::this_thread::sleep_for(interval - (time2 - time1)) #interface

// snake move #game_engine

// check eat egg/hit wall #game_engine

// process #game_engine

// output map/egg/snake #interface

// time1

// input check_input #input

// A simple curses class (singleton)

class Curses {
 public:
  static Curses &Get() {
    if (curses == nullptr)
      curses.reset(new Curses());
    return *curses.get();
  }
  
  ~Curses() {
    delwin(mainwin_);
    endwin();
    refresh();
  }
  
  int PoseCursor(int row, int col) {
    return move(row, col);
  }
  
  int InsertCh(int ch) {
    return addch(ch);
  }
  
  int InsertChAt(int row, int col, int ch) {;
    return mvaddch(row, col, ch);
  }

  int GetInput() {
    if (no_delay_ == false) {
      nodelay(stdscr, true);
      no_delay_ = true;
    }
    return getch();
  }
  
  int WaitForInput() {
    if (no_delay_ == true) {
      nodelay(stdscr, false);
      no_delay_ = false;
    }
    return getch();
  }
  
  int Clear() {
    clear();
  }
  
  int Refresh() {
    return refresh();
  }
  
 private:
  Curses() {
    if (mainwin_ == nullptr)
      throw std::runtime_error("initsrc failed");
  }
  
  Curses(const Curses &) = delete;
  Curses(Curses &&) = delete;
  
  Curses &operator=(const Curses &) = delete;
  Curses &operator==(Curses &&) = delete;
  
  WINDOW *mainwin_ = initscr();
  bool no_delay_ = false;
  
  static std::unique_ptr<Curses> curses;
};

std::unique_ptr<Curses> Curses::curses{nullptr};

// The body of game
struct coord {
  int x = 0;
  int y = 0;
  coord(int x1, int y1): x(x1), y(y1){}
};


class Map {
public:
  Map() {}

  ~Map() {
    gamemap_.clear();
  }

  void Reset_Map() {
    for (size_t  i = 0; i < gamemap_.size(); ++i) {
        for (size_t j = 0; j < gamemap_[0].size(); ++j) {
            gamemap_[i][j] = 0;
          }
      }
  }

  void Snk_On_Map(const std::vector<coord> &snavec_) {
    for (auto z : snavec_) {
      gamemap_[z.x][z.y] = 1;
    }
  }

  void Egg_On_Map(const std::vector<coord> &eggvec_) {
    for (auto z : eggvec_) {
      gamemap_[z.x][z.y] = 2;
    }
  }

  void Init_Map(int x, int y) {
    for (int i = 0; i < y; ++i) {
        std::vector<int> temp;
      for (int j = 0; j < x; ++j) {
        temp.push_back(0);
      }
      gamemap_.push_back(temp);
    }
  }

  int Map_Row() const {
    return gamemap_.size();
  }

  int Map_column() const {
    return gamemap_[0].size();
  }

  int Map_Val(int &x, int &y) const {
    return gamemap_[x][y];
  }

private:
  std::vector<std::vector<int>> gamemap_;
};

class printMap {
public:
  void Print_Map(const Map &map) {
		Curses::Get().Clear();
    for (int i = 0; i < map.Map_Row(); ++i) {
			Curses::Get().PoseCursor(i, 6);
      for (int j = 0; j < map.Map_column(); ++j) {
        if (map.Map_Val(i, j) == 0)
          Curses::Get().InsertCh('.');
        else if (map.Map_Val(i, j) == 1)
          Curses::Get().InsertCh('#');
        else
          Curses::Get().InsertCh('@');
      }
      Curses::Get().InsertCh('\n');
    }
		Curses::Get().Refresh();
  }
};

class controlSnake {
public:
  bool Control_Snake(std::vector<coord> &A, std::vector<coord> &eggVec, char index) {
    int dx = 0, dy = 0;
    static int delta[][2] = {
      {-1, 0},
      {1, 0},
      {0, -1},
      {0, 1}};
    int direction = 0;
    switch (index) {
      case 'w':
        direction = 0;
        break;
      case 's':
        direction = 1;
        break;
      case 'a':
        direction = 2;
        break;
      case 'd':
        direction = 3;
        break;
      default:
        ;
    }
    dx = delta[direction][0];
    dy = delta[direction][1];
    if (A[0].x+dx<0 || A[0].y+dy<0 ||
        A[0].x+dx>=20 || A[0].y+dy>=20)
      return false;

    for (int i = A.size() - 1; i > 0; --i) {
      A[i].x = A[i - 1].x;
      A[i].y = A[i - 1].y;
    }
    A[0].x = A[0].x + dx;
    A[0].y = A[0].y + dy;
    for (int i = 1; i < A.size(); ++i) {
        if (A[0].x == A[i].x && A[0].y == A[i].y)
            return false;
    }

    if (A[0].x == eggVec[0].x && A[0].y == eggVec[0].y) {
      eggVec.clear();
      int tempX = A.back().x, tempY = A.back().y;
      A.push_back(coord(tempX, tempY));
    }
    return true;
  }
};

class Model {
public:
  Model() {}
  ~Model() {
    snavec_.clear();
    eggvec_.clear();
  }

  void Gene_Snake() {
    snavec_.push_back(coord(5, 7));
    snavec_.push_back(coord(5, 6));
    snavec_.push_back(coord(5, 5));
    snavec_.push_back(coord(5, 4));
    snavec_.push_back(coord(5, 3));
    map_.Snk_On_Map(snavec_);
  }

  void Gene_Egg() {
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

  void Set_Map(int x, int y) {
    map_.Init_Map(x, y);
  }

  bool Run(char &index) {
    Gene_Egg();
    map_.Reset_Map();
    map_.Snk_On_Map(snavec_);
    map_.Egg_On_Map(eggvec_);
    printmap_.Print_Map(map_);
		Curses::Get().InsertCh('\n');
    std::cout << "Length of your Snake : " << snavec_.size() << std::endl;
    std::chrono::duration<double, std::milli> ms(100);
    std::this_thread::sleep_for(ms);
		char tempIndex = Curses::Get().GetInput();
    if (tempIndex != ERR) {
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

private:
  Map map_;
  printMap printmap_;
  controlSnake controlsnake_;
  std::vector<coord> snavec_;
  std::vector<coord> eggvec_;
};



int main() {
  srand(time(NULL));
  Model model;
  model.Set_Map(20, 20);
  model.Gene_Snake();
  char index = 'd';
  while (model.Run(index));
  Curses::Get().Clear();
  Curses::Get().InsertCh('g');
  Curses::Get().InsertCh('g');
  Curses::Get().Refresh();
  return 0;
}
