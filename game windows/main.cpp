#include <iostream>
#include <list>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <cstdlib>

// std::this_thread::sleep_for(interval - (time2 - time1)) #interface

// snake move #game_engine

// check eat egg/hit wall #game_engine

// process #game_engine

// output map/egg/snake #interface

// time1

// input check_input #input


struct coord {
  int x = 0;
  int y = 0;
  coord(int x1, int y1): x(x1), y(y1){}
};

void printMap(std::vector<coord> &A, std::vector<coord> &eggVec, int sMap[][20], int len) {
  for (auto z : A) {
    sMap[z.x][z.y] = 1;
  }
  sMap[eggVec[0].x][eggVec[0].y] = 7;
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < len; ++j) {
      std::cout << sMap[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "Length of your Snake : " << A.size() << std::endl;
}

bool controlSnake(std::vector<coord> &A, std::vector<coord> &eggVec, char index) {
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

  if (A[0].x+dx<0 || A[0].y+dy<0 ||
      A[0].x+dx>=20 || A[0].y+dy>=20)
    return false;

  for (int i = A.size() - 1; i > 0; --i) {
    A[i].x = A[i - 1].x;
    A[i].y = A[i - 1].y;
  }

  A[0].x = A[0].x + dx;
  A[0].y = A[0].y + dy;
  for (int i = 1; i < A.size(); ++i) {
      if (A[0].x == A[i].x && A[0].y == A[i].y)
          return false;
  }

  if (A[0].x == eggVec[0].x && A[0].y == eggVec[0].y) {
    eggVec.clear();
    int tempX = A.back().x, tempY = A.back().y;
    A.push_back(coord(tempX, tempY));
  }

  return true;
}

void layEgg(std::vector<coord> &snaVec, std::vector<coord> &eggVec) {
  if (eggVec.empty()){
    for (;;) {
      int vx = rand() % 19 + 0;
      int vy = rand() % 19 + 0;
      int i = 0;
      for (auto z : snaVec) {
        if (z.x == vx && z.y == vy) {
          ++i;
        }
      }
      if (i == 0) {
        eggVec.push_back(coord(vx, vy));
        return;
      }
    }
  }
}



int main() {
  srand(time(NULL));

  std::vector<coord> snaVec;
  snaVec.push_back(coord(5, 7)); // row  column
  snaVec.push_back(coord(5, 6));
  snaVec.push_back(coord(5, 5));
  snaVec.push_back(coord(5, 4));
  snaVec.push_back(coord(5, 3));

  std::vector<coord> eggVec;
  char index = 'd';
  for (;;) {
    system("cls");
    int sMap[20][20]{0};
    layEgg(snaVec, eggVec);
    printMap(snaVec, eggVec, sMap, 20);
    std::chrono::duration<double, std::milli> ms(100);
    std::this_thread::sleep_for(ms);
    if (_kbhit()) {
      char tempIndex = _getch();
      switch (tempIndex) {
        case 'w':
          if (snaVec[1].x - snaVec[0].x != -1)
            index = tempIndex;
          break;
        case 's':
          if (snaVec[1].x - snaVec[0].x != 1)
            index = tempIndex;
          break;
        case 'a':
          if (snaVec[1].y - snaVec[0].y != -1)
            index = tempIndex;
          break;
        case 'd':
          if (snaVec[1].y - snaVec[0].y != 1)
            index = tempIndex;
          break;
        default:
          ;
      }

      if (controlSnake(snaVec, eggVec, index)) {
          continue;
      } else {
          break;
      }
    } else {
      if (controlSnake(snaVec, eggVec,index)) {
          continue;
      } else {
          break;
      }
    }
  }
  std::cout << "GG" << std::endl;

  return 0;
}
