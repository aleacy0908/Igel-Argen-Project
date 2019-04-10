#include "struct_setup.h"


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

typedef struct Player
{
    enum COLOUR team_col;
    unsigned int score;
    Token p_tokens[4];
} Player;
