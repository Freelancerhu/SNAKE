#ifndef _SNAKE_CURSOR_H
#define _SNAKE_CURSOR_H

#include <curses.h>

#include <memory>

class Cursor {
 public:
  static Cursor &Get();

  ~Cursor();

  int PoseCursor(int row, int col);

  int InsertCh(int ch);

  int InsertChAt(int row, int col, int ch);
  
  int InsertStringAt(int row, int col, const char *str);

  int GetInput();

  int WaitForInput();

  int Clear();

  int Refresh();

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

#endif // _SNAKE_CURSOR_H
