#include "window.h"

#include <SDL.h>
#include <stdio.h>

#include "game.h"

extern SDL_Window *game_window;
extern SDL_Renderer *game_renderer;

int width = CELL_SIZE * GRID_COLS * WINDOW_SCALE;
int height = CELL_SIZE * GRID_ROWS * WINDOW_SCALE;

void renderer_init()
{
  game_renderer = SDL_CreateRenderer(
      game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (game_renderer == NULL)
  {
    SDL_DestroyWindow(game_window);
    SDL_Quit();
  }
}

void init()
{
  game_window =
      SDL_CreateWindow(WINDOW_TITLE, 0, 0, width, height, SDL_WINDOW_HIDDEN);
  if (game_window == NULL)
  {
    SDL_DestroyWindow(game_window);
    SDL_Quit();
  }
}

void setup()
{
  SDL_DisplayMode display;
  SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(game_window), &display);
  int posX = display.w / 2 - width / 2;
  int posY = display.h / 2 - height / 2;
  SDL_SetWindowPosition(game_window, posX, posY);
  SDL_ShowWindow(game_window);
}

void window_init()
{
  init();
  renderer_init();
  setup();
}