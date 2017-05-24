#include <cstdlib>

#include <cursor.h>
#include <model.h>

int main() {
  srand(time(NULL));

  Model model;
  model.SetMap(20, 20);
  model.GeneSnake();

  char index = 'd';
  model.Run(index);
  Cursor::Get().InsertCh('g');
  Cursor::Get().InsertCh('g');
  Cursor::Get().Refresh();
  return 0;
}
