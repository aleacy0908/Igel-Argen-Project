#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "SETUP_BOARD.h"

#define TOKENS_PER_PLAYER 4

int col_chars[6] = {'R', 'B', 'Y', 'G', 'P', 'O'};

void NEW_BOARD();

void SETUP_TOKENS(unsigned int num_players, Player player_arr[]);
void print_tile_error(char error[]);
void PRINT_COLOUR(enum COLOUR c);
void SETUP_TOKENS(unsigned int player_count, Player player_arr[]);

void print_tile_atts(Tile tx);
void print_game_stacks();


int roll_die();

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

int PLAYER_COUNT;
int PLAYER_TURN;

int main(int argc, char** argv) {
    
    srand(time(NULL)); //Sets up the random generator
    
    unsigned int num_players;
    
    NEW_BOARD();
    
    printf("How many players will be playing?: ");
    scanf("%d", &num_players);
    
    PLAYER_COUNT = num_players;
    
    Player players[PLAYER_COUNT];
    
    
    for(int c = 0; c < num_players; c++)
    {
        Player new_player;
        
        players[c] = new_player;
    }
    
    
    CHOOSE_COLOURS(num_players, players, col_chars);
    
    
    SETUP_TOKENS(PLAYER_COUNT, players);
    
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
            Tile new_tile = {false,false, 0, NONE};
            
            GAME_BOARD[r][c] = new_tile;
        }
    }
}

void SETUP_TOKENS(unsigned int player_count, Player player_arr[])
{
    int game_tokens = player_count * 4;
    int tokens_placed = 0;
    int turn = 0;
    int round = 0;
    
    int stack_layer = 0;
    
    //Give the players their tokens
    for(int p = 0; p < PLAYER_COUNT; p++)
    {
        for(int t = 0; t < TOKENS_PER_PLAYER; t++)
        {
            Token new_tkn = {{-1,-1}, player_arr[p].team_col};
            
            player_arr[p].p_tokens[t] = new_tkn;
        }
    }
    
    //Ask players where they want to place their tokens
    while(tokens_placed < game_tokens)
    {
        Player plyr = player_arr[turn];
        Token tkn = player_arr[turn].p_tokens[round];
        
        printf("Player Turn: ");
        PRINT_COLOUR(plyr.team_col);
        
        printf("\nWhich row would you like to place your token?\n");
        printf("Enter a number from 0-5\n");
        
        int input;
        scanf("%d", &input);
        
        //Check it's a number between 1 and 6
        if(input < 0 || input > 5)
        {
            printf("\nINVALID INPUT, TRY AGAIN\n");
            continue;
        }
        
        Tile tl = GAME_BOARD[input][0];
        
        //If theres one tile left on this layer
        //and it's the players own colour, they
        //can place their token on another tile
        bool viable_tile = tl.stack_count == stack_layer;
        bool own_token_on_top = tl.col_on_top == plyr.team_col;
        
        
        //This counts how many viable tiles are
        //left and if your
        int viable_tile_count = 0;
        int own_team_on_top = 0;
        for(int r = 0; r < BOARD_ROWS; r++)
        {
            Tile x = GAME_BOARD[r][0];
            
            if(x.stack_count == stack_layer)
            {
                viable_tile_count++;
            }
            
            if(x.col_on_top == plyr.team_col)
            {
                own_team_on_top++;
            }
        }
        
        if(viable_tile_count == own_team_on_top)
        {
            viable_tile = true;
            
            printf("Your own tokens are on top of every viable tile\n");
            printf("You must select a tile that isn't on the current stack level");
        }
        
        
        //if the tile has the right number of tokens on it and the token
        //on top isn't the current player's token
        
        if(viable_tile && !own_token_on_top)
        {
            //place token, update coords, put it in token array
            //increment stack count for tile
            //update colour on top
            
            player_arr[turn].p_tokens[round].coord[0] = input;
            player_arr[turn].p_tokens[round].coord[1] = 0;
            player_arr[turn].p_tokens[round].token_col = plyr.team_col;
            
            player_arr[turn].p_tokens[round] = tkn;
            
            GAME_BOARD[input][0].stack_count++;
            
            GAME_BOARD[input][0].col_on_top = plyr.team_col;
            
            //PRINT_TILE_BOARD(player_arr); PUT TEACHERS FUNCTION CALL HERE
            
        }
        else if(!viable_tile && !own_token_on_top)
        {
            //ERROR: TOO MANY TOKENS
            print_tile_error("This tile has too many tokens on it");
            
            continue;
        }
        else if(viable_tile && own_token_on_top)
        {
            //ERROR: OWN TOKEN ON TOP
            print_tile_error("Your own token is on top");
            
            continue;
        }
        else
        {
            //ERROR: BOTH
            print_tile_error("Tile has too many tokens AND own token is on top");
            
            continue;
        }
        
        
        //Check if the stack layer needs to be incremented
        bool keep_stack_level = false;
        
        for(int r = 0; r < BOARD_ROWS; r++)
        {
            Tile t = GAME_BOARD[r][0];
            
            //Is there any tile where we have not reached
            //the current stack layer yet?
            if(t.stack_count == stack_layer)
            {
                keep_stack_level = true;
                break;
            }
        }
        
        print_board(GAME_BOARD);
        
        //If every tile has reached the stack layer,
        //we increment the stack layer
        if(!keep_stack_level) stack_layer++;
        
        if(++turn == player_count) turn = 0; round++; //next round
        tokens_placed++;
    }
}



void PRINT_COLOUR(enum COLOUR c)
{
    switch(c)
    {
        case RED:
            printf("Red");
            break;
            
        case BLU:
            printf("Blue");
            break;
            
        case YELLOW:
            printf("Yellow");
            break;
            
        case GREEN:
            printf("Green");
            break;
            
        case PINK:
            printf("Pink");
            break;
            
        case ORANGE:
            printf("Orange");
            break;
            
        default:
            printf("Invalid Colour\n");
            break;
            
    }
}

void print_game_stacks()
{
    printf("\n");
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        for(int j = 0; j < BOARD_COLS; j++)
        {
            Tile x = GAME_BOARD[i][j];
            
            printf("%d ", x.stack_count);
        }
        printf("\n");
    }
}

void print_tile_atts(Tile tx)
{
    printf("Stack Count: %d\n Colour On Top: %d\n\n\n", tx.stack_count, tx.col_on_top);
}

void print_tile_error(char error[])
{
    printf("~You cannot select this tile~\n");
    printf("Reason: %s\n", error);
    printf("TRY AGAIN\n\n");
}

