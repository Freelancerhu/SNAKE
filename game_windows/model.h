#ifndef MODEL_H
#define MODEL_H
#include <coord.h>
#include <map.h>
#include <controlsnake.h>
#include <printmap.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <coord.h>

class Model {
public:
  Model() {}
  ~Model();
  void Gene_Snake();
  void Gene_Egg();

  void Set_Map(int x, int y);

  bool Run(char &index);

private:
  Map map_;
  printMap printmap_;
  controlSnake controlsnake_;
  std::vector<coord> snavec_;
  std::vector<coord> eggvec_;
};
#endif // MODEL_H
