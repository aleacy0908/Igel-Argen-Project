#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_TOKENS 24
#define BOARD_ROWS 6
#define BOARD_COLS 9

enum COLOUR {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE, NONE
};

//STACK STRUCT
typedef struct stack_elem{
    enum COLOUR data;
    struct stack_elem *next;
} stack;

//GAME STRUCTS
typedef struct Token
{
    unsigned int coord[2]; //(row,column) -> e.g (0,2)
    enum COLOUR token_col;
    
}Token;

typedef struct Tile
{
    bool is_obstacle; //is this tile a black obstacle tile?
    int stack_count;
    
    struct stack_elem *stack_top;
    
    
}Tile;

typedef struct Player
{
    enum COLOUR team_col;
    unsigned int score;
    Token p_tokens[4];
    unsigned int player_id;
    
}Player;

struct stack_elem * push(enum COLOUR col, struct stack_elem *top);
struct stack_elem * pop(struct stack_elem *top);

void NEW_BOARD(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS]);

void CHOOSE_COLOURS(unsigned int num_players, struct Player player_arr[], int col_chars[]);

void print_board(Tile game_board[BOARD_ROWS][BOARD_COLS]);
void printLine();
char print_token(Token t);

void print_colour(enum COLOUR c);
void PRINT_COLOUR_LONG(enum COLOUR c);

void REMOVE_OBSTACLES(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS]);





