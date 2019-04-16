#include <stdio.h>
#include <stdlib.h>
#include "SETUP_BOARD.h"

// -Action Functions-
void TAKE_TURN(Player p, Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS]);
void move_down(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);
void move_up(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);
void move_forward(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], Player *p, int r, int c);

// -Other Functions-
bool token_stuck(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);
int roll_die();

