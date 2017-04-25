#include <curses.h>

#include <chrono>
#include <memory>
#include <thread>

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

int main(void) {
  
  Curses::Get().PoseCursor(1, 10);
  Curses::Get().InsertCh('a');
  Curses::Get().Refresh();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  

  Curses::Get().InsertCh('b');
  Curses::Get().Refresh();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  
  int ch = Curses::Get().GetInput();
  Curses::Get().InsertCh(ch);
  
  std::this_thread::sleep_for(std::chrono::seconds(1));
  
  return 0;
}

// g++ -std=c++14 main.cc -lpthread -lncurses