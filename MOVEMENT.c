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
        
        while(!valid_token)
        {
            printf("Please Select A Token To Be Moved\n"
                   "Enter Row: ");
            scanf("%d", &r);
            
            printf("Enter Col: ");
            scanf("%d", &c);
            
            //CHECK IF THEY HAVE TRIED TO SIDESTEP SOMEONE ELSES TOKEN
            //You cannot sidestep a token that is not your own.
            if(GAME_BOARD[r][c].stack_top->data == p.team_col)
                valid_token = true;
            
            if(!valid_token) printf("You cannot sidestep someone elses token.\n");
        }
        
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
            
            if(a == 0 && !close_to_top) //UP & the token isn't at the highest row
            {
                move_up(GAME_BOARD, r, c);
                sidestep_complete = true;
            }
            else if (a == 1 && !close_to_bottom) //DOWN & the token isn't at the lowest row
            {
                move_down(GAME_BOARD, r, c);
                sidestep_complete = true;
            }
            else if(close_to_top || close_to_bottom)
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








