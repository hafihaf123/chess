/*
 * =====================================================================================
 *
 *       Filename:  chess.h
 *
 *    Description: header for chess.c 
 *
 *        Version:  1.0
 *        Created:  02/01/24 19:18:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (Michal Buchman), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CHESS_H
#define CHESS_H

enum PieceType {
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	EMPTY
};

enum Color {
	WHITE,
	BLACK,
	NONE
};

struct Piece {
	enum PieceType type;
	enum Color color;
};

struct ChessBoard{
	struct Piece board[8][8];
};

void initialiseBoard(struct ChessBoard* board);

void printBoard(const struct ChessBoard* board);

int validateMove(enum PieceType pieceType, int fromRank, int fromFile, int toRank, int toFile);

void makeMove(struct ChessBoard* board, enum PieceType pieceType, int fromRank, char fromFile, int toRank, char toFile);

/* void makeMoveShort(struct ChessBoard* board, enum PieceType pieceType, int toRank, char toFile); */

int gameLoop(struct ChessBoard* board);

enum PieceType handlePromotion();

#endif
