#include "cursor.h"

std::unique_ptr<Cursor> Cursor::cursor{nullptr};

Cursor &Cursor::Get() {
  if (cursor == nullptr)
    cursor.reset(new Cursor());
  return *cursor.get();
}

Cursor::~Cursor() {
  delwin(main_window_);
  endwin();
  refresh();
}

int Cursor::PoseCursor(int row, int col) {
  return move(row, col);
}

int Cursor::InsertCh(int ch) {
  return addch(ch);
}

int Cursor::InsertChAt(int row, int col, int ch) {;
  return mvaddch(row, col, ch);
}

int InsertStringAt(int row, int col, const char *str) {
  return mvaddstr(row, col, str);
}

int Cursor::GetInput() {
  if (no_delay_ == false) {
    nodelay(stdscr, true);
    no_delay_ = true;
  }
  return getch();
}

int Cursor::WaitForInput() {
  if (no_delay_ == true) {
    nodelay(stdscr, false);
    no_delay_ = false;
  }
  return getch();
}

int Cursor::Clear() {
  clear();
}

int Cursor::Refresh() {
  return refresh();
}
