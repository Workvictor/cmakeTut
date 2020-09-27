#pragma once
#define GAME_SCREEN_MATRIX 3
#define GAME_SCREEN_WIDTH 640.0
#define GAME_SCREEN_HEIGHT 480.0
#define CELL_WIDTH (GAME_SCREEN_WIDTH / GAME_SCREEN_MATRIX)
#define CELL_HEIGHT (GAME_SCREEN_HEIGHT / GAME_SCREEN_MATRIX)

#define CELL_SIZE 32
#define GRID_COLS 3
#define GRID_ROWS 3

#define EMPTY 0
#define P1 1
#define P2 2

#define STATE_RUNNING 0
#define STATE_P1_VICTORY 1
#define STATE_P2_VICTORY 2
#define STATE_TIE 3
#define STATE_QUIT 4

typedef struct
{
  int board[GAME_SCREEN_MATRIX * GAME_SCREEN_MATRIX];
  int player;
  int state;
} TGame;

void
game_init();