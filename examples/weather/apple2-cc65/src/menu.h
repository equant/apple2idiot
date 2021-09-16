/*

Menu handling

*/

#define CH_CURS_UP      0x0B
#define CH_CURS_DOWN    0x0A

#define MENU_CANCEL 0

#define MENU_YES 1
#define MENU_NO 0


extern unsigned char menu_bc; /* border color */
extern unsigned char menu_tc; /* title color */
extern unsigned char menu_nc; /* normal item color */
extern unsigned char menu_ic; /* inactive item color */

extern unsigned char menu_xpos; /* default menu position */
extern unsigned char menu_ypos;

typedef enum itemstates {
  ISTATE_NORMAL,
  ISTATE_INACTIVE
} ItemState;

typedef struct item {
  struct item *next;
  struct item *prev;
  unsigned char id;
  unsigned char *name;
  ItemState state;
} Item;

typedef struct menu {
  unsigned char visible;
  unsigned char numitems;
  unsigned char current;
  unsigned char xpos;
  unsigned char ypos;
  unsigned char width;
  unsigned char height;
  unsigned char *title;
  Item *firstitem;
} Menu;


/* Set menu colors */
#define SetMenuColors(BC, TC, NC, IC) \
  menu_bc = (BC); \
  menu_tc = (TC); \
  menu_nc = (NC); \
  menu_ic = (IC);

/* Set default menu position */
#define SetMenuDefaultPosition(XPOS, YPOS) \
  menu_xpos = (XPOS); \
  menu_ypos = (YPOS);

/* Initialize an empty menu. */
Menu *NewMenu(void);

/* Deallocate menu resources. */
void DestroyMenu(Menu *menu);

/* Set the title. */
void SetMenuTitle(Menu *menu, unsigned char *title);

/* Add an item to the menu. id is the value that SelectMenu will return, which must not be 0. */
signed char AddMenuItem(Menu *menu, unsigned char id, ItemState state, unsigned char *name);

/* Delete an item from the menu. */
signed char DelMenuItem(Menu *menu, unsigned char id);

/* Set item state to normal or inactive. */
signed char SetItemState(Menu *menu, unsigned char id, ItemState state);

/* Display the menu on the screen. */
void ShowMenu(Menu *menu);
signed char DrawMenu(Menu *menu);

/* Erase the menu from the screen. */
void HideMenu(Menu *menu);

/* Let the user choose a menu item. ShowMenu() first. */
signed char SelectMenu(Menu *menu);

/* Ask if user is sure */
unsigned char AskAreYouSure(Menu *menu);

/* Display message, wait for enter */
void DisplayMessage(unsigned char *message);
