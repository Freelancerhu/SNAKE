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

class Cursor {
 public:
  static Cursor &Get() {
    if (cursor == nullptr)
      cursor.reset(new Cursor());
    return *cursor.get();
  }
  
  ~Cursor() {
    delwin(main_window_);
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
  Cursor() {
    if (main_window_ == nullptr)
      throw std::runtime_error("initsrc failed");
  }
  
  Cursor(const Cursor &) = delete;
  Cursor(Cursor &&) = delete;
  
  Cursor &operator=(const Cursor &) = delete;
  Cursor &operator==(Cursor &&) = delete;
  
  WINDOW *main_window_ = initscr();
  bool no_delay_ = false;
  
  static std::unique_ptr<Cursor> cursor;
};

std::unique_ptr<Cursor> Cursor::cursor{nullptr};

// The body of game
struct Coord {
  int x = 0;
  int y = 0;
  Coord(int x1, int y1): x(x1), y(y1){}
};


class Map {
public:
  Map() {}

  ~Map() {
    game_map_.clear();
  }

  void ResetMap() {
    for (size_t  i = 0; i < game_map_.size(); ++i) {
        for (size_t j = 0; j < game_map_[0].size(); ++j) {
            game_map_[i][j] = 0;
          }
      }
  }

  void SnkOnMap(const std::vector<Coord> &snavec_) {
    for (auto z : snavec_) {
      game_map_[z.x][z.y] = 1;
    }
  }

  void EggOnMap(const std::vector<Coord> &eggvec_) {
    for (auto z : eggvec_) {
      game_map_[z.x][z.y] = 2;
    }
  }

  void InitMap(int x, int y) {
    for (int i = 0; i < y; ++i) {
        std::vector<int> temp;
      for (int j = 0; j < x; ++j) {
        temp.push_back(0);
      }
      game_map_.push_back(temp);
    }
  }

  int MapRow() const {
    return game_map_.size();
  }

  int MapColumn() const {
    return game_map_[0].size();
  }

  int MapVal(int &x, int &y) const {
    return game_map_[x][y];
  }

private:
  std::vector<std::vector<int>> game_map_;
};

class View {
public:
  static void PrintMap(const Map &map) {
		Cursor::Get().Clear();
    for (int i = 0; i < map.MapRow(); ++i) {
			Cursor::Get().PoseCursor(i, 6);
      for (int j = 0; j < map.MapColumn(); ++j) {
        if (map.MapVal(i, j) == 0)
          Cursor::Get().InsertCh('.');
        else if (map.MapVal(i, j) == 1)
          Cursor::Get().InsertCh('#');
        else
          Cursor::Get().InsertCh('@');
      }
      Cursor::Get().InsertCh('\n');
    }
		Cursor::Get().Refresh();
  }
};

class ControlSnake {
public:
  bool Control(std::vector<Coord> &snake, std::vector<Coord> &egg, char index) {
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
    if (snake[0].x+dx<0 || snake[0].y+dy<0 ||
        snake[0].x+dx>=20 || snake[0].y+dy>=20)
      return false;

    for (int i = snake.size() - 1; i > 0; --i) {
      snake[i].x = snake[i - 1].x;
      snake[i].y = snake[i - 1].y;
    }
    snake[0].x = snake[0].x + dx;
    snake[0].y = snake[0].y + dy;
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return false;
    }

    if (snake[0].x == egg[0].x && snake[0].y == egg[0].y) {
      egg.clear();
      int temp_x = snake.back().x, temp_y = snake.back().y;
      snake.push_back(Coord(temp_x, temp_y));
    }
    return true;
  }
};

class Model {
public:
  Model() = default;
  ~Model() = default;

  void GeneSnake() {
    snake_.push_back(Coord(5, 7));
    snake_.push_back(Coord(5, 6));
    snake_.push_back(Coord(5, 5));
    snake_.push_back(Coord(5, 4));
    snake_.push_back(Coord(5, 3));
    map_.SnkOnMap(snake_);
  }

  void GeneEgg() {
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

  void SetMap(int x, int y) {
    map_.InitMap(x, y);
  }

  bool Run(char &index) {
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

private:
  Map map_;
  ControlSnake control_snake_;
  std::vector<Coord> snake_;
  std::vector<Coord> egg_;
};

int main() {
  srand(time(NULL));
  
  Model model;
  model.SetMap(20, 20);
  model.GeneSnake();
  
  char index = 'd';
  while (model.Run(index));
  
  Cursor::Get().Clear();
  Cursor::Get().InsertCh('g');
  Cursor::Get().InsertCh('g');
  Cursor::Get().Refresh();
  return 0;
}
