/*
 * =====================================================================================
 *
 *       Filename:  chess.c
 *
 *    Description:  simple chess game program in C
 *
 *        Version:  1.0
 *        Created:  02/01/24 19:46:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (Michal Buchman), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "chess.h"
#include <stdio.h>

void initialiseBoard(struct ChessBoard* board) {
	struct Piece blackPawn = {.type = PAWN, .color = BLACK};

	struct Piece whitePawn = {.type = PAWN, .color = WHITE};

	struct Piece whiteBishop = {.type = BISHOP, .color = WHITE};

	struct Piece blackBishop = {.type = BISHOP, .color = BLACK};

	struct Piece whiteKnight = {.type = KNIGHT, .color = WHITE};

	struct Piece blackKnight = {.type = KNIGHT, .color = BLACK};

	struct Piece whiteRook = {.type = ROOK, .color = WHITE};

	struct Piece blackRook = {.type = ROOK, .color = BLACK};

	struct Piece whiteQueen = {.type = QUEEN, .color = WHITE};

	struct Piece blackQueen = {.type = QUEEN, .color = BLACK};

	struct Piece whiteKing = {.type = KING, .color = WHITE};

	struct Piece blackKing = {.type = KING, .color = BLACK};

	for (int i = 0; i < 8; i++) {
		//white pawns to second rank
		board->board[i][1] = whitePawn;

		//black pawns to seventh rank
		board->board[i][6] = blackPawn;
	}
	//white
	board->board[0][0] = whiteRook;
	board->board[1][0] = whiteKnight;
	board->board[2][0] = whiteBishop;
	board->board[3][0] = whiteQueen;
	board->board[4][0] = whiteKing;
	board->board[5][0] = whiteBishop;
	board->board[6][0] = whiteKnight;
	board->board[7][0] = whiteRook;

	//black
	board->board[0][7] = blackRook;
	board->board[1][7] = blackKnight;
	board->board[2][7] = blackBishop;
	board->board[3][7] = blackQueen;
	board->board[4][7] = blackKing;
	board->board[5][7] = blackBishop;
	board->board[6][7] = blackKnight;
	board->board[7][7] = blackRook;

	//everything else is empty
	for (int i=0; i<8; i++) {
		for (int ii=2; ii<7; ii++) {
			board->board[i][ii].type = EMPTY;
		}
	}
}

void printBoard(const struct ChessBoard* board) {
	for (int i=7; i>=0; i--) {
		printf(" - - - - - - - -\n");
		for (int ii=0; ii<8; ii++) {
			printf("|");
			if (board->board[ii][i].color == BLACK) {
			switch (board->board[ii][i].type) {
				case PAWN:
				printf("♙");
				break;
				case KNIGHT:
				printf("♘");
				break;
				case BISHOP:
				printf("♗");
				break;
				case ROOK:
				printf("♖");
				break;
				case QUEEN:
				printf("♕");
				break;
				case KING:
				printf("♔");
				break;
				case EMPTY:
				printf(" ");
			}
			}
			else if (board->board[ii][i].color == WHITE) {
			switch (board->board[ii][i].type) {
				case PAWN:
				printf("♟");
				break;
				case KNIGHT:
				printf("♞");
				break;
				case BISHOP:
				printf("♝");
				break;
				case ROOK:
				printf("♜");
				break;
				case QUEEN:
				printf("♛");
				break;
				case KING:
				printf("♚");
				break;
				case EMPTY:
				printf(" ");
			}
			}
			else printf(" ");
		}
		printf("|\n");
	}
	printf(" - - - - - - - -\n");
}

void makeMove(struct ChessBoard* board, enum PieceType pieceType, int fromRank, char fromFile, int toRank, char toFile) {
	if ((1 <= fromRank && fromRank <= 8) && (1 <= toRank && toRank <= 8)) {
		fromRank--;
		toRank--;
	} else {
		printf("invalid input\n");
		return;
	}
	int fromFileNum, toFileNum;
	
	if (('a' <= fromFile && fromFile <= 'h') && ('a' <= toFile && toFile <= 'h')) {
		fromFileNum = fromFile - 'a';
		toFileNum = toFile - 'a';
	} else {
		printf("invalid input\n");
		return;
	}

	struct Piece piece = board->board[fromFileNum][fromRank];
	if (piece.type != pieceType) {
		printf("piece type not corresponding\n");
		return;
	}
}

/*
void makeMoveShort(struct ChessBoard* board, PieceType pieceType, int toRank, char toFile);*/

int main() {
	struct ChessBoard board;
	initialiseBoard(&board);
	printBoard(&board);

	return 0;
}