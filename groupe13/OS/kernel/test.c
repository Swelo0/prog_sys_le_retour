//////////////////////////////////////////////////////////////////////////////////////////
/// \file test.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of test functions.
//////////////////////////////////////////////////////////////////////////////////////////

#include "test.h"

//////////////////////////////////////////////////////////////////////////////////////////
void runTests()
{
    printf("The testing procedure begins ...");
    sleep(2000);
    printf(" NOW !\n\n");
    sleep(3000);
    
    printf("Testing colors :\n");
    printf("----------------\n\n");
    sleep(3000);
    
    printf("Function : set_text_color\n");
    printf("You should see all the available colors for characters :\n");
    for (int i = 0; i < NB_COLORS; i++)
    {
        set_text_color(i);
        printf("%d ", i);
    }
    set_text_color(WHITE);
    sleep(3000);
    
    printf("\n\nFunction : set_background_color\n");
    printf("You should see all the available colors for the background :\n");
    for (int i = 0; i < NB_COLORS; i++)
    {
        set_background_color(i);
        printf(" ");
    }
    set_background_color(BLACK);
    sleep(3000);
    
    printf("\n\nFunction : set_color, get_text_color, get_background_color\n");
    set_colors(GREEN, DARK_GREY);
    printf("The colors of this text are : %d (text=GREEN) and %d (background=DARK_GREY)\n",
           get_text_color(), get_background_color());
    set_colors(WHITE, BLACK);
    sleep(3000);
    
    printf("\nTesting cursor :\n");
    printf("----------------\n\n");
    sleep(3000);
    
    printf("Function : get_cursor_offset, set_cursor_position\n");
    printf("The line numbers are now displayed at the end of each line\n");
    uint8_t l, c;
    int oldOffset = get_cursor_offset();
    for (l = 0; l < TEXT_DISPLAY_LINES; l++)
    {
        set_cursor_position(l, TEXT_DISPLAY_COLUMNS - 3);
        print_int(l);
    }
    sleep(3000);
    
    set_cursor_offset(oldOffset);
    printf("\nFunction : set_cursor_offset, get_cursor_position\n");
    get_cursor_position(&l, &c);
    printf("The first character of this line was on line %d at column %d when printed\n", l, c);
    sleep(3000);
    
    printf("\nTesting print functions :\n");
    printf("-----------------------------\n\n");
    sleep(3000);
    
    printf("Function : print_char, print_str, print_int, print_hex, printf\n");
    printf("This is a character (=i) : %c\nThis is a string (=toto) : %s\n", 'i', "toto");
    printf("This is an integer (=1337) : %d\nThis is an hex integer (=0xAB42) : %x\n", 1337, 0xAB42);
    printf("This is a percentage : 10%%\n");
    sleep(3000);

//Test du sleep

    printf("\nTesting sleep function :\n");
    printf("-----------------------------\n\n");
    sleep(3000);

    printf("\n");
    printf("+----------------------------------------------\n");
    printf("          Before the 3 seconds sleep\n");
    printf("+----------------------------------------------\n");

    sleep(3000);

    printf("\n");
    printf("+----------------------------------------------\n");
    printf("          After the 3 seconds sleep\n");
    printf("+----------------------------------------------\n");
    
    printf("\nTesting the exception handler by doing a division by zero (the kernel will halt):\n");
    printf("-----------------------------\n\n");
    sleep(3000);

    uint8_t a = 10 / 0;
}

