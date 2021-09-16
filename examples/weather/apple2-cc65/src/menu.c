/*

Menu handling

*/


#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <apple2.h>
#include "menu.h"
#include "screen.h"


unsigned char menu_bc =  1; /* border color */
unsigned char menu_tc =  7; /* title color */
unsigned char menu_nc = 13; /* normal item color */
unsigned char menu_ic =  5; /* inactive item color */

unsigned char menu_xpos = 5; /* default menu position */
unsigned char menu_ypos = 2;


void DrawItem(Item *item, unsigned char xpos, unsigned char ypos, unsigned char current);


Menu *NewMenu(void) {
  register Menu *menu;

  if ((menu = malloc(sizeof(*menu))) == NULL) {
    return(NULL);
  }
  menu->visible = 0;
  menu->numitems = 0;
  menu->current = 0;
  menu->xpos = menu_xpos;
  menu->ypos = menu_ypos;
  menu->width = 0;
  menu->height = 0;
  menu->title = NULL;
  menu->firstitem = NULL;
  return(menu);
}


void SetMenuTitle(Menu *menu, unsigned char *title) {
  unsigned char l;

  menu->title = title;
  if ((l = strlen(title)) > menu->width) {
    menu->width = l;
  }
}


signed char AddMenuItem(Menu *menu, unsigned char id, ItemState state, unsigned char *name) {
  register Item *item;
  int l;

  if (id == MENU_CANCEL) { /* 0 is reserved for cancelling */
    return(-1);
  }
  if (menu->numitems == 0) {
    if ((menu->firstitem = malloc(sizeof(*item))) == NULL) {
      return(-1);
    }
    item = menu->firstitem;
    item->prev = NULL;
  } else {
    item = menu->firstitem;
    while (item->next) {
      item = item->next;
    }
    if ((item->next = malloc(sizeof(*item))) == NULL) {
      return(-1);
    }
    item->next->prev = item;
    item = item->next;
  }
  item->next = NULL;
  item->id = id;
  item->name = name;
  item->state = state;
  ++(menu->numitems);
  if ((l = strlen(name)) > menu->width) {
    menu->width = l;
  }
  if (menu->numitems > menu->height) {
    menu->height = menu->numitems;
  }
  return(0);
}


signed char DelMenuItem(Menu *menu, unsigned char id) {
  register Item *item;

  if (menu->numitems) {
    item = menu->firstitem;
    while (item) {
      if (item->id == id) {
	if (menu->firstitem == item) {
	  menu->firstitem = item->next;
	  item->next->prev = NULL;
	  free(item);
	} else {
	  item->prev->next = item->next;
	  item->next->prev = item->prev;
	  free(item);
	}
	--(menu->numitems);
	return(0);
      }
      item = item->next;
    }
  }
  return(-1);
}


signed char SetItemState(Menu *menu, unsigned char id, ItemState state) {
  register Item *item;

  if (menu->numitems) {
    item = menu->firstitem;
    while (item) {
      if (item->id == id) {
	item->state = state;
	return(0);
      }
      item = item->next;
    }
  }
  return(-1);
}


void ShowMenu(Menu *menu) {
  if (menu->visible == 0) {
    menu->visible = 1;
    DrawMenu(menu);
  }
}


void HideMenu(Menu *menu) {
  if (menu->visible) {
    menu->visible = 0;
    DrawMenu(menu);
  }
}


Item *FindItemNumber(Menu *menu, unsigned char itemnum) {
  Item *item;

  item = menu->firstitem;
  while (itemnum) {
    if (item->next) {
      item = item->next;
      --itemnum;
    } else {
      return(NULL);
    }
  }
  return(item);
}


Item *FindItem(Menu *menu, unsigned char id) {
  Item *item;

  item = menu->firstitem;
  while (item->id != id) {
    if (item->next) {
      item = item->next;
    } else {
      return(NULL);
    }
  }
  return(item);
}


