#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "helpers.h"

class ChessPiece;


class ChessBoard {

	public:
		/* constructor */
		ChessBoard();

		/* destructor */
		~ChessBoard();
		
		/* A function to load a board state, and set the pieces up from a FEN string 
		 * @param std::string: A FEN string
		 * */
		void loadState(const std::string); 

		/* A function to print the chessboard to the screen */
		void displayBoard() const;

		/* A function to get a chess piece from the chess board
		 * @param int: An integer to represent the row of the piece that we are after
		 * @param int: An integer to represent the column of the piece that we are after
		 * 
		 * @return A ChessPiece pointer to a given chess piece
		 * */
		ChessPiece* getPiece(const int row, const int col) const;

		/* A function to get the location of the white king on out board
		 * 
		 * @return white king's position as a string
		 * */
		std::string getWhiteKingPos() const;

		/* A function to get the location of the black king on out board
		 * 
		 * @return black king's position as a string
		 * */
		std::string getBlackKingPos() const;

		/* A function that returns true if a given row and column on our board represents a piece of the given colour
		 * @param int: the row number
		 * @param int: the col number
		 * 
		 * @return true if the piece is one of our own, false otherwise
		 * */
		bool isOwnPiece(int, int, Colour) const;
		
		/* A function that returns true if a given row and column on our board represents a piece of the opposite colour tot he one given
		 * @param int: the row number
		 * @param int: the col number
		 * 
		 * @return true if the piece is ane enemy one, false otherwise
		 * */
		bool isEnemyPiece(int, int, Colour) const;

		/* A function to submit a move from one position to another. 
		 * It checks the move submitted is of the right format, and then looks to make the move.
		 * If the move is allowed, the game state is checked i.e. for check, checkmate and stalemate.
		 * When a move is made, whoever's turn is updated
		 *
		 * It makes use of tryMove, tryCastleMove, isCheck, isCheckmate and isStalemate
		 *
		 * @param std::string: a string of length 2 to represent the start position
		 * @param std::string: a string of length 2 to represent the end position
		 * */
		void submitMove(const std::string, const std::string);

	private:
		/* A 'Colour' attribute from the "helpers.h" file to keep track of whose turn it is */
		Colour turn;
		
		/* The pieces on the board, represented as chess piece pointers to the heap */
		ChessPiece* board[8][8]; 
		
		/* Strings to keep track of where each colour's king is on the board */
		std::string white_king_pos;
		std::string black_king_pos;
		
		/* Booleans to keep track of whether a given castle move is feasible */
		bool white_castle_k;
		bool white_castle_q;
		bool black_castle_k;
		bool black_castle_q;

		/* A function to safely delete all heap pointers on our board and assign them to NULL */
		void destroyBoard();

		/* A function to update the location of a colour's king 
		 * By default, if the king is moved, castling is no longer feasible 
		 * If the location specified is not a king, no update is made
		 * @param std::string: the start position of the move that is being made
		 * @param std::string: the end position of the move that is being made
		 * */
		void updateKingPosition(const std::string, const std::string);

		/* A function to move the pieces around on board. It moves a piece from the start position to the end position
		 * (denoted by indices)
		 * @param int: the start row
		 * @param int: the start col 
		 * @param int: the end row
		 * @param int: the end col 
		 * */
		void makeBoardMove(const int, const int, const int, const int);
		
		/* A function to try and make a move from a given start position to another
		 * @param std::string: a string of length 2 to represent the start position
		 * @param std::string: a string of length 2 to represent the end position
		 * 
		 * @return True if the move can be made; false otherwise
		 * */
		bool tryMove(const std::string, const std::string);
		
		/* A function to check if a given move is a castle move or not. This simply checks if the king is moving 2 horizontally or not
		 * @param std::string: a string of length 2 to represent the start position
		 * @param std::string: a string of length 2 to represent the end position
		 * 
		 * @return True if it as attempted castle i.e. an attempt to move the king 2 squares horizontally.
		 * */
		bool isCastleMove(const std::string, const std::string);

		/* A function to try and make a castle move. This includes relevant checks to ensure a castle move is valid
		 * @param std::string: a string of length 2 to represent the start position
		 * @param std::string: a string of length 2 to represent the end position
		 * 
		 * @return True if the move can be made; false otherwise
		 * */
		bool tryCastleMove(const std::string, const std::string);

		/* A function to check if a particular colour is in check
		 * @param Colour: a colour (BLACK or WHITE) based on the enum defined in "helpers.h"
		 *
		 * @return: True if the given colour is in check; false otherwise
		 * */
		bool isCheck(Colour);
		
		/* A function to check if a given colour is in checkmate 
		 * @param Colour: a colour (BLACK or WHITE) based on the enum defined in "helpers.h"
		 * 
		 * @return: True if the given colour is in checkmate
		 * */
		bool isCheckmate(Colour);
		
		/* A function to check if any piece from a given colour can move to the position specified by the string 
		 * @param std::string: a target position to try and move a clour's pieces to
		 * @param Colour: the colour of the pieces that we are trying to move to the target location
		 *
		 * @return true if one of the colour's pieces can move to the location, false otherwise
		 * */
		bool moveOwnPiece(const std::string, Colour);

		/* A function to check if a given colour is in stalemate 
		 * @param Colour: a colour (BLACK or WHITE) based on the enum defined in "helpers.h"
		 * 
		 * @return: True if the given colour is in stalemate
		 * */
		bool isStalemate(Colour);

};

#endif

