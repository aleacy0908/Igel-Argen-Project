#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TOTAL_TOKENS 24
#define BOARD_ROWS 6
#define BOARD_COLS 9

typedef struct Token
{
    unsigned int coord[2]; //(row,column) -> e.g (0,2)
    unsigned int team; //team number from 1-6
    unsigned int token_id; //token number from 1-4
    
} Token;

typedef struct Tile
{
    bool is_occupied; //does this tile have any tokens on it?
    bool is_obstacle; //is this tile a black obstacle tile?
    Token tokens_stack[TOTAL_TOKENS]; //first token in is first token in array
    
} Tile;

void PRINT_BOARD();
void NEW_BOARD();

int roll_die();

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

unsigned int PLAYER_TURN; //which player's turn is it

int main(int argc, char** argv) {
    
    srand(time(NULL)); //Sets up the random generator
    
    NEW_BOARD();
    
    
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
