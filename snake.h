#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include "colors.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const uint16_t WINDOW_WIDTH = 1200;
const uint16_t WINDOW_HEIGHT = 640;

const SDL_Color GRID_BACKGROUND_COLOR = BACKGROUND;
const SDL_Color GRID_BORDER_COLOR = FOREGROUND;

const SDL_Color SNAKE_COLOR = FOREGROUND;

const uint16_t CELL_SIZE = 24; /*in pixel*/

enum SnakeState {
  GOING_UP,
  GOING_DOWN,
  GOING_LEFT,
  GOING_RIGHT,
  DEAD
};

class GridPoint {
  uint16_t x, y;
  public: 
  GridPoint();
  GridPoint(uint16_t x, uint16_t y);
  uint16_t getX();
  uint16_t getY();
  void setX(uint16_t x);
  void setY(uint16_t y);
  GridPoint& operator=(const GridPoint& p);
  bool operator==(const GridPoint& p) ;
};
class Grid {
  private:
    uint16_t x, y; // position in the root renderer
    uint16_t width; /*in cell unit*/
    uint16_t height; /*in cell unit*/
    uint16_t cellSize; /*in pixel*/
    SDL_Color backgroundColor;
    SDL_Color borderColor;
  public:
    Grid(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t cellSize, SDL_Color backgroundColor);
    uint16_t getWidth();
    uint16_t getHeight();
    uint16_t getX();
    uint16_t getY();
    uint16_t getCellSize();
    SDL_Color getBackgroundColor();
};

class Snake;
class Food {
  GridPoint Position;
  public:
  Food();
  Food(GridPoint p);
  void generate(Grid box);
  GridPoint getPosition();
  bool isGeneratedInsideSnake(Snake &snake);
};

class Snake {
  private:
    std::vector<GridPoint> body; // the last point is head
    SnakeState state = GOING_RIGHT;
  public:
    Snake();
    Snake(uint16_t length, GridPoint startPos);
    std::vector<GridPoint> getBody();
    SnakeState getState();
    void moveBodyAlong(); // move the body of the snake along the head(the last element in vector)
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool isEatingFood(Food food);
    void grow();
};

class Screen {
  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool success = true;
  public:
    Screen();
    void updateWindow();

    void drawBox(Grid box);
    void drawAGridCell(SDL_Color color, Grid box, GridPoint gridPoint);

    void drawSnake(Grid box, Snake snake);
    void clearSnake(Grid box, Snake snake);

    void drawFood(Grid box, Food food);
    void clearFood(Grid box, Food food);

    void setRendererColor(SDL_Color color);
    void clear();
    ~Screen();
};

#endif 
