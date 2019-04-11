#include <stdio.h>
#include <stdlib.h>
#include "SETUP_BOARD.h"

int roll_die();

void TAKE_TURN(Player p, Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS]);

void move_down(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);
void move_up(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);
void move_forward(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c);

