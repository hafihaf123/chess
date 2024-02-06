/*
 * =====================================================================================
 *
 *       Filename:  Validation.h
 *
 *    Description:  header file for validation logic
 *
 *        Version:  1.0
 *        Created:  02/05/24 11:46:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (Michal Buchman), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef VALIDATION_H
#define VALIDATION_H

#include "chess.h"

struct Validation {
	struct ChessBoard* board;
	int fromFile;
	int fromRank;
	int toFile;
	int toRank;
};

int validateMove(struct Validation obj);
	
int validatePawnMove(struct Validation obj);

int validateKnightMove(struct Validation obj);

int validateBishopMove(struct Validation obj);

int validateRookMove(struct Validation obj);

int validateKingMove(struct Validation obj);

int validateQueenMove(struct Validation obj);

enum PieceType handlePromotion();

struct Validation createValidationObject(
	struct ChessBoard* board,
	int fromFile,
	int fromRank,
	int toFile,
	int toRank
);

#endif
