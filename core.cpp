#include "core.h"
#include <SDL2/SDL.h>

Screen::Screen(uint16_t WindowWidth, uint16_t WindowHeight) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow("Snake game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
      printf("Window could not initialize! SDL_Error: SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if(renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error(): %s\n", SDL_GetError());
        success = false;
      }
    }
  }
}
Screen::~Screen() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
void Screen::setRendererColor(SDL_Color color) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}
void Screen::updateWindow() {
  if(success == false) {
    printf("Fail to initialize screen!");
    return;
  }
  SDL_RenderPresent(renderer);
}
void Screen::drawBox(Grid box) {
  // draw the outline
  this->setRendererColor((SDL_Color){0xFF, 0xFF, 0xFF});
  SDL_Rect outlineRect = {-1 + box.getX(), -1 + box.getY(), 
    box.getWidth() * box.getCellSize() + 2, box.getHeight() * box.getCellSize() + 2};
  SDL_RenderDrawRect(renderer, &outlineRect);

  // fill the box
  this->setRendererColor(box.getBackgroundColor());
  SDL_Rect fillRect = {box.getX(), box.getY(),
    box.getWidth() * box.getCellSize(), box.getHeight() * box.getCellSize()};
  SDL_RenderFillRect(renderer, &fillRect);
}
void Screen::drawAGridCell(SDL_Color color, Grid box, GridPoint gridPoint) {
  if(box.getWidth() <= gridPoint.getX() || box.getHeight() <= gridPoint.getY()) return; // ??
  SDL_Rect squarePoint = {box.getX() + gridPoint.getX() * box.getCellSize(), box.getY() + gridPoint.getY() * box.getCellSize(),
    box.getCellSize(), box.getCellSize()};
  this->setRendererColor(color);
  SDL_RenderFillRect(renderer, &squarePoint);
}

GridPoint::GridPoint(uint16_t x, uint16_t y) { this->x = x; this->y = y;}
GridPoint::GridPoint() {}
uint16_t GridPoint::getX() { return this->x; }
uint16_t GridPoint::getY() { return this->y; }
void GridPoint::setX(uint16_t x) { this->x = x; }
void GridPoint::setY(uint16_t y) { this->y = y; }
GridPoint& GridPoint::operator=(const GridPoint& p) {
  x = p.x;
  y = p.y;
  return *this;
}
bool GridPoint::operator==(const GridPoint& p) {
  return this->x == p.x && this->y == p.y;
}

Grid::Grid(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t cellSize, SDL_Color backgroundColor) {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      this->cellSize = cellSize;
      this->backgroundColor = backgroundColor;
}

uint16_t Grid::getWidth() { return width;}
uint16_t Grid::getHeight() { return height;}
uint16_t Grid::getX() { return x;}
uint16_t Grid::getY() { return y;}
uint16_t Grid::getCellSize() { return cellSize;}
SDL_Color Grid::getBackgroundColor() { return backgroundColor;}
