#include "SETUP_BOARD.h"

void NEW_BOARD(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS])
{
    for(int r = 0; r < BOARD_ROWS; r++)
    {
        for(int c = 0; c < BOARD_COLS; c++)
        {
            //Initialise tiles with defaults
            Tile new_tile = {false,false, NULL};
            
            //Push to board
            new_tile.stack_top = push(NONE, new_tile.stack_top);
            GAME_BOARD[r][c] = new_tile;
        }
    }
    
    //Create obstacle tiles
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        int obstacle_placement = rand() % 7 + 1;
        
        GAME_BOARD[i][obstacle_placement].is_obstacle = true;
    }
}

void SETUP_TOKENS(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], unsigned int player_count, Player player_arr[])
{
    int game_tokens = player_count * 4;
    int tokens_placed = 0;
    int turn = 0;
    int round = 0;
    
    int stack_layer = 0;
    
    /* Give the player their tokens
     
       Initialise the coords as {-1,-1} before
       the player has chosen the coords for their
       tokens*/
    
    for(int p = 0; p < player_count; p++)
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
        
        /* If theres one tile left on this layer
           and it's the players own colour, they
           can place their token on another tile */
        
        bool viable_tile = tl.stack_count == stack_layer;
        bool own_token_on_top = tl.stack_top->data == plyr.team_col;
        
        
        /*Check that there is viable tiles
         (i.e stack is under the stack level for at least one tile)
         left and that your own team is on top*/
        
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
        
        
        /* If the tile has the right number of tokens on it and the token
           on top isn't the current player's token */
        
        if(viable_tile && !own_token_on_top)
        {
            /* Place token, update coords, put it in token array
               increment stack count for tile
               update colour on top */
            
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
            
            /* Is there any tile where we have not reached
               the current stack layer yet? */
            if(t.stack_count == stack_layer)
            {
                keep_stack_level = true;
                break;
            }
        }
        
        print_board(GAME_BOARD);
        
        /* If every tile has reached the stack layer,
           we increment the stack layer */
        
        if(!keep_stack_level) stack_layer++;
        
        if(++turn == player_count) turn = 0; round++; //next round
        tokens_placed++;
    }
}

void CHOOSE_COLOURS(unsigned int num_players, Player player_arr[], int col_chars[])
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
         */
        
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
        
        /* Search for the colour and if
           none is found then the input
           was invalid */
        
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
            strcpy(col_inputs[num], "");
        }
    }
}

/* PUSH & POP Functions */
struct stack_elem * push(enum COLOUR col, struct stack_elem *top){
    struct stack_elem *curr = top;
    top = malloc(sizeof(stack));
    top->data = col;
    top->next = curr;
    return top;
}


struct stack_elem * pop(struct stack_elem *top){
    struct stack_elem *curr = top;
    if(curr!=NULL){
        top = curr->next;
        printf("Stack Data: %d\n", curr->data);
        free(curr);
    }
    return top;
}

/* Print Functions */

void print_board(Tile board[BOARD_ROWS][BOARD_COLS]){
    printf("                THE BOARD\n");
    
    for(int i =0; i < BOARD_ROWS; i++){
        
        //prints an horizontal line
        printLine();
        
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        
        /* if the square (i,j) is occupied,
           c is assigned the initial of the color 
           of the token that occupies the square */
        
        for (int j = 0; j < BOARD_COLS; j++){
            
            if(board[i][j].stack_top->data != NONE){
                printf("|");
                print_colour(board[i][j].stack_top->data);
                
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].is_obstacle)
                    printf("|%c", 'X');
                //c is assigned an empty space otherwise
                else printf("|%c", ' ');
            }
            printf("|    %c", c);
        }
        printf ("\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("    0      1      2      3      4      5      6      7      8\n");
}

void printLine(){
    printf("   -----------------------------------------------------------\n");
}

//Print The First Character Of A Team Colour
void print_colour(enum COLOUR c)
{
    switch(c)
    {
        case RED:
            printf("R");
            break;
            
        case BLU:
            printf("B");
            break;
            
        case YELLOW:
            printf("Y");
            break;
            
        case GREEN:
            printf("G");
            break;
            
        case PINK:
            printf("P");
            break;
            
        case ORANGE:
            printf("O");
            break;
            
        default:
            printf("Invalid Colour\n");
            break;
            
    }
}

//Print The Full Team Colour
void PRINT_COLOUR_LONG(enum COLOUR c)
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

//Remove an obstacle when there is no token on the left side of an obstacle in a single row
void REMOVE_OBSTACLE(Tile board[BOARD_ROWS][BOARD_COLS])
{
    bool no_token_found = true;
    int i = 0;
    int j = 0;
    
    //this nested loop will scan the board for a row without any tokens
    for (i = 0; i < BOARD_ROWS; i++)
    {
        //no_token_found is set back to true when the loop moves to the next row
        no_token_found = true;
        
        //BOARD_COLS is iterated to check for any tokens
        for (j = 0; j < BOARD_COLS; j++)
        {
            //when a token is found no_token_found is set to false and the loop is broken
            if(board[i][j].stack_top->data != NONE)
            {
                no_token_found = false;
                break;
            }
        }
        
        //if a token is found then this loop is used to find the obstacle and delete it
        if (no_token_found == true)
        {
            //j is set back to 0
            j = 0;
            while (j < BOARD_COLS)
            {
                //when an obstacle is found, it is set to false which stops it being printed onto the board
                if (board[i][j].is_obstacle)
                {
                    board[i][j].is_obstacle = false;
                }
                j++;
            }
        }
    }
}
