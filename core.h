#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

class Screen;
class Grid;
class GridPoint;
class TextRenderer;

class Screen {
  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint16_t windowWidth, WindowHeight;
    bool success = true;
  public:
    Screen(uint16_t WindowWidth, uint16_t WindowHeight);
    void updateWindow();

    void drawBox(Grid box);
    void drawAGridCell(SDL_Color cellColor, Grid box, GridPoint gridPoint);

    void setRendererColor(SDL_Color color);
    void clear();

    SDL_Renderer* getRederer();
    ~Screen();
};

class GridPoint {
  int16_t x, y;
  public: 
  GridPoint();
  GridPoint(int16_t x, int16_t y);
  int16_t getX();
  int16_t getY();
  void setX(int16_t x);
  void setY(int16_t y);
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
  public:
    Grid();
    Grid(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t cellSize, SDL_Color backgroundColor);
    uint16_t getWidth();
    uint16_t getHeight();
    uint16_t getX();
    uint16_t getY();
    uint16_t getCellSize();
    SDL_Color getCellColor();
    SDL_Color getBackgroundColor();
    void setX(uint16_t x);
    void setY(uint16_t y);
    void setWidth(uint16_t width);
    void setHeight(uint16_t height);
    void setCellSize(uint16_t cellSize);
    void setBackgroundColor(SDL_Color backgroundColor);
};

bool const number[][5][5] = {
  {{1,1,1,1,1}, {1,0,0,1,1}, {1,0,1,0,1}, {1,1,0,0,1}, {1,1,1,1,1}}, /*0*/
  {{0,0,1,0,0}, {0,1,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,1,1,1,0}}, /*1*/
  {{1,1,1,1,0}, {0,0,0,0,1}, {0,1,1,1,0}, {1,0,0,0,0}, {1,1,1,1,1}}, /*2*/
  {{1,1,1,1,1}, {0,0,0,0,1}, {0,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,1}}, /*3*/
  {{1,0,0,0,0}, {1,0,0,0,0}, {1,0,1,0,0}, {1,1,1,1,1}, {0,0,1,0,0}}, /*4*/
  {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,0}}, /*5*/
  {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}}, /*6*/
  {{1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,1,0}, {0,0,1,0,0}, {0,0,1,0,0}}, /*7*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}}, /*8*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*9*/
};
bool const letters[][5][5] = {
  {{1,1,1,1,1}, {1,0,0,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}}, /*a*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,0}, {1,0,0,0,1}, {1,1,1,1,1}}, /*b*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {0,1,1,1,0}, {1,0,0,0,0}, {1,1,1,1,1}}, /*c*/
  {{1,1,1,1,1}, {0,0,0,0,1}, {0,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,1}}, /*d*/
  {{1,0,0,0,0}, {1,0,0,0,0}, {1,0,1,0,0}, {1,1,1,1,1}, {0,0,1,0,0}}, /*e*/
  {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,0}}, /*f*/
  {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}}, /*g*/
  {{1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,1,0}, {0,0,1,0,0}, {0,0,1,0,0}}, /*h*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}}, /*i*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*j*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*k*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*l*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*m*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*n*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*o*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*p*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*q*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*r*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*s*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*t*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*u*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*v*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*w*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*x*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*y*/
  {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}}, /*z*/
};

void drawDigit(Screen* screen, uint8_t digit, uint16_t x, uint16_t y);
void showNumber(Screen* screen, uint16_t number, uint16_t x, uint16_t y);

#endif 
