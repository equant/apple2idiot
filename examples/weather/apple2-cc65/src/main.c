#include <stdio.h>
#include <conio.h>
#include <peekpoke.h>
#include <apple2.h>

//#include <stdlib.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <peekpoke.h>

#include "main.h"
#include "inputline.h"

unsigned char i = 0;
char p;
char text[20];

//unsigned char menuEntries[8][4] = {"HLP", "END", "SEL", "REF", "CPY", "REN", "MDR", "DEL"};
//unsigned char menuEntries[MENU_LENGTH][MENU_WORD_LENGTH] = {"CHANNEL", "MISC"};

// Writes the menu bar at the top of the screen
// which is scaled to the current screen size.
void writeMenuBar(void)
{
	static unsigned char i, x;
	
	//cclearxy(0, bottom, size_x);	
	cclearxy(0, 0, SIZE_X);	
	
    for(i = 0; i < MENU_LENGTH; i++){
		//x = i*5;
		x = (MENU_WORD_LENGTH + 1) * i;
        revers(1);
        //gotoxy(x, bottom); cputc('1' + i);
        gotoxy(x, 0); cputc('1' + i);
        revers(0);
        //cputsxy(x + 1, bottom, menuEntries[i]);
        cputsxy(x + 1, 0, menuEntries[i]);
    }
	revers(0);
}


void main(void)
{
    //screensize(&size_x, &size_y);
    clrscr();
    writeMenuBar();
    //cvlinexy(0,1,size_x);
    gotoxy(0, 1);
    chline(SIZE_X);
    gotoxy(0, 3);
    //printf("Screensize is %d by %d\n", size_x, size_y);
	printf("Hello, world!\n");
    for (i=0;i<8;i++)
    {
        p = PEEK(0xC200+i);
        printf("(%u) -> %d, %c\n", 0xC200+i, p, p);
    }
    cursor(1);
    p = cgetc();
    gotoxy(0, SIZE_Y-5);
    printf("You said: %c\n", p);
    //inputline(1, 17, 38, 53, ibuf, NULL);
    //gotoxy(1, 17);
    //printf("YO: %c\n", ibuf);
    //cursor(1);
    //p = cgetc();
    fputs("enter some text: ", stdout);
    fflush(stdout); /* http://c-faq.com/stdio/fflush.html */
    fgets(text, sizeof text, stdin);
    printf("\ntext = \"%s\"\n", text);
    //printf("YO: %c\n", ibuf);
    printf("Press any key to exit.");
    cursor(1);
    p = cgetc();

}

