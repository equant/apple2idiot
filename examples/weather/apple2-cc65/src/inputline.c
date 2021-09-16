/*
 * This code is not original to slapple2, I took it from cvote.
 */

#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <apple2.h>
#include "screen.h"
#include "menu.h"


unsigned char ibuf[100];
static unsigned char allowme[256];


unsigned char ptoa(unsigned char p) {
  unsigned char a = p;

  if (p >= 192) {
    if (p >= 224) {
      if (p == 255) {
	a = 126;
      } else {
	a -= 64;
      }
    } else {
      a -= 96;
    }
  }
  return(a);
}

void printbuf(unsigned char x, unsigned char y, unsigned char width, unsigned char *buffer) {
  gotoxy(x, y);
  PrintLeftString(buffer, width);
  sprintf("%c", buffer);
}


unsigned char inputline(unsigned char x, unsigned char y, unsigned char width,
			unsigned char maxlen, unsigned char *buffer, unsigned char *allowed) {
  unsigned char offset = 0, pos = 0;
  unsigned char len, i, c;

  pos = len = strlen(buffer);
  if (len > maxlen) {
    pos = len = maxlen;
    buffer[pos] = 0;
  }
  if (len >= width) {
    offset += len - width + 1;
    pos -= offset;
  }
  printbuf(x, y, width, buffer + offset);
  cursor(1);

  while (1) {

    gotoxy(0, 1);
    cprintf("pos = %2d, offset = %2d, len = %2d", pos, offset, len);
    gotoxy(x + pos, y);
    switch (c = cgetc()) {

    default:
      c = ptoa(c);
      if (allowme[c] && len < maxlen) {
        ++len;
        memmove(buffer + pos + offset + 1, buffer + pos + offset, strlen(buffer + pos + offset) + 1);
        buffer[pos + offset] = c;
        buffer[len] = 0;
        printbuf(x, y, width, buffer + offset);
      }

      // fall through

    case CH_CURS_RIGHT:
      if (pos + offset < len) {
        if (pos < width - 1) {
          pos += 1;
        } else if (len > offset + pos) {
          offset += 1;
          if (offset + pos == len) {
            cputsxy(x + width - 1, y, " ");
          }
          printbuf(x, y, width, buffer + offset);
        }
      }
      break;

    case CH_CURS_LEFT:
      if (pos > 0) {
        pos -= 1;
          } else if (offset > 0) {
        offset -= 1;
        printbuf(x, y, width, buffer + offset);
      }
      break;

    case 3: // stop
      len = 0;
      // fall through

    case 13: // return
      ClearBox(width, 1, x, y);
      cursor(0);
      return(len);
      break;

    case 20: // del
      if (pos || offset) {
	if (pos) {
	  pos -= 1;
	} else {
	  offset -= 1;
	}
	i = offset + pos;
	while (buffer[i]) {
	  buffer[i] = buffer[i+1];
	  ++i;
	}
	--len;
	if (offset + pos == len) {
	  cputsxy(x + pos, y, " ");
	} else if (len - offset < width) {
	  cputsxy(x + len - offset, y, " ");
	}
	printbuf(x, y, width, buffer + offset);
      }
      break;

    case 19: // home
      if (pos || offset) {
	pos = offset = 0;
	printbuf(x, y, width, buffer + offset);
      }
      break;

    case 147: // clear
      pos = offset = len = 0;
      buffer[0] = 0;
      ClearBox(width, 1, x, y);
      break;

    }

  }
}
