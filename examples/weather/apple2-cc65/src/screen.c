/*

Screen handling

*/

#include <conio.h>
#include <string.h>


static unsigned char screen_bgc;
static unsigned char screen_borderc;
static unsigned char screen_textc;

static unsigned char *spaces = "                                                                                ";


/* initialize screen mode */
void InitScreen(unsigned char *title, unsigned char border, unsigned char bg, unsigned char text) {
  screen_borderc = bordercolor(border);
  screen_bgc = bgcolor(bg);
  screen_textc = textcolor(text);
  clrscr();
  revers(1);
  cprintf(title);
  revers(0);
}


/* restore basic screen mode */
void ExitScreen(void) {
  bordercolor(screen_borderc);
  bgcolor(screen_bgc);
  textcolor(screen_textc);
  clrscr();
}


/* Draw petscii box */
void DrawBox(unsigned char xsize, unsigned char ysize, unsigned char xpos, unsigned char ypos) {
  /* Top line */
  gotoxy(xpos,ypos);
  cputc(CH_ULCORNER);
  chline(xsize - 2);
  cputc(CH_URCORNER);

  /* Vertical line, left side */
  cvlinexy(xpos, ypos + 1, ysize - 2);

  /* Bottom line */
  cputc(CH_LLCORNER);
  chline(xsize - 2);
  cputc(CH_LRCORNER);

  /* Vertical line, right side */
  cvlinexy(xpos + xsize - 1, ypos + 1, ysize - 2);
}


/* Clear screen area */
void ClearBox(unsigned char xsize, unsigned char ysize, unsigned char xpos, unsigned char ypos) {
  unsigned char *s;
  unsigned char line;

  s = spaces + 80 - xsize;
  for (line = 0; line < ysize; ++line) {
    gotoxy(xpos, ypos + line);
    cprintf(s);
  }
}


/* print maxlen leftmost chars of string */
void PrintLeftString(unsigned char *string, unsigned char maxlen) {
  unsigned char c;

  if ((c = strlen(string)) <= maxlen) {
    cputs(string);
    cputs(spaces + 80 + c - maxlen);
  } else {
    c = string[maxlen];
    string[maxlen] = 0;
    cputs(string);
    string[maxlen] = c;
  }
}
