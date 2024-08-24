#include "../snake.h"

const short int BOX_WIDTH = 36;
const short int BOX_HEIGHT = 16;

Screen screen;
Grid box(40, 40, BOX_WIDTH, BOX_HEIGHT, CELL_SIZE, GRID_BACKGROUND_COLOR);

int main() {
  screen.drawBox(box);
  
  SDL_Color cellFillColor = {0xFF, 0xFF, 0xFF};
  for(int i = 0; i < BOX_WIDTH; i++) {
    for(int j = 0; j < BOX_HEIGHT; j++) {
      cellFillColor.r = 0xFF + 0xFA * j;
      cellFillColor.g = 0xFF + 0xFA * i;
      cellFillColor.b = 0xFF + 0xFA * j;
      screen.drawAGridCell(cellFillColor, box, GridPoint(i, j));
    }
  }
  // screen.drawAGridCell(RED, box, GridPoint(BOX_WIDTH - 1, BOX_HEIGHT - 1));
  // screen.drawAGridCell(RED, box, GridPoint(BOX_WIDTH - 1, 0));
  // screen.drawAGridCell(RED, box, GridPoint(0, 0));
  // screen.drawAGridCell(RED, box, GridPoint(0, BOX_HEIGHT - 1));

  screen.updateWindow();
  //Hack to get window to stay up
  SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

}
