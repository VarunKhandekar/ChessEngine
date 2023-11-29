#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "helpers.h"

class ChessPiece;


class ChessBoard {

	public:
		//constructor
		ChessBoard();

		//destructor
		~ChessBoard();
		

		void loadState(const std::string); //check string passed as input is valid
		void submitMove(char*, char*);
		bool validMove(char*, char*);

		/* A function to check if a particular colour is in check */
		bool isCheck(Colour) const;
		/* A function to check if a given move leads to a check on the opponent's*/
		bool isCheckmate(Colour);
		/* A function to check if a given move leads to a check on the opponent's*/
		bool isStalemate(Colour);

		//TODO convert to getter and setter
		ChessPiece* board[8][8]; 
		void displayBoard();
		char* white_king_position;
		char* black_king_position;



	private:
		Colour turn;

		bool white_castle_k;
		bool white_castle_q;
		bool black_castle_k;
		bool black_castle_q;

		/* Function to delete all heap pointers on our board and assign them to NULL */
		void destroyBoard();


		

};

#endif
