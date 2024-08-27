#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
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
    void drawAGridCell(SDL_Color color, Grid box, GridPoint gridPoint);

    void setRendererColor(SDL_Color color);
    void clear();

    ~Screen();
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

class TextRenderer {
    TTF_Font* font = TTF_OpenFont("./retro_gaming.ttf", 24);
    SDL_Color fontColor = {0xFF, 0xFF, 0xFF};
    std::string message;
    SDL_Surface* surfaceMessage;
    SDL_Texture* texttureMessage;
    SDL_Rect* rect;
  public:
    TextRenderer(Screen& screen);
    ~TextRenderer();
    void setFont(std::string fontFile, uint8_t fontSize);
    void setMessage(std::string Msg);
};
#endif 
