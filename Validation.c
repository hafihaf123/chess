/*
 * =====================================================================================
 *
 *       Filename:  Validation.c
 *
 *    Description: implementation of the Validation.h header
 *
 *        Version:  1.0
 *        Created:  02/05/24 12:28:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (Michal Buchman), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <ctype.h>
#include "Validation.h"

int validateMove(struct Validation obj) {
	if (obj.fromRank == obj.toRank && obj.fromFile == obj.toFile) return -1;
	switch (obj.board->board[obj.fromFile][obj.fromRank].type) {
		case PAWN:
			return validatePawnMove(obj);
		case KNIGHT:
			return validateKnightMove(obj);
		case BISHOP:
			return validateBishopMove(obj);
		case ROOK:
			return validateRookMove(obj);
		case QUEEN:
			return validateQueenMove(obj);
		case KING:
			return validateKingMove(obj);
		case EMPTY:
			return -1;
	}
	return -1;
}

int validatePawnMove(struct Validation obj) {
	struct Piece pawn = obj.board->board[obj.fromFile][obj.fromRank];
	switch (pawn.color) {
		case WHITE:
			//capturing with a pawn
			if (obj.fromFile != obj.toFile) {
				//must be obj.to an adjacent file
				if (abs(obj.toFile - obj.fromFile) > 1) return 0;
				//the rank must be one up
				if (obj.toRank != obj.fromRank + 1) return 0;
				//if there isn't a piece, it cannot be taken :)
				if (obj.board->board[obj.toFile][obj.toRank].type == EMPTY) return 0;
				//handling pawn promotion
				if (obj.toRank == 7) {
					enum PieceType promoteToType = handlePromotion();
					if (promoteToType == EMPTY) return 0;
					obj.board->board[obj.fromFile][obj.fromRank].type = promoteToType;
				}
				//if all conditions are satisfied, the move is valid
				return 1;
			}

			//checking if there is a piece in front of the pawn
			if (obj.board->board[obj.fromFile][obj.fromRank+1].type != EMPTY) return 0;
			//the pawn can only move 2 squares if it is on the starting rank
			if (obj.toRank == obj.fromRank + 2) {
				if (obj.fromRank != 1) return 0;
				if (obj.board->board[obj.fromFile][obj.fromRank+2].type != EMPTY) return 0;
			}
			//the pawn can normally move only 1 square up
			else if (obj.toRank != obj.fromRank + 1) return 0;
			//handling pawn promotion
			if (obj.toRank == 7) {
				enum PieceType promoteToType = handlePromotion();
				if (promoteToType == EMPTY) return 0;
				obj.board->board[obj.fromFile][obj.fromRank].type = promoteToType;
			}
			//if all conditions are satisfied, the move is valid
			return 1;
		case BLACK:
			//capturing with a pawn
			if (obj.fromFile != obj.toFile) {
				//must be obj.to an adjacent file
				if (abs(obj.toFile - obj.fromFile) > 1) return 0;
				//the rank must be one down
				if (obj.toRank != obj.fromRank - 1) return 0;
				//if there isn't a piece, it cannot be taken :)
				if (obj.board->board[obj.toFile][obj.toRank].type == EMPTY) return 0;
				//handling pawn promotion
				if (obj.toRank == 0) {
					enum PieceType promoteToType = handlePromotion();
					if (promoteToType == EMPTY) return 0;
					obj.board->board[obj.fromFile][obj.fromRank].type = promoteToType;
				}
				//if all conditions are satisfied, the move is valid
				return 1;
			}

			//checking if there is a piece in front of the pawn
			if (obj.board->board[obj.fromFile][obj.fromRank-1].type != EMPTY) return 0;
			//the pawn can only move 2 squares if it is on the starting rank
			if (obj.toRank == obj.fromRank - 2) {
				if (obj.fromRank != 6) return 0;
				if (obj.board->board[obj.fromFile][obj.fromRank-2].type != EMPTY) return 0;
			}
			//the pawn can normally move only 1 square down
			else if (obj.toRank != obj.fromRank - 1) return 0;
			//handling pawn promotion
			if (obj.toRank == 0) {
				enum PieceType promoteToType = handlePromotion();
				if (promoteToType == EMPTY) return 0;
				obj.board->board[obj.fromFile][obj.fromRank].type = promoteToType;
			}
			//if all conditions are satisfied, the move is valid
			return 1;
		case NONE:
			return -1;
	}
	return -1;
}

int validateKnightMove(struct Validation obj) {
	if (
		(abs(obj.toFile - obj.fromFile) == 2 && abs(obj.toRank - obj.fromRank) == 1) ||
		(abs(obj.toRank - obj.fromRank) == 2 && abs(obj.toFile - obj.fromFile) == 1)
	) return 1;
	else return 0;
}

int validateBishopMove(struct Validation obj) {
	/* if (
		(obj.toFile == obj.fromFile + (obj.toRank - obj.fromRank)) ||
		(obj.toFile == obj.fromFile - (obj.toRank - obj.fromRank))
	) return 1;
	else return 0; */
	if (obj.toFile - obj.fromFile == obj.toRank - obj.fromRank && obj.toFile > obj.fromFile) {
		for (int i=1; i < obj.toFile - obj.fromFile; i++) {
			if (obj.board->board[obj.fromFile + i][obj.fromRank + i].type != EMPTY) {
				return 0;
			}
		}
		return 1;
	} else if (obj.toFile - obj.fromFile == obj.fromRank - obj.toRank && obj.toFile > obj.fromFile) {
		for (int i=1; i < obj.toFile - obj.fromFile; i++) {
			if (obj.board->board[obj.fromFile + i][obj.fromRank - i].type != EMPTY) {
				return 0;
			}
		}
		return 1;
	} else if (obj.fromFile - obj.toFile == obj.fromRank - obj.toRank) {
		for (int i=1; i < obj.fromFile - obj.toFile; i++) {
			if (obj.board->board[obj.fromFile - i][obj.fromRank - i].type != EMPTY) {
				return 0;
			}
		}
		return 1;
	} else if (obj.fromFile - obj.toFile == obj.toRank - obj.fromRank) {
		for (int i=1; i < obj.fromFile - obj.toFile; i++) {
			if (obj.board->board[obj.fromFile - i][obj.fromRank + i].type != EMPTY) return 0;
		}
		return 1;
	} else return 0;
}

