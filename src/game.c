#include "game.h"

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include "window.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;

TGame game;

enum EActivePlayer
{
  Player_O,
  Player_X
} ActivePlayer;

void game_update() {}

void game_render() {}

void reset()
{
  size_t sizeOfBoard = sizeof(game.board) / sizeof(*game.board);
  for (size_t i = 0; i < sizeOfBoard; i++)
  {
    game.board[i] = EMPTY;
  }
}

void game_init()
{
  window_init();

  reset();
  SDL_ShowCursor(SDL_DISABLE);

  IMG_Init(IMG_INIT_PNG);
  SDL_Log("test log 1111");

  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = 32;
  srcRect.h = 32;
  SDL_Rect dstRect;
  dstRect.x = 0;
  dstRect.y = 0;
  dstRect.w = 32;
  dstRect.h = 32;
  SDL_Texture *circle_tex = NULL;
  circle_tex = IMG_LoadTexture(game_renderer, "../res/circle.png");
  if (circle_tex == NULL)
  {
    SDL_Log("textue error %s\n", SDL_GetError());
  }
  SDL_Texture *cross_tex = NULL;
  cross_tex = IMG_LoadTexture(game_renderer, "../res/cross.png");
  if (cross_tex == NULL)
  {
    SDL_Log("textue error %s\n", SDL_GetError());
  }

  SDL_Texture *figure[2];
  figure[Player_O] = circle_tex;
  figure[Player_X] = cross_tex;

  int places[GRID_COLS][GRID_ROWS];
  for (int i = 0; i < GRID_COLS; i++)
  {
    for (int j = 0; j < GRID_ROWS; j++)
    {
      places[i][j] = -1;
    }
  }

  SDL_Rect hoverRect;
  hoverRect.x = 0;
  hoverRect.y = 0;
  hoverRect.w = 32 * WINDOW_SCALE;
  hoverRect.h = 32 * WINDOW_SCALE;

  game.player = P1;
  game.state = STATE_RUNNING;
  ActivePlayer = Player_O;

  int cellX = 0;
  int cellY = 0;
  SDL_Event e;
  while (game.state != STATE_QUIT)
  {
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_QUIT:
        game.state = STATE_QUIT;
        break;

      case SDL_MOUSEBUTTONDOWN:
        cellX = e.button.x / (CELL_SIZE * WINDOW_SCALE);
        cellY = e.button.y / (CELL_SIZE * WINDOW_SCALE);
        SDL_Log("click: [%d, %d]\n", e.button.x, e.button.y);
        SDL_Log("ActivePlayer: [%d]\n", ActivePlayer);
        places[cellX][cellY] = ActivePlayer;
        SDL_Log("places: [%d, %d] = %d\n", cellX, cellY, places[cellX][cellY]);

        for (int i = 0; i < GRID_COLS; i++)
        {
          for (int j = 0; j < GRID_ROWS; j++)
          {
            if (places[i][j] >= ActivePlayer)
            {
            }
          }
        }

        ActivePlayer = -1 * ActivePlayer + 1;
        break;

      case SDL_MOUSEMOTION:
        dstRect.x = e.button.x - dstRect.w / 2;
        dstRect.y = e.button.y - dstRect.h / 2;
        hoverRect.x = (CELL_SIZE * WINDOW_SCALE) *
                      (e.motion.x / (CELL_SIZE * WINDOW_SCALE));
        hoverRect.y = (CELL_SIZE * WINDOW_SCALE) *
                      (e.motion.y / (CELL_SIZE * WINDOW_SCALE));
        break;

      default:
      {
      }
      }
    }
    SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
    SDL_RenderClear(game_renderer);

    SDL_SetRenderDrawBlendMode(game_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 25);
    SDL_RenderFillRect(game_renderer, &hoverRect);

    SDL_SetRenderDrawColor(game_renderer, 255, 255, 255, 125);
    for (int i = 1; i < GRID_COLS; i++)
    {
      int x = i * CELL_SIZE * WINDOW_SCALE;
      SDL_RenderDrawLine(game_renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int i = 1; i < GRID_ROWS; i++)
    {
      int y = i * CELL_SIZE * WINDOW_SCALE;
      SDL_RenderDrawLine(game_renderer, 0, y, WINDOW_WIDTH, y);
    }

    for (int i = 0; i < GRID_COLS; i++)
    {
      for (int j = 0; j < GRID_ROWS; j++)
      {
        if (places[i][j] >= 0)
        {
          SDL_Rect placeRect;
          placeRect.x = i * CELL_SIZE * WINDOW_SCALE;
          placeRect.y = j * CELL_SIZE * WINDOW_SCALE;
          placeRect.w = 32 * WINDOW_SCALE;
          placeRect.h = 32 * WINDOW_SCALE;
          SDL_RenderCopy(game_renderer,
                         figure[places[i][j]],
                         &srcRect,
                         &placeRect);
        }
      }
    }

    SDL_SetTextureBlendMode(figure[ActivePlayer], SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(figure[ActivePlayer], 75);
    SDL_RenderCopy(game_renderer, figure[ActivePlayer], &srcRect, &dstRect);

    SDL_RenderPresent(game_renderer);
  }

  SDL_DestroyWindow(game_window);
  SDL_Quit();
}