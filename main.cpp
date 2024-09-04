#include "snake.h"
#include <unistd.h>

const uint8_t BOX_WIDTH = 40;
const uint8_t BOX_HEIGHT = 22;

Draw draw(new Screen(BOX_WIDTH * CELL_SIZE, BOX_HEIGHT * CELL_SIZE + 100));
Screen* screen = draw.getScreen();
Grid mainBox(0, 0, BOX_WIDTH, BOX_HEIGHT, CELL_SIZE, GRID_BACKGROUND_COLOR);

Snake snake(3, GridPoint(10, 10), FOREGROUND, RED);
Food food(GridPoint(3, 10), GREEN);

const int frameDelay = 1000 / 13; // FPS, speed of snake
uint32_t frameStart;
int frameTime;

void gameLoop() {
  // The main game loop
  SDL_Event e;
  bool quit = false;
  bool isRightKeyPress;

  uint16_t scores = 0;

  while(quit == false) {

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
        break;
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

    if(snake.isDead(mainBox))
      break;

    //rendering
    draw.clearFood(mainBox, food);
    draw.clearSnake(mainBox, snake);

    screen->drawBox(mainBox);

    draw.drawSnake(mainBox, snake);
    draw.drawFood(mainBox, food);


    if(snake.isEatingFood(food)) {
      scores++;
      std::cout << scores << "\n";
      do {
        food.generate(mainBox);
      }
      while(food.isGeneratedInsideSnake(snake));
      snake.grow();
    }

    screen->updateWindow();

    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}

int main() {
  //snake.logSnake();
  // do {
  gameLoop();  
  // } while(true);

  SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
  return 0;
}
