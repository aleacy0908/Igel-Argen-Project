#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*SETUP BOARD:
 This C and Header file will hold the functions and structs
 required to setup our game board and put all the necessary
 tokens on it. */

#define TOKENS_PER_PLAYER 4
#define TOTAL_TOKENS 24

#define BOARD_ROWS 6
#define BOARD_COLS 9

//Enum to hold the colours of our players
enum COLOUR {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE, NONE
};

//TOKEN STRUCT
typedef struct Token
{
    //(row,column) -> e.g (0,2)
    unsigned int coord[2];
    
    //Token's team colour
    enum COLOUR token_col;
    
}Token;

// TILE (SQUARE) STRUCT
typedef struct Tile
{
    bool is_obstacle;
    
    //Amount of tokens in the stack
    int stack_count;
    
    //Our linked list for the stack
    struct stack_elem *stack_top;
    
    
} Tile;

//PLAYER STRUCT
typedef struct Player
{
    //Team colour
    enum COLOUR team_col;
    
    //Stores the tokens for each player
    Token p_tokens[4];
    
    unsigned int score;
    unsigned int player_id;
    
} Player;

//STACK STRUCT
typedef struct stack_elem{
    enum COLOUR data;
    struct stack_elem *next;
} stack;

/* Stack: Linked List
 Push -> Pushes an element onto the top of the stack
 Pop  -> Removes the top element of the stack */

struct stack_elem * push(enum COLOUR col, struct stack_elem *top);
struct stack_elem * pop(struct stack_elem *top);

/* -Game Functions-
 These functions will create a new board, allow players
 to choose which colour they'd like to be, and place their
 tokens onto the game board */

void NEW_BOARD(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS]);
void CHOOSE_COLOURS(unsigned int num_players, struct Player player_arr[], int col_chars[]);
void SETUP_TOKENS(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], unsigned int player_count, Player player_arr[]);

/* -Print Functions-
 These functions allow us to print the game 
 board, tile errors and the team colours.
 
 Printing tile errors: Allows us to condense the amount of
 space we need everytime we want to print a tile error.
 */

void print_board(Tile game_board[BOARD_ROWS][BOARD_COLS]);
void print_tile_error(char error[]);
void printLine();

//Print a colour character
void print_colour(enum COLOUR c);

//Print the full colour name
void PRINT_COLOUR_LONG(enum COLOUR c);








