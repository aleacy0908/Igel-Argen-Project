#include "MOVEMENT.h"


//Returns a random number from 0-5
int roll_die()
{
    return (rand() % 6);
}

void TAKE_TURN(Player p, Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS])
{
    enum COLOUR c = p.team_col;
    
    printf("~Turn ");
    PRINT_COLOUR_LONG(c);
    printf("~\n");
    
    //PART (A)
    int rolled_num = roll_die();
    printf("You Rolled The Number %d\n\n", rolled_num);
    
    //PART (B)
    char inp;
    
    //Ask if the user would like to perform a sidestep
    while((inp != 'Y') && (inp != 'N'))
    {
        printf("Would you like to perform a sidestep?(Y/N)\n");
        scanf(" %c", &inp);
        
        //Check for valid input
        if((inp != 'Y') && (inp != 'N'))
        {
            printf("Invalid Character. Try Again.\n\n");
        }
    }
    
    if(inp == 'Y')
    {
        int r,c;
        
        bool valid_token = false;
        bool is_stuck;
        
        do
        {
            printf("Please Select A Token To Be Moved\n"
                   "Enter Row: ");
            scanf("%d", &r);
            
            printf("Enter Col: ");
            scanf("%d", &c);
            
            is_stuck = token_stuck(GAME_BOARD, r, c);
            
            
            //If you own this token, you can sidestep it.
            if(GAME_BOARD[r][c].stack_top->data == p.team_col)
                valid_token = true;
            
            
            /* ERROR MESSAGES
             Valid Token: This means that you own the token. If you don't, then you cannot
             sidestep it.
             
             Is_Stuck: This is true/false. If its true, then we cannot sidestep this token.
             */
            if(!valid_token && !is_stuck)
                printf("You cannot sidestep this token as it is not yours. Try Again.\n");
            else if(valid_token && is_stuck)
                printf("TOKEN STUCK: This token is on an obstacle and cannot be moved yet. Try Again.\n");
            else if(!valid_token && is_stuck)
                printf("This token is STUCK and is not your own. Try Again.\n");
            
        
        } while(!valid_token || is_stuck);
        
        
        bool sidestep_complete = false;
        
        while(!sidestep_complete)
        {
            printf("Would you like to move this token up or down one tile?\n"
                   "0 For Up\n"
                   "1 For Down\n\n");
            
            int a;
            scanf(" %d", &a);
            
            bool close_to_top,close_to_bottom;
            
            close_to_top = (r == 0);
            close_to_bottom = (r == 5);
            
            /*The player wants to move UP & the token isn't too high on the board*/
            if(a == 0 && !close_to_top)
            {
                move_up(GAME_BOARD, r, c);
                sidestep_complete = true;
            }
            /*The player wants to move DOWN & the token isn't too low on the board*/
            else if (a == 1 && !close_to_bottom)
            {
                move_down(GAME_BOARD, r, c);
                sidestep_complete = true;
            }
            /*The token is too close to the edge for this move*/
            else if((close_to_top || close_to_bottom))
            {
                printf("\nTRY AGAIN: Your token is too close to the edge for this move.\n");
            }
            else
            {
                printf("Invalid Character Inputted.\n");
            }
        }
        
        print_board(GAME_BOARD);
    }
    
    
    //PART (C)
    int col;
    
    bool forward_move_succeeded = false;
    
    while(!forward_move_succeeded)
    {
        printf("You must move one token forward on row %d.\n", rolled_num);
        
        printf("Which token would you like to move?\n"
               "Enter Column: ");
        
        scanf("%d", &col);
        
        if(col < 0 || col > 5)
        {
            printf("\n\nInvalid Input. Try Again.\n");
        }
        else if(GAME_BOARD[rolled_num][col].stack_top->data != NONE)
        {
            move_forward(GAME_BOARD, &p, rolled_num, col);
            forward_move_succeeded = true;
        }
        else
        {
            printf("\n\nThere is no token on this tile.\n"
                   "Try Again.\n");
        }
    }
    
    print_board(GAME_BOARD);
    
    printf("\n\nTURN OVER\n\n");
    
    
}

void move_up(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c)
{
    /*
     r1 = original row
     c1 = original column
     */
    
    GAME_BOARD[r-1][c].stack_top = push(GAME_BOARD[r][c].stack_top->data, GAME_BOARD[r-1][c].stack_top);
    GAME_BOARD[r][c].stack_top = pop(GAME_BOARD[r][c].stack_top);
    
    GAME_BOARD[r][c].stack_count--;
    GAME_BOARD[r-1][c].stack_count++;
    
}


void move_down(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c)
{
    /*
     r1 = original row
     c1 = original column
     */
    GAME_BOARD[r+1][c].stack_top = push(GAME_BOARD[r][c].stack_top->data, GAME_BOARD[r+1][c].stack_top);
    GAME_BOARD[r][c].stack_top = pop(GAME_BOARD[r][c].stack_top);
    
    GAME_BOARD[r][c].stack_count--;
    GAME_BOARD[r+1][c].stack_count++;
}


void move_forward(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], Player *p, int r, int c)
{
    /*
     r1 = original row
     c1 = original column
     */
    
    GAME_BOARD[r][c+1].stack_top = push(GAME_BOARD[r][c].stack_top->data, GAME_BOARD[r][c+1].stack_top);
    GAME_BOARD[r][c].stack_top = pop(GAME_BOARD[r][c].stack_top);
    
    GAME_BOARD[r][c].stack_count--;
    GAME_BOARD[r][c+1].stack_count++;
    
    //INCREMENT SCORE
    //Check if a token is entering the last column i.e the winning one
    if((c+1) == (BOARD_COLS-1))
        p->score++;
    
}

bool token_stuck(Tile GAME_BOARD[BOARD_ROWS][BOARD_COLS], int r, int c)
{
    Tile tl = GAME_BOARD[r][c];
    
    //It can only be stuck if it's the first token on that tile
    //and that tile is an obstacle
    if(tl.stack_count == 1 && tl.is_obstacle)
    {
        
        for(int i = 0; i < c; i++)
        {
            /*
             We can only move a token on an obstacle if every token
             on that row has passed it already. Therefore, we need
             to check that the stack count is 0 on every
             tile before the obstacle.
             
             If there is any tile before our obstaclewhere stack count
             is greater than 0, then the token we're trying to move
             is still stuck.
             */
            
            if(GAME_BOARD[r][i].stack_count != 0)
            {
                return true;
            }
        }
        
    }
    
    return false;
}








