#ifndef A2I_CHESS_COMMANDS_H
#define A2I_CHESS_COMMANDS_H

/* Apple II <-> ESP Commands */
#define CHESS_GET_AI_MOVE     20
#define CHESS_GET_GAME_STATUS 22
#define CHESS_GET_BOARD       23
#define CHESS_MAKE_MOVE       21

/* Responses */
#define CHESS_INVALID_MOVE    123
#define CHESS_VALID_MOVE      124

/*
 * Responses from API...
 * "in_progress"
 * "black_won"
 * "white_won"
 * "white_won_resign"
 * "black_won_resign"
 * "stalemate"
 * "insufficient_material"
 * "fifty_rule_move"
 * "threefold_repitition"
 * "unknown"
 */

#define STATUS_IN_PROGRESS 200
#define STATUS_BLACK_WON 201
#define STATUS_WHITE_WON 202
#define STATUS_STALEMATE 205
#define STATUS_FIFTY_RULE_MOVE 207
#define STATUS_UNKNOWN 209
#define STATUS_UNHANDLED 210
#define STATUS_ERROR 211

#endif
