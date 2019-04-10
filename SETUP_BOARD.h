#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_TOKENS 24

enum COLOUR {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE, NONE
};

typedef struct Token
{
    unsigned int coord[2]; //(row,column) -> e.g (0,2)
    unsigned int team; //team number from 1-6
    //unsigned int token_id; //token number from 1-4
    enum COLOUR token_col;
    
}Token;

typedef struct Tile
{
    bool is_occupied; //does this tile have any tokens on it?
    bool is_obstacle; //is this tile a black obstacle tile?
    int stack_count;
    
    enum COLOUR col_on_top;
    Token tokens_stack[TOTAL_TOKENS]; //first token in is first token in array
    
}Tile;

typedef struct Player
{
    enum COLOUR team_col;
    unsigned int score;
    Token p_tokens[4];
}Player;


void CHOOSE_COLOURS(unsigned int num_players, struct Player player_arr[], int col_chars[]);
