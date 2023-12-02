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
		void submitMove(std::string, std::string);

		bool makeMove(std::string, std::string);

		/* A function to check if a particular colour is in check */
		bool isCheck(Colour);
		/* A function to check if a given move leads to a check on the opponent's*/
		bool isCheckmate(Colour);
		/* A function to check if a given move leads to a check on the opponent's*/
		bool isStalemate(Colour);

		//TODO convert to getter and setter
		ChessPiece* board[8][8]; 
		void displayBoard();
		std::string white_king_pos;
		std::string black_king_pos;

		//int white_king_row;
		//int white_king_col;
		//int black_king_row;
		//int black_king_col;
		bool white_castle_k;
		bool white_castle_q;
		bool black_castle_k;
		bool black_castle_q;



	private:
		Colour turn;


		/* Function to delete all heap pointers on our board and assign them to NULL */
		void destroyBoard();


		
		bool blockCheck(std::string, Colour);
};

#endif
