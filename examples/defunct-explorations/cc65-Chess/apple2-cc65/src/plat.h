/*
 *	plat.h
 *	cc65 Chess
 *
 *	Created by Stefan Wessels, February 2014.
 *
 */

#ifndef _PLAT_H_
#define _PLAT_H_

void plat_Init(void);
void plat_UpdateScreen(void);
char plat_Menu(char **menuItems, char height, char *scroller);
void plat_DrawBoard(char clearLog);
void plat_DrawSquare(char position);
void plat_ShowSideToGoLabel(char side);
void plat_Highlight(char position, char color, char cursor);
void plat_ShowMessage(char *str, char color);
void plat_ClearMessage(void);
int plat_ReadKeys(char blocking);
void plat_Shutdown(void);

#endif //_PLAT_H_
