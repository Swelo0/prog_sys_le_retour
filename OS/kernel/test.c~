//////////////////////////////////////////////////////////////////////////////////////////
/// \file test.c
/// \author Benjamin Ganty
/// \date 4 november 2015
/// \brief Implementation of test functions.
//////////////////////////////////////////////////////////////////////////////////////////

#include "test.h"

#include "io.h"

//////////////////////////////////////////////////////////////////////////////////////////
static void sleep(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 1000000; j++);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void runTests()
{
    printf("The testing procedure begins ...");
    sleep(300);
    printf(" NOW !\r\n\n");
    sleep(200);
    
    printf("Testing colors :\r\n");
    printf("----------------\r\n\n");
    sleep(200);
    
    printf("Function : set_text_color\r\n");
    printf("You should see all the available colors for characters :\r\n");
    for (int i = 0; i < NB_COLORS; i++)
    {
        set_text_color(i);
        printf("%d ", i);
    }
    set_text_color(WHITE);
    sleep(800);
    
    printf("\r\n\nFunction : set_background_color\r\n");
    printf("You should see all the available colors for the background :\r\n");
    for (int i = 0; i < NB_COLORS; i++)
    {
        set_background_color(i);
        printf(" ");
    }
    set_background_color(BLACK);
    sleep(800);
    
    printf("\r\n\nFunction : set_color, get_text_color, get_background_color\r\n");
    set_colors(GREEN, DARK_GREY);
    printf("The colors of this text are : %d (text=GREEN) and %d (background=DARK_GREY)\r\n",
           get_text_color(), get_background_color());
    set_colors(WHITE, BLACK);
    sleep(800);
    
    printf("\r\nTesting cursor :\r\n");
    printf("----------------\r\n\n");
    sleep(200);
    
    printf("Function : get_cursor_offset, set_cursor_position\r\n");
    printf("The line numbers are now displayed at the end of each line\r\n");
    uint8_t l, c;
    int oldOffset = get_cursor_offset();
    for (l = 0; l < TEXT_DISPLAY_LINES; l++)
    {
        set_cursor_position(l, TEXT_DISPLAY_COLUMNS - 3);
        print_int(l);
    }
    sleep(800);
    
    set_cursor_offset(oldOffset);
    printf("\r\nFunction : set_cursor_offset, get_cursor_position\r\n");
    get_cursor_position(&l, &c);
    printf("The first character of this line was on line %d at column %d when printed\r\n", l, c);
    sleep(800);
    
    printf("\r\nTesting print functions :\r\n");
    printf("-----------------------------\r\n\n");
    sleep(200);
    
    printf("Function : print_char, print_str, print_int, print_hex, printf\r\n");
    printf("This is a character (=i) : %c\r\nThis is a string (=toto) : %s\r\n", 'i', "toto");
    printf("This is an integer (=1337) : %d\r\nThis is an hex integer (=0xAB42) : %x\r\n", 1337, 0xAB42);
    printf("This is a percentage : 10%%\r\n");
    sleep(800);
    
    printf("\r\nTests are over. Because of the scrolling, you should now see some lines without their numbers on the right.");
}

