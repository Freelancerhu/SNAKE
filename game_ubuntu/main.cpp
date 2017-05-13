#include <cstdlib>

#include <cursor.h>
#include <model.h>

int main() {
  srand(time(NULL));

  Model model;
  model.SetMap(20, 20);
  model.GeneSnake();

  char index = 'd';
  while (model.Run(index));
  //Cursor::Get().Clear();
  Cursor::Get().InsertCh('g');
  Cursor::Get().InsertCh('g');
  Cursor::Get().Refresh();
  return 0;
}
