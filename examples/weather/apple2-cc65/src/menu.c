#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <apple2.h>

#include "globals.h"
#include "menu.h"

#define MENU_LENGTH 4
#define MENU_WORD_LENGTH 8
unsigned char menuEntries[MENU_LENGTH][MENU_WORD_LENGTH] = {"Country", "City", "Update", "Quit"};

void drawMenuBar() {
	static unsigned char i;
	static unsigned char x_offset;

    x_offset = 0;

	cclearxy(0, 0, SIZE_X);	
    gotoxy(0,0);
    for(i = 0; i < MENU_LENGTH; i++){
        //printf("%d, %d, %d\n", i, strlen(menuEntries[i]), x_offset);
        revers(1);
        gotoxy(x_offset, 0); cputc('1' + i);
        revers(0);
        cputsxy(x_offset + 1, 0, menuEntries[i]);
        x_offset += strlen(menuEntries[i]) + 1;
    }
	revers(0);
}

void fancy_hline(unsigned char x, unsigned char y) {
    gotoxy(x,y);
    printf("<><>-------------------------------<><>\n");
}
