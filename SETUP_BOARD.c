#include "SETUP_BOARD.h"
#include "struct_setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

enum COLOUR {
    RED, BLU, GREEN, YELLOW, PINK, ORANGE
} COLOUR;

void CHOOSE_COLOURS(unsigned int num_players, struct Player player_arr[], int col_chars[], enum COLOUR)
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
