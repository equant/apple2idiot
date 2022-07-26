/*
 *	human.c
 *	cc65 Chess
 *
 *	Created by Stefan Wessels, February 2014.
 *
 */

#include "types.h"
#include "globals.h"
#include "human.h"
#include "plat.h"

#include "apple2idiot.h"
#include "../../../chess/chess_commands.h"
#include "../../../../arduino-lib/Apple2Idiot/A2I_commands.h"

/*-----------------------------------------------------------------------*/
// Internal function Prototype
void human_ProcessInput(int keyMask);
void human_ProcessToggle(int keyMask, char side, char tile);

/*-----------------------------------------------------------------------*/
// Track the user controlled curson on the board
static char sc_cursorX, sc_cursorY;

/*-----------------------------------------------------------------------*/
// Handle the cursor movement
void human_ProcessInput(int keyMask)
{
	switch(keyMask)
	{
		case INPUT_UP:
			if(!sc_cursorY)
				sc_cursorY = 7;
			else
				--sc_cursorY;
		break;

		case INPUT_RIGHT:
			if(7==sc_cursorX)
				sc_cursorX = 0;
			else
				++sc_cursorX;
		break;

		case INPUT_DOWN:
			if(7==sc_cursorY)
				sc_cursorY = 0;
			else
				++sc_cursorY;
		break;

		case INPUT_LEFT:
			if(!sc_cursorX)
				sc_cursorX = 7;
			else
				--sc_cursorX;
		break;
	}
}

/*-----------------------------------------------------------------------*/
// Main routine when it's a human player's turn.
// The routine is sort-of in 2 parts. The bit before the user key is read
// and the bit after the key is read.
char human_Play(char side)
{
	int keyMask = INPUT_MOTION;
	char selector = 0;

	// get this sides' cursor
	sc_cursorY = gCursorPos[side][0];
	sc_cursorX = gCursorPos[side][1];

	gTile[0] = sc_cursorY * 8 + sc_cursorX;
	
	do
	{
		if(keyMask & INPUT_MOTION)
		{
			// Show the cursor
			plat_Highlight(gTile[0], selector ? HCOLOR_SELECTED : gChessBoard[sc_cursorY][sc_cursorX] == NONE ? HCOLOR_EMPTY : HCOLOR_VALID, 1);
			if(selector)
			{
				plat_Highlight(gTile[1], HCOLOR_ATTACK, 1);
			}
		}

		// Get input
		keyMask = plat_ReadKeys(1);
		
		if(keyMask & INPUT_MOTION)
		{
			// Erase the cursor and move it
			plat_DrawSquare(gTile[selector]);
			human_ProcessInput(keyMask & INPUT_MOTION);
			gTile[selector] = sc_cursorY * 8 + sc_cursorX;
			plat_DrawSquare(gTile[selector]);
		}
		else if(keyMask & INPUT_MENU)
		{
			// Drop out so the menu can be displayed
			return OUTCOME_MENU;
		}
		else if(keyMask & INPUT_BACKUP)
		{
			// If a piece was selected, deselct the piece
			if(selector)
			{
				plat_DrawSquare(gTile[selector]);
				selector = 0;
				sc_cursorY = gTile[0] / 8;
				sc_cursorX = gTile[0] & 7;
				keyMask = INPUT_MOTION;
			}
			// Otherwise bring up the menu
			else
				return OUTCOME_MENU;
		}
		else if(keyMask & INPUT_SELECT)
		{
			// Check that the piece selected is on the side of the player playing
			if(!selector && (gChessBoard[sc_cursorY][sc_cursorX] >> 7) == side)
			{
				// If the cursor is on a piece of this turn, that has moved and no other piece
				// has yet been selected, then select this piece
				++selector;
				gTile[1] = gTile[0];
				keyMask = INPUT_MOTION; // Force a cursor re-draw
			}
			else if(gTile[0] == gTile[1])
			{
				// If the selected tile is re-selected, deselect it
				--selector;
				// Since plat_Highlight doesn't undraw selected, just draw this tile 
				plat_DrawSquare(gTile[0]);
				keyMask = INPUT_MOTION;	// force a redraw (which should have made the plat_Drawsquae above unnecessary)
			}
			else if(selector)
			{
				// Doesn't consider if this is a valid move, just does it
                
                //write_string_to_ram(RAM_DATA_START_ADDRESS, player_move);
                write_byte(APPLE_COMMAND_ADDRESS, CHESS_MAKE_MOVE);

				gChessBoard[sc_cursorY][sc_cursorX] = gChessBoard[gTile[0]/8][gTile[0]&7];
				gChessBoard[gTile[0]/8][gTile[0]&7] = NONE;
				plat_DrawSquare(gTile[0]);
				plat_DrawSquare(gTile[1]);
				++selector;
			}
		}
	} while(selector < 2);

	// Save the cursor positions for next time
	gCursorPos[side][0] = sc_cursorY;
	gCursorPos[side][1] = sc_cursorX;
	
	return OUTCOME_OK;
}
