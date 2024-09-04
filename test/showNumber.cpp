#include "../core.h"
#include <SDL2/SDL_events.h>

int main() {
  Screen screen(640, 400);

  // for(int i = 0; i < 10; i++) {
  //   drawDigit(&screen, i, 200 + i*6*5 + 10 * i, 400 / 2);
  // }
  showNumber(&screen, 230, 20, 20);

  screen.updateWindow();
  SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
  return 0;
}
