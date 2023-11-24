#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "ChessPieces.h"

class ChessBoard {

	public:
		//constructor
		ChessBoard();

		//destructor
		~ChessBoard();
		

		void loadState(const std::string); //check string passed as input is valid
		void submitMove(std::string, std::string);


	private:
		ChessPiece* board[8][8]; 
		Colour turn;
		bool white_castle_k;
		bool white_castle_q;
		bool black_castle_k;
		bool black_castle_q;

		int posToRow(std::string);
		int posToCol(std::string);
		std::string rowColToPos(int, int);

		/* Function to delete all heap pointers on our board and assign them to NULL */
		void destroyBoard();

};

#endif
