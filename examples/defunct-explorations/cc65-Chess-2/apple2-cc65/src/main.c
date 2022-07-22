/*
 *	main.c
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
void board_Init()
{
	char x,y,i;
	
	for(x=0; x < 8; x++)
	{
		for(y=0; y < 8; y++)
		{
			gChessBoard[x][y] = NONE;
		}
	}
				
	gChessBoard[0][0] = gChessBoard[7][0] = ROOK;
	gChessBoard[0][1] = gChessBoard[7][1] = KNIGHT;
	gChessBoard[0][2] = gChessBoard[7][2] = BISHOP;
	gChessBoard[0][3] = gChessBoard[7][3] = QUEEN;
	gChessBoard[0][4] = gChessBoard[7][4] = KING;
	gChessBoard[0][5] = gChessBoard[7][5] = BISHOP;
	gChessBoard[0][6] = gChessBoard[7][6] = KNIGHT;
	gChessBoard[0][7] = gChessBoard[7][7] = ROOK;

	for(i=0; i < 8; ++i)
	{
		gChessBoard[1][i] = PAWN;
		gChessBoard[6][i] = PAWN | PIECE_WHITE;
		gChessBoard[7][i] |= PIECE_WHITE;
	}
	
	// Not part of the board but does need resetting for every game
	gCursorPos[SIDE_BLACK][1] = gCursorPos[SIDE_WHITE][1] = 4;
	gCursorPos[SIDE_BLACK][0] = 1;
	gCursorPos[SIDE_WHITE][0] = 6;
}

/*-----------------------------------------------------------------------*/
// Internal function Prototype
void gameLoop(void);
void init(void);

/*-----------------------------------------------------------------------*/
int main()
{
	init();

    while (state != STATE_QUIT) {
        switch(state) {
            case STATE_AI_GAME:
                break;
            //case STATE_NONE:
                //break;
            default:
                gameLoop();
                break;
        }
    }
	
	plat_Shutdown();
	return 0;
}

/*-----------------------------------------------------------------------*/
void init()
{
	board_Init();
	plat_Init();
}

/*-----------------------------------------------------------------------*/
void gameLoop()
{
	char side = SIDE_WHITE, outcome = OUTCOME_OK;

	plat_DrawBoard(1);
	while(outcome != OUTCOME_QUIT)
	{
		outcome = human_Play(side);
		side = 1 - side;
	}
}
