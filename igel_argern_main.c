#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "SETUP_BOARD.h"
#include "struct_setup.h"

#define BOARD_ROWS 6
#define BOARD_COLS 9

enum COLOUR {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE
} COLOUR;

int col_chars[6] = {'R', 'B', 'Y', 'G', 'P', 'O'};

/*typedef struct Token
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
} Player;*/

void PRINT_BOARD();
void NEW_BOARD();
//void CHOOSE_COLOURS(unsigned int num_players, Player player_arr[]);

int roll_die();

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

unsigned int PLAYER_TURN; //which player's turn is it

int main(int argc, char** argv) {
    
    srand(time(NULL)); //Sets up the random generator
    
    unsigned int num_players;
    int i = 0;
    
    NEW_BOARD();
    
    printf("How many players will be playing?: ");
    scanf("%d", &num_players);
    
    Player players[num_players];
    
    CHOOSE_COLOURS(num_players, players, col_chars, COLOUR);
    
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

/*void CHOOSE_COLOURS(unsigned int num_players, Player player_arr[])
{
    char col_inputs[6][20] = {"R = Red\n","B = Blue\n","Y = Yellow\n","G = Green\n","P = Pink\n","O = Orange\n"};
    
    bool invalid_input = false;
    
    for(int i = 0; i < num_players; i++)
    {
        /* 
         Print Colour Options
         -> We want one unique colour for each individual player,
            thus we get rid of the option for a colour in the 
            switch statement below after it's been selected
         -> Also, if the user inputs an invalid character,
            he/she is asked to try again
 
        
        if(invalid_input) 
        {
            printf("INVALID INPUT, TRY AGAIN\n");
            invalid_input = false;
        }
        else
        {
            printf("Player %d, Which Colour Would You Like?\n", i+1);
        }
        
        for(int j = 0; j < 6; j++)
        {
            printf("%s",col_inputs[j]);
        }
        
        //Input Player Colour
        char c;
        scanf(" %c", &c);
        
        /*
         Search for the colour and if
         none is found then the input
         was invalid
         *
        
        bool valid_colour = false;
        int num;
        
        for(int i = 0; i < 6; i++)
        {
            if(c == col_chars[i])
            {
                num = i;
                valid_colour = true;
                break;
            }
        }
        
        if(!valid_colour)
        {
            invalid_input = true;
            i -= 1;
        }
        else
        {
            switch(c)
            {
                case 'R':
                    player_arr[i].team_col = RED;
                    break;
                case 'B':
                    player_arr[i].team_col = BLU;
                    break;
                case 'Y':
                    player_arr[i].team_col = YELLOW;
                    break;
                case 'G':
                    player_arr[i].team_col = GREEN;
                    break;
                case 'P':
                    player_arr[i].team_col = PINK;
                    break;
                case 'O':
                    player_arr[i].team_col = ORANGE;
                    break;
            }
            strcpy(col_inputs[num], ""); //Get rid of the option for this colour
        }
    }
}*/
