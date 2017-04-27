#include <model.h>
// std::this_thread::sleep_for(interval - (time2 - time1)) #interface

// snake move #game_engine

// check eat egg/hit wall #game_engine

// process #game_engine

// output map/egg/snake #interface

// time1

// input check_input #input

int main() {
  srand(time(NULL));
  Model model;
  model.Set_Map(20, 20);
  model.Gene_Snake();
  char index = 'd';
  while (model.Run(index));
  std::cout << "GG" << std::endl;
  return 0;
}
