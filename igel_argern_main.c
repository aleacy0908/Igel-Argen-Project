#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "MOVEMENT.h"

#define TOKENS_PER_PLAYER 4

int col_chars[6] = {'R', 'B', 'Y', 'G', 'P', 'O'};

void SETUP_TOKENS(unsigned int num_players, Player player_arr[]);
void print_tile_error(char error[]);
void PRINT_COLOUR_LONG(enum COLOUR c);
void SETUP_TOKENS(unsigned int player_count, Player player_arr[]);

void print_game_stacks();
void printList(struct stack_elem *currentPtr);

bool check_for_winner(Player p_arr[], Player *winner, int player_count);

void print_score_board(Player p_arr[], int player_count);

Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS];

int PLAYER_COUNT;
int PLAYER_TURN;

bool GAME_WON = false;

int main(int argc, char** argv) {
    
    //Set up a random number generator (based on time)
    time_t t;
    srand((unsigned) time(&t));
    
    unsigned int num_players;
    
    printf("--Igel Ärgern--\n\n");
    
    NEW_BOARD(GAME_BOARD);
    
    printf("How many players will be playing?: ");
    scanf("%d", &PLAYER_COUNT);
    
    Player players[PLAYER_COUNT];
    
    
    
    for(int c = 0; c < num_players; c++)
    {
        Player new_player;
        new_player.player_id = c;
        new_player.score = 0;
        
        players[c] = new_player;
    }
    
    
    CHOOSE_COLOURS(PLAYER_COUNT, players, col_chars);

    
    SETUP_TOKENS(PLAYER_COUNT, players);
    
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
    
    //END OF GAME: PLAYER WINS
    
    
    /*A player wins the game if they reach a score of 3.
     When someone wins, we congratulate the winner and
     print out a scoreboard.
     
     This scoreboard lists every player and their final
     score. It also makes clear who won the game.
     */
    printf("\n\n\n~THERE IS A WINNER~\n\n"
           "Congratulations To Team ");
    PRINT_COLOUR_LONG(winning_player.team_col);
    
    print_score_board(players, PLAYER_COUNT);
    
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
        
        if(p.score == 3)
            printf(" *WINNER* ");
        
    }
}
//FUNCTIONS TO SET UP THE GAME
/*void NEW_BOARD()
{
    for(int r = 0; r < BOARD_ROWS; r++)
    {
        for(int c = 0; c < BOARD_COLS; c++)
        {
            Tile new_tile = {false,false, NULL};
            
            new_tile.stack_top = push(NONE, new_tile.stack_top);
            
            GAME_BOARD[r][c] = new_tile;
        }
    }
    
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        int obstacle_placement = rand() % 7 + 1;
        
        GAME_BOARD[i][obstacle_placement].is_obstacle = true;
    }
}*/

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
        PRINT_COLOUR_LONG(plyr.team_col);
        
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
        bool own_token_on_top = tl.stack_top->data == plyr.team_col;
        
        
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
            
            if(x.stack_top->data == plyr.team_col)
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
            
            //Push to the stack for this tile
            GAME_BOARD[input][0].stack_top = push(plyr.team_col, GAME_BOARD[input][0].stack_top);
            
            //Increase the stack count
            GAME_BOARD[input][0].stack_count++;
            
            //Change the colour on top of the stack
            GAME_BOARD[input][0].stack_top->data = plyr.team_col;
            
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
        printList(GAME_BOARD[input][0].stack_top);
        
        //If every tile has reached the stack layer,
        //we increment the stack layer
        if(!keep_stack_level) stack_layer++;
        
        if(++turn == player_count) turn = 0; round++; //next round
        tokens_placed++;
    }
}

bool check_for_winner(Player p_arr[], Player *winner, int player_count)
{
    for(int i = 0; i < player_count; i++)
    {
        Player p = p_arr[i];
        
        if(p.score == 3)
        {
            winner = &p;
            return true;
        }
        
    }
    
    return false;
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

void print_tile_error(char error[])
{
    printf("~You cannot select this tile~\n");
    printf("Reason: %s\n", error);
    printf("TRY AGAIN\n\n");
}


//delete
void printList(struct stack_elem *currentPtr)
{
    /* if list is empty */
    if ( currentPtr == NULL ) {
        printf( "List is empty.\n\n" );
    } /* end if */
    else {
        printf( "The list is:\n" );
        
        /* while not the end of the list */
        while ( currentPtr->data != NONE ) {
            print_colour(currentPtr->data);
            printf(" ");
            currentPtr = currentPtr->next;
        } /* end while */
        
        printf( " \n\n" );
    }
}

