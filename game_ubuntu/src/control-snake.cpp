#include "control-snake.h"

bool ControlSnake::Control(std::vector<Coord> &snake, std::vector<Coord> &egg,
                           char index) {
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
  if (snake[0].x+dx<0 || snake[0].y+dy<0 ||
      snake[0].x+dx>=20 || snake[0].y+dy>=20)
    return false;

  for (int i = snake.size() - 1; i > 0; --i) {
    snake[i].x = snake[i - 1].x;
    snake[i].y = snake[i - 1].y;
  }
  snake[0].x = snake[0].x + dx;
  snake[0].y = snake[0].y + dy;
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        return false;
  }

  if (snake[0].x == egg[0].x && snake[0].y == egg[0].y) {
    egg.clear();
    int temp_x = snake.back().x, temp_y = snake.back().y;
    snake.push_back(Coord(temp_x, temp_y));
  }
  return true;
}
