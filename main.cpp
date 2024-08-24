#include "snake.h"
#include <unistd.h>

Screen screen;
Snake snake(4, GridPoint(10, 10));
Food food(GridPoint(3, 2));

int main() {
  Grid mainBox(40, 40, 40, 22, CELL_SIZE, GRID_BACKGROUND_COLOR);
  food.generate(mainBox);
  const int frameDelay = 1000 / 13; // FPS, speed of snake
  uint32_t frameStart;
  int frameTime;

  // The main game loop
  SDL_Event e;
  bool quit = false;
  bool gameOver = false;
  bool isRightKeyPress;
  while(quit == false && gameOver == false) {
    frameStart = SDL_GetTicks();
    
    isRightKeyPress = false;
    while(SDL_PollEvent(&e)){ 
      if(e.type == SDL_QUIT) quit = true; 
      else if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
          case SDLK_UP:
            if(snake.getState() == GOING_UP) break; // prevent double press
            snake.moveUp();
            isRightKeyPress = true;
            break;
          case SDLK_DOWN:
            if(snake.getState() == GOING_DOWN) break;
            snake.moveDown();
            isRightKeyPress = true;
            break;
          case SDLK_LEFT:
            if(snake.getState() == GOING_LEFT) break;
            snake.moveLeft();
            isRightKeyPress = true;
            break;
          case SDLK_RIGHT:
            if(snake.getState() == GOING_RIGHT) break;
            snake.moveRight();
            isRightKeyPress = true;
            break;
        }
      }
    }
    if(!isRightKeyPress) {
      switch(snake.getState()) {
        case GOING_UP:
          snake.moveUp();
          break;
        case GOING_DOWN:
          snake.moveDown();
          break;
        case GOING_LEFT:
          snake.moveLeft();
          break;
        case GOING_RIGHT:
          snake.moveRight();
          break;
        case DEAD:
          break;
      }
    }

    screen.clearFood(mainBox, food);
    screen.clearSnake(mainBox, snake);

    screen.drawBox(mainBox);

    screen.drawSnake(mainBox, snake);
    screen.drawFood(mainBox, food);

    if(snake.isEatingFood(food)) {
      food.generate(mainBox);
      snake.grow();
    }

    screen.updateWindow();

    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
  return 0;
}
