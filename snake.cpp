#include "snake.h"
#include <SDL2/SDL_ttf.h>
#include <cstdlib>

Draw::Draw(Screen *screen) {
  this->screen = screen;
}
void Draw::drawSnake(Grid box, Snake snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength - 1; i++) {
    screen->drawAGridCell(snake.getBodyColor(), box, snake.getBody()[i]);
  }
  screen->drawAGridCell(snake.getHeadColor(), box, snake.getBody().back());
}
void Draw::clearSnake(Grid box, Snake snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength; i++) {
    screen->drawAGridCell(box.getBackgroundColor(), box, snake.getBody()[i]);
  }
}
void Draw::drawFood(Grid box, Food food) {
  screen->drawAGridCell(food.getColor(), box, food.getPosition());
}
void Draw::clearFood(Grid box, Food food) {
  screen->drawAGridCell(box.getBackgroundColor(), box, food.getPosition());
}
Screen* Draw::getScreen() { return screen; }

Food::Food(GridPoint position, SDL_Color color) {
  this->position = position;
  this->color = color;
}
void Food::generate(Grid box) {
  position.setX(rand() % (box.getWidth()));
  position.setY(rand() % (box.getHeight()));
  //std::cout << "(" << Position.getX() << ", " << Position.getY() << ")\n";
}
bool Food::isGeneratedInsideSnake(Snake &snake) {
  uint16_t snakeLength = snake.getBody().size();
  for(int i = 0; i < snakeLength; i++) {
    if(position == snake.getBody()[i]) return true;
  }
  return false;
}
GridPoint Food::getPosition() { return position; }
SDL_Color Food::getColor() { return color; }

Snake::Snake(uint16_t length, GridPoint startPos, SDL_Color bodyColor, SDL_Color headColor) {
  this->bodyColor = bodyColor;
  this->headColor = headColor;
  while(length--) {
    body.push_back((GridPoint){int16_t(startPos.getX() - length), startPos.getY()});
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
  // std::cout << "move down\n";
}
void Snake::moveUp() {
  if(state == GOING_DOWN) return;
  this->moveBodyAlong();
  this->body.back().setY(this->body.back().getY() - 1);
  this->state = GOING_UP;
  // std::cout << "move up\n";
}
void Snake::moveLeft() {
  if(state == GOING_RIGHT) return;
  this->moveBodyAlong();
  this->body.back().setX(this->body.back().getX() - 1);
  this->state = GOING_LEFT;
  // std::cout << "move left\n";
}
void Snake::moveRight() {
  if(state == GOING_LEFT) return;
  this->moveBodyAlong();
  this->body.back().setX(this->body.back().getX() + 1);
  this->state = GOING_RIGHT;
  // std::cout << "move right\n";
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
}
bool Snake::isDead(Grid box) {
  // check snake eating its tail
  uint16_t snakeLength = body.size();
  for(int i = 1; i < snakeLength - 3; i++) {
    if(body.back() == body[i]) {
      std::cout << "snake ate its tail\n";
      return true;
    } 
  }

  // check snake heading the wall of the box
  if(body.back().getX() < 0 || body.back().getX() == box.getWidth() 
      || body.back().getY() < 0 || body.back().getY() == box.getHeight())  {
    std::cout << "snake headed toward the wall\n";
    return true;
  }
  return false;
}
void Snake::logSnake() {
  uint16_t snakeLength = body.size();
  for(int i = 0; i < snakeLength; i++) {
    std::cout << "(" << body[i].getX() << ", " << body[i].getY() << ")\n" << "---\n";
  }
}
SDL_Color Snake::getBodyColor() { return bodyColor;}
SDL_Color Snake::getHeadColor() { return headColor;}
