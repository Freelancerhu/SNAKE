#include "view.h"
#include "cursor.h"
#include "map.h"
void View::PrintMap(const Map &map) {
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

void View::PrintMapSplit(const Map &map1,const std::vector<Coord> snake_1, const Map &map2, const std::vector<Coord> snake_2) {
	char STR[] = "length of your snake : ";
	int row = 0;
	Cursor::Get().Clear();
  for (int i = 0; i < map1.MapRow(); ++i) {
	Cursor::Get().PoseCursor(i, 6);
    for (int j = 0; j < map1.MapColumn(); ++j) {
      if (map1.MapVal(i, j) == 0)
        Cursor::Get().InsertCh('.');
      else if (map1.MapVal(i, j) == 1)
        Cursor::Get().InsertCh('#');
      else
        Cursor::Get().InsertCh('@');
    }
    Cursor::Get().InsertCh('\n');
		row = i;
  }
	Cursor::Get().InsertStringAt(row, 6, STR);
	Cursor::Get().InsertChAt(row, 30, snake_1.size() + '0');
	for (int i = 0; i < map2.MapRow(); ++i) {
	Cursor::Get().PoseCursor(i, 60);
    for (int j = 0; j < map2.MapColumn(); ++j) {
      if (map2.MapVal(i, j) == 0)
        Cursor::Get().InsertCh('.');
      else if (map2.MapVal(i, j) == 1)
        Cursor::Get().InsertCh('#');
      else
        Cursor::Get().InsertCh('@');
    }
    Cursor::Get().InsertCh('\n');
		row = i;
  }
  Cursor::Get().InsertStringAt(row, 60, STR);
	Cursor::Get().InsertChAt(row, 84, snake_1.size() + '0');
	Cursor::Get().Refresh();
}
