/*
 COMP10050: Software Engineering Project 1
 Assignment 2
 
 Assignment Title: Igel Argern
 
 Developers: Daniel Gallagher, Adam Leacy
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "MOVEMENT.h"

/* -Print Functions-
 Printing A Scoreboard: A Scoreboard is printed at the 
 end of the game to show the final score of each player.
 It also makes explicit which of these players has won.*/

void print_score_board(Player p_arr[], int player_count);


//This function checks our players to see if any have a score of 3
bool check_for_winner(Player p_arr[], Player *winner, int player_count);


/* -Global Variables-
 
 We want the amount of players, which turn it is, the team colours,
 whether the game has been won and the board of our game to be global so
 that we can access these variables anywhere*/

int PLAYER_COUNT, PLAYER_TURN;
bool GAME_WON = false;

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

//Stores the first letter of each team colour
int col_chars[6] = {'R', 'B', 'Y', 'G', 'P', 'O'};

int main(int argc, char** argv) {
    
    //Setup for a random number generator (based on time)
    time_t t;
    srand((unsigned) time(&t));
    
    
    /* BEGINNING:
     -> Choosing amount of players
     -> Choosing team colours
     -> Placing Tokens on the board */
    
    printf("--Igel Ärgern--\n\n");
    
    NEW_BOARD(GAME_BOARD);
    
    printf("How many players will be playing?: ");
    scanf("%d", &PLAYER_COUNT);
    
    Player players[PLAYER_COUNT];
    
    //Add players to our player array
    for(int c = 0; c < PLAYER_COUNT; c++)
    {
        Player new_player;
        
        //Team ID is based on index in array
        new_player.player_id = c;
        
        //Score at the beginning is set to zero
        new_player.score = 0;
        
        players[c] = new_player;
    }
    
    CHOOSE_COLOURS(PLAYER_COUNT, players, col_chars);

    SETUP_TOKENS(GAME_BOARD, PLAYER_COUNT, players);
    
    /* PLAYING THE GAME i.e TAKING TURNS:
     -> A die is rolled giving the player a random number 
        between 0 and 5 (inclusive)
     -> The player is given an opportunity to perform
        a sidestep.
     -> The player must choose a token on the row of
        the random rolled number to move forward.
     
     This continues until a player wins. When a player wins,
     our global bool GAME_WON is switched to true and the turns
     loop ceases.
     */

    int p_turn = 0;
    Player winning_player;
    
    while(!GAME_WON)
    {
        TAKE_TURN(players[p_turn], GAME_BOARD);
        
        GAME_WON = check_for_winner(players, &winning_player, PLAYER_COUNT);
        
        if(p_turn == (PLAYER_COUNT-1))
            p_turn = 0;
        else p_turn++;
    }
    
    /* END OF GAME: PLAYER WINS
     
     A player wins the game if they reach a score of 3.
     When someone wins we congratulate the winner and
     print out a scoreboard.
     
     This scoreboard lists every player and their final
     score. It also makes clear who won the game. */
    
    printf("\n\n\n~THERE IS A WINNER~\n\n"
           "Congratulations To Team ");
    PRINT_COLOUR_LONG(winning_player.team_col);
    
    print_score_board(players, PLAYER_COUNT);
    
}

//Print Functions
void print_tile_error(char error[])
{
    printf("~You cannot select this tile~\n"
           "Reason: %s\n", error);
    printf("TRY AGAIN\n\n");
}

void print_score_board(Player p_arr[], int player_count)
{
    printf("\n--FINAL SCOREBOARD--\n");
    
    for(int i = 0; i < player_count; i++)
    {
        Player p = p_arr[i];
        
        printf("\n");
        PRINT_COLOUR_LONG(p.team_col);
        printf(" Score: %u", p.score);
        
        /* If their score is 3, we put a winner
         tag beside their name */
        if(p.score == 3)
            printf(" *WINNER* ");
        
    }
}

//Other Functions
bool check_for_winner(Player p_arr[], Player *winner, int player_count)
{
    for(int i = 0; i < player_count; i++)
    {
        Player p = p_arr[i];
        
        /* For each player, if their score is 3
           then register this player as the winner
           and return true */
        
        if(p.score == 3)
        {
            winner = &p;
            return true;
        }
        
    }
    
    return false;
}



