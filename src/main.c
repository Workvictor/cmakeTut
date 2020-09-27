#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  game_init();

  return 0;
}