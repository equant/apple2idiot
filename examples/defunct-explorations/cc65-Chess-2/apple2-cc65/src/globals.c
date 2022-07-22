/*
 *	globals.c
 *	cc65 Chess
 *
 *	Created by Stefan Wessels, February 2014.
 *
 */

#include "types.h"
#include "globals.h"

/*-----------------------------------------------------------------------*/
char		gChessBoard[8][8];			// The chess board itself - row, col
char		gCursorPos[2][2];			// Remember last cursor pos for human players
char        gTile[2];                   // Tiles on board that user selected - linear 0..63 ; 0 = src, 1 = dest

char        state = STATE_NONE;
