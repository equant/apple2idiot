/*
 *	types.h
 *	cc65 Chess
 *
 *	Created by Stefan Wessels, February 2014.
 *
 */

#ifndef _TYPES_H_
#define _TYPES_H_

/**********************************************************/
// Stuff from my old chess code (NPH)

#define ASCII_L 76
#define ASCII_Q 81
#define ASCII_S 83
#define ASCII_W 87
#define BACKSPACE 8

#define SIZE_X 40
#define SIZE_Y 24

#define STATE_NONE 0
#define STATE_LOCAL_GAME 1
#define STATE_QUIT 27

#define CARD_ADDRESS 0xC200
#define ESP_COMMAND_ADDRESS 0xC200
#define APPLE_COMMAND_ADDRESS 0xC201
#define RAM_DATA_START_ADDRESS 0xC202

#define ESP_TIMEOUT 5555

/**********************************************************/

#define SET_BIT(x)			(1<<(x))

#define SIDE_BLACK			0
#define SIDE_WHITE			1
#define NUM_PIECES_SIDE		16

#define HCOLOR_WHITE		1
#define HCOLOR_BLACK		2
#define HCOLOR_EMPTY		4
#define HCOLOR_VALID		5
#define HCOLOR_INVALID		2
#define HCOLOR_SELECTED		6
#define HCOLOR_ATTACK		3

#define PIECE_WHITE			SET_BIT(7)
#define PIECE_DATA			(SET_BIT(0) | SET_BIT(1) | SET_BIT(2))

#define INPUT_UP			SET_BIT(0)
#define INPUT_RIGHT			SET_BIT(1)
#define INPUT_DOWN			SET_BIT(2)
#define INPUT_LEFT			SET_BIT(3)
#define INPUT_BACKUP		SET_BIT(4)
#define INPUT_TOGGLE_A		SET_BIT(5)
#define INPUT_TOGGLE_B		SET_BIT(6)
#define INPUT_TOGGLE_D		SET_BIT(7)
#define INPUT_SELECT		SET_BIT(8)
#define INPUT_MENU			SET_BIT(9)
#define INPUT_UNDO			SET_BIT(10)
#define INPUT_REDO			SET_BIT(11)
#define INPUT_UNDOREDO		(INPUT_UNDO | INPUT_REDO)
#define INPUT_MOTION		(INPUT_UP | INPUT_RIGHT | INPUT_DOWN | INPUT_LEFT)
#define INPUT_TOGGLE		(INPUT_TOGGLE_A | INPUT_TOGGLE_B | INPUT_TOGGLE_D)

enum
{
	NONE,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN,
};

enum
{
	OUTCOME_INVALID,
	OUTCOME_OK,
	OUTCOME_CHECK,
	OUTCOME_CHECKMATE,
	OUTCOME_DRAW,
	OUTCOME_STALEMATE,
	OUTCOME_MENU,
	OUTCOME_ABANDON,
	OUTCOME_QUIT,
};

#define STATE_NONE 0
#define STATE_LOCAL_GAME 1
#define STATE_AI_GAME 1
#define STATE_QUIT 27

#endif //_TYPES_H_
