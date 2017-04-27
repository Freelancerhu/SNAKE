#include "view.h"

static void View::PrintMap(const Map &map) {
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