int validateRookMove(struct Validation obj) {
	/* if (obj.toFile == obj.fromFile || obj.toRank == obj.fromRank) return 1;
	else return 0; */
	if (obj.toFile == obj.fromFile) {
		for (int i=1; i < abs(obj.toRank - obj.fromRank); i++) {
			if (obj.toRank > obj.fromRank) {
				if (obj.board->board[obj.fromFile][obj.fromRank + i].type != EMPTY) return 0;
			} else {
				if (obj.board->board[obj.fromFile][obj.fromRank - i].type != EMPTY) return 0;
			}
		}
		return 1;
	}else if (obj.toRank == obj.fromRank) {
		for (int i=1; i < abs(obj.toFile - obj.fromFile); i++) {
			if (obj.toFile > obj.fromFile) {
				if (obj.board->board[obj.fromFile + i][obj.fromRank].type != EMPTY) return 0;
			} else {
				if (obj.board->board[obj.fromFile - i][obj.fromRank].type != EMPTY) return 0;
			}
		}
		return 1;
	} else return 0;
}

int validateKingMove(struct Validation obj) {
	if (
		(abs(obj.toFile - obj.fromFile) <= 1) &&
		(abs(obj.toRank - obj.fromRank) <= 1)
	) return 1;
	else return 0;
}

int validateQueenMove(struct Validation obj) {
	if (
		(validateBishopMove(obj) == 1) ||
		(validateRookMove(obj) == 1)
	) return 1;
	else return 0;
}

enum PieceType handlePromotion() {
	char promoteTo;
	printf("choose a piece obj.to promote obj.to (N/B/R/Q): ");
	scanf(" %c", &promoteTo);

	//flushing the input buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	switch (toupper(promoteTo)) {
		case 'N':
			return KNIGHT;
		case 'B':
			return BISHOP;
		case 'R':
			return ROOK;
		case 'Q':
			return QUEEN;
		default:
			return EMPTY;
	}
}

struct Validation createValidationObject(
	struct ChessBoard* board,
	int fromFile,
	int fromRank,
	int toFile,
	int toRank
) {
	struct Validation obj;
	obj.board = board;
	obj.fromFile = fromFile;
	obj.fromRank = fromRank;
	obj.toFile = toFile;
	obj.toRank = toRank;
	return obj;
}
