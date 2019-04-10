#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "SETUP_BOARD.h"

#define BOARD_ROWS 6
#define BOARD_COLS 9

int col_chars[6] = {'R', 'B', 'Y', 'G', 'P', 'O'};

void PRINT_BOARD();
void NEW_BOARD();


int roll_die();

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

unsigned int PLAYER_TURN; //which player's turn is it

int main(int argc, char** argv) {
    
    srand(time(NULL)); //Sets up the random generator
    
    unsigned int num_players;
    
    NEW_BOARD();
    
    printf("How many players will be playing?: ");
    scanf("%d", &num_players);
    
    Player players[num_players];
    
    CHOOSE_COLOURS(num_players, players, col_chars);
    
}

//ACTION FUNCTIONS

//Returns a random number from 1-6
int roll_die()
{
    return (rand() % 6) + 1;
}

//FUNCTIONS TO SET UP THE GAME 
void NEW_BOARD()
{
    for(int r = 0; r < BOARD_ROWS; r++)
    {
        for(int c = 0; c < BOARD_COLS; c++)
        {
            Tile new_tile = {false,false};
            
            GAME_BOARD[r][c] = new_tile;
        }
    }
}

//PRINTING FUNCTIONS
void PRINT_BOARD()
{
    
}

