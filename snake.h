#ifndef SNAKE_H
#define SNAKE_H

#include "core.h"
#include "colors.h"
#include <cstdint>
#include <string>
#include <vector>

const uint16_t WINDOW_WIDTH = 1200;
const uint16_t WINDOW_HEIGHT = 640;

const SDL_Color GRID_BACKGROUND_COLOR = BACKGROUND;

const SDL_Color SNAKE_COLOR = FOREGROUND;

const uint16_t CELL_SIZE = 24; /*in pixel*/

enum SnakeState {
  GOING_UP,
  GOING_DOWN,
  GOING_LEFT,
  GOING_RIGHT,
  DEAD
};

class Snake;
class Food;
class Draw;

class Draw {
    Screen* screen = nullptr;
  public:
    Draw(Screen *screen);
    void drawSnake(Grid box, Snake snake);
    void clearSnake(Grid box, Snake snake);

    void drawFood(Grid box, Food food);
    void clearFood(Grid box, Food food);

    Screen* getScreen();
};

class Food {
  GridPoint position;
  SDL_Color color;
  public:
  Food();
  Food(GridPoint p, SDL_Color color);
  void generate(Grid box);
  GridPoint getPosition();
  bool isGeneratedInsideSnake(Snake &snake);
  SDL_Color getColor();
  void getColor(SDL_Color color);
};

class Snake {
  private:
    std::vector<GridPoint> body; // the last point is head
    SnakeState state = GOING_RIGHT;
    SDL_Color bodyColor;
    SDL_Color headColor;
    
  public:
    Snake();
    Snake(uint16_t length, GridPoint startPos, SDL_Color bodyColor, SDL_Color headColor);
    std::vector<GridPoint> getBody();
    SnakeState getState();
    void moveBodyAlong(); // move the body of the snake along the head(the last element in vector)
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool isEatingFood(Food food);
    void grow();

    bool isDead(Grid box);

    void logSnake();

    SDL_Color getBodyColor();
    SDL_Color getHeadColor();
};


#endif 
