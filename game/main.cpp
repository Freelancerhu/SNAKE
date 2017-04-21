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
using namespace std;
struct coord {
    int x = 0;
    int y = 0;
    coord(int x1, int y1): x(x1), y(y1){}
};

void printMap(vector<coord> &A, vector<coord> &eggVec, int sMap[][20], int len) {
    for (auto z : A) {
        sMap[z.x][z.y] = 1;
    }
    sMap[eggVec[0].x][eggVec[0].y] = 7;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << sMap[i][j];
        }
        cout << endl;
    }
    cout << "Length of your Snake : " << A.size() << endl;
}

bool controlSnake(vector<coord> &A, vector<coord> &eggVec, char index) {
    int dx = 0, dy = 0;
    switch (index) {
        case 'w' :  if (A[0].x == 0) {
                        return false;
                    }
                    if ( A[0].y == A[1].y && A[0].x > A[1].x) { //snake in this column
                        return true;
                    }
                    --dx;
                    break;
        case 's' : if (A[0].x == 19) {
                        return false;
                    }
                    if ( A[0].y == A[1].y && A[0].x < A[1].x) { //snake in this column
                        return true;
                    }
                    ++dx;
                    break;
        case 'a' : if (A[0].y == 0) {
                        return false;
                    }
                    if ( A[0].x == A[1].x && A[0].y > A[1].y) { //snake in this column
                        return true;
                    }
                    --dy;
                    break;
        case 'd' :  if (A[0].y == 19) {
                        return false;
                    }
                    if ( A[0].x == A[1].x && A[0].y < A[1].y) { //snake in this column
                        return true;
                    }
                    ++dy;
                    break;
    }
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

void layEgg(vector<coord> &snaVec, vector<coord> &eggVec) {
    if (eggVec.empty()){
        for (;;) {
            srand (time(NULL));
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
    vector<coord> snaVec;
    snaVec.push_back(coord(5, 7)); // row  column
    snaVec.push_back(coord(5, 6));
    snaVec.push_back(coord(5, 5));
    snaVec.push_back(coord(5, 4));
    snaVec.push_back(coord(5, 3));

    vector<coord> eggVec;
    char index = 'd';
    for (;;) {
        system("cls");
        int sMap[20][20]{0};
        layEgg(snaVec, eggVec);
        printMap(snaVec, eggVec, sMap, 20);
        std::chrono::duration<double, std::milli> ms(300);
        std::this_thread::sleep_for(ms);
        if (_kbhit())
        {
            char tempIndex = _getch();
            switch (tempIndex) {
                case 'w': if (snaVec[1].x - snaVec[0].x != -1)
                            index = tempIndex;
                          break;
                case 's': if (snaVec[1].x - snaVec[0].x != 1)
                            index = tempIndex;
                          break;
                case 'a':if (snaVec[1].y - snaVec[0].y != -1)
                            index = tempIndex;
                          break;
                case 'd':if (snaVec[1].y - snaVec[0].y != 1)
                            index = tempIndex;
                          break;
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
    cout << "GG" << endl;







    return 0;
}
