#include "SETUP_BOARD.h"

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
        
        /*
         Search for the colour and if
         none is found then the input
         was invalid
         */
        
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
}

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

void print_board(Tile board[BOARD_ROWS][BOARD_COLS]){
    printf("                THE BOARD\n");
    for(int i =0; i < BOARD_ROWS; i++){
        
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < BOARD_COLS; j++){
            
            if(board[i][j].stack_top != NULL){
                printf("| ");
                print_colour(board[i][j].stack_top->data);
                printf(" ");
                
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].is_obstacle)
                    printf("| %c ", 'X');
                //c is assigned an empty space otherwise
                else printf("| %c ", ' ');
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
    printf("   -------------------------------------\n");
}


//TODO: ADAPT THIS FUNCTION WITH OTHER ONE IN MAIN:

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