signed char SelectMenu(register Menu *menu) {
  unsigned char c;
  register Item *item;

  if ((item = FindItemNumber(menu, menu->current)) == NULL) {
    return(-1);
  }
  if (menu->visible == 0) {
    return(-1);
  }
  while(c = cgetc()) {
    switch (c) {
    case 27:
    case 3:
      return(MENU_CANCEL);
    case '\r':
    case '\n':
      if (item->state == ISTATE_NORMAL) {
	return(item->id);
      }
      break;
      /*
    case CH_CURS_DOWN:
      if (menu->current + 1 < menu->numitems) {
	DrawItem(item, menu->xpos + 1, menu->ypos + menu->current + 3, 0);
	item = item->next;
	++(menu->current);
	DrawItem(item, menu->xpos + 1, menu->ypos + menu->current + 3, 1);
      }
      break;
    case CH_CURS_UP:
      if (menu->current > 0) {
	DrawItem(item, menu->xpos + 1, menu->ypos + menu->current + 3, 0);
	item = item->prev;
	--(menu->current);
	DrawItem(item, menu->xpos + 1, menu->ypos + menu->current + 3, 1);
      }
      break;
      */
    }
  }
}


void DestroyMenu(Menu *menu) {
  Item *item;
  Item *next;

  if (menu->numitems) {
    item = menu->firstitem;
    while (item) {
      next = item->next;
      free(item);
      item = next;
    }
  }
  free(menu);
}


void DrawItem(Item *item, unsigned char xpos, unsigned char ypos, unsigned char current) {
  unsigned char c;

  gotoxy(xpos, ypos);
  if (current) {
    revers(1);
  }
  if (item->state == ISTATE_NORMAL) {
    c = textcolor(menu_nc);
    cprintf(item->name);
  } else {
    c = textcolor(menu_ic);
    cprintf(item->name);
  }
  textcolor(c);
  revers(0);
}


signed char DrawMenu(register Menu *menu) {
  unsigned char l = 0;
  Item *item;

  if (menu->numitems == 0) {
    return(-1);
  } else {
    if (menu->title == NULL) {
      return(-1);
    } else {
      if (menu->visible) {
	textcolor(menu_bc);
	DrawBox(menu->width+2,menu->height+4,menu->xpos,menu->ypos);
	gotoxy(menu->xpos + 1, menu->ypos + 1);
	textcolor(menu_tc);
	cprintf(menu->title);
	item = menu->firstitem;
	while (item) {
	  DrawItem(item, menu->xpos + 1, menu->ypos + l + 3, menu->current == l ? 1 : 0);
	  item = item->next;
	  ++l;
	}
      } else {
	ClearBox(menu->width+2,menu->height+4,menu->xpos,menu->ypos);
      }
    }
  }
}


/* Ask if user is sure */
unsigned char AskAreYouSure(Menu *menu) {
  unsigned char x, y, sx, sy;

  screensize(&sx, &sy);

  if ((x = menu->xpos + 3) + 15 > sx) {
    x = sx - 16;
  }
  if ((y = menu->ypos + menu->current + 4) + 3 > sy) {
    y = sy - 3;
  }

  textcolor(menu_bc);
  DrawBox(17, 3, x, y);
  ClearBox(15, 1, x + 1, y + 1);
  textcolor(menu_nc);
  cputsxy(x + 1, y + 1, "Are you sure? ");

  while (1) {
    cursor(1);
    sx = cgetc();
    cursor(0);
    switch (sx) {

    case 'y':
    case 'Y':
      ClearBox(17, 3, x, y);
      return(1);
      break;

    case 'n':
    case 'N':
      ClearBox(17, 3, x, y);
      return(0);
      break;

    default:
      break;

    }
  }
}


/* Display message, wait for enter */
void DisplayMessage(unsigned char *message) {
  unsigned char l = strlen(message);

  textcolor(menu_bc);
  DrawBox(l + 2, 5, 20 - (l>>1) - (l & 1), 10);
  ClearBox(l, 3, 21 - (l>>1) - (l & 1), 11);
  textcolor(menu_nc);
  cputsxy(21 - (l>>1) - (l & 1), 11, message);
  revers(1);
  cputsxy(18, 13, " OK ");
  revers(0);
  while (cgetc() != 13);
  ClearBox(l + 2, 5, 20 - (l>>1) - (l & 1), 10);
}
