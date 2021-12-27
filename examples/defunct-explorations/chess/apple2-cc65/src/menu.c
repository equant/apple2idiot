#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <apple2.h>

#include "globals.h"
#include "menu.h"

void drawMenuBar() {
	cclearxy(0, 0, SIZE_X);	
    gotoxy(0,0);
	revers(1); printf("W"); 
	revers(0); printf("ifi Game | "); 
	revers(1); printf("L"); 
	revers(0); printf("ocal Game | "); 
	revers(1); printf("S"); 
	revers(0); printf("ettings | "); 
	revers(1); printf("Q"); 
	revers(0); printf("uit"); 
}

void fancy_hline(unsigned char x, unsigned char y) {
    gotoxy(x,y);
    printf("<><>-------------------------------<><>\n");
}
