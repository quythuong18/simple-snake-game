#include "snake.h"
#include <cstdlib>


Draw::Draw() {

}
void Draw::drawSnake(Grid box, Snake snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength - 1; i++) {
    screen->drawAGridCell(SNAKE_COLOR, box, snake.getBody()[i]);
  }
  screen->drawAGridCell(RED, box, snake.getBody()[snakeLength - 1]);
}
void Draw::clearSnake(Grid box, Snake snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength; i++) {
    screen->drawAGridCell(box.getBackgroundColor(), box, snake.getBody()[i]);
  }
}
void Draw::drawFood(Grid box, Food food) {
  screen->drawAGridCell(GREEN, box, food.getPosition());
}
void Draw::clearFood(Grid box, Food food) {
  screen->drawAGridCell(box.getBackgroundColor(), box, food.getPosition());
}
Screen* Draw::getScreen() { return screen; }

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

void Screen::drawAGridCell(SDL_Color color, Grid box, GridPoint gridPoint) {
  if(box.getWidth() <= gridPoint.getX() || box.getHeight() <= gridPoint.getY()) return; // ??
  SDL_Rect squarePoint = {box.getX() + gridPoint.getX() * box.getCellSize(), box.getY() + gridPoint.getY() * box.getCellSize(),
    box.getCellSize(), box.getCellSize()};
  this->setRendererColor(color);
  SDL_RenderFillRect(renderer, &squarePoint);
}

Food::Food(GridPoint p) {
  Position = p;
}
void Food::generate(Grid box) {
  Position.setX(rand() % (box.getWidth()));
  Position.setY(rand() % (box.getHeight()));
  std::cout << "(" << Position.getX() << ", " << Position.getY() << ")\n";
}
GridPoint Food::getPosition() { return Position; }

Snake::Snake(uint16_t length, GridPoint startPos) {
  while(length--) {
    body.push_back((GridPoint){uint16_t(startPos.getX() - length), startPos.getY()});
  }
}
std::vector<GridPoint> Snake::getBody() { return body; }
SnakeState Snake::getState() { return state; }

void Snake::moveBodyAlong() {
  uint16_t snakeLength = this->body.size();
  for(int i = 0; i < snakeLength - 1; i++) {
    this->body[i] = this->body[i + 1];
  }
}
void Snake::moveDown() {
  if(state == GOING_UP) return;
  this->moveBodyAlong();
  this->body.back().setY(this->body.back().getY() + 1);
  this->state = GOING_DOWN;
  std::cout << "move down\n";
}
void Snake::moveUp() {
  if(state == GOING_DOWN) return;
  this->moveBodyAlong();
  this->body.back().setY(this->body.back().getY() - 1);
  this->state = GOING_UP;
  std::cout << "move up\n";
}
void Snake::moveLeft() {
  if(state == GOING_RIGHT) return;
  this->moveBodyAlong();
  this->body.back().setX(this->body.back().getX() - 1);
  this->state = GOING_LEFT;
  std::cout << "move left\n";
}
void Snake::moveRight() {
  if(state == GOING_LEFT) return;
  this->moveBodyAlong();
  this->body.back().setX(this->body.back().getX() + 1);
  this->state = GOING_RIGHT;
  std::cout << "move right\n";
}
bool Snake::isEatingFood(Food food) {
  return this->body.back() == food.getPosition();
}
void Snake::grow() {
  if(body[0].getX() == body[1].getX()) { // vertical direction
    if(body[0].getY() - body[1].getY() < 0) { // add on the top
      body.insert(body.begin(), GridPoint(body[0].getX(), body[0].getY() - 1));
    } else {                                  // add on the bottom
      body.insert(body.begin(), GridPoint(body[0].getX(), body[0].getY() + 1));
    }
  } else {                               // vertical direction
    if(body[0].getX() - body[1].getX() < 0) { // add to the left
      body.insert(body.begin(), GridPoint(body[0].getX() - 1, body[0].getY()));
    } else {                                  // add to the right
      body.insert(body.begin(), GridPoint(body[0].getX() + 1, body[0].getY()));
    }
  }
  std::cout << "grow\n";
}

bool Food::isGeneratedInsideSnake(Snake &snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength; i++) {
    if(Position == snake.getBody()[i]) return true;
  }
  return false;
}
