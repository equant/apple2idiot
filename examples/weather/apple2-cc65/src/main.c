#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <apple2.h>

#include "globals.h"
#include "menu.h"
#include "apple2idiot.h"

unsigned char i = 0;
char p;
char text[20];


void main(void)
{
    unsigned char key;

    while (key != ASCII_0) {    // Last menu item should be Quit
        clrscr();
        drawMenuBar();
        //cvlinexy(0,1,size_x);
        //fancy_hline(0,2);
        //fputs("enter some text: ", stdout);
        //fflush(stdout); /* http://c-faq.com/stdio/fflush.html */
        //fgets(text, sizeof text, stdin);
        //printf("\ntext = \"%s\"", text);
        //revers(1);
        gotoxy(0,SIZE_Y-1);
        printf("Selection:");
        cursor(1);
        //revers(0);
        //p = cgetc();
        key = toupper(cgetc());
        gotoxy(0,SIZE_Y-3);
        printf("cgetc() -> \"%c\"", key);

        switch((int)key) {
        case ASCII_0:
            printf("QUIT!");
            break;
        case ASCII_1:
            printf("COUNTRY!");
            write_string_to_ram("US", 0xC202);
            break;
        case ASCII_2:
            printf("City: ");
            fgets(text, sizeof text, stdin);
            write_string_to_ram(text, 0xC202);
            break;
        case ASCII_3:
            printf("UPDATE!");
            break;
        default:
            printf("DEFAULT!");
            break;
        }

    }
}
