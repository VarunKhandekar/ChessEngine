#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <iostream>
#include <string>
#include <cmath>
#include "helpers.h"


class ChessBoard;


class ChessPiece {
	
	public:
		/* constructor */
		ChessPiece(Colour);

		/* destructor */
		virtual ~ChessPiece();
		
		/* Function overloading for the << operator. Makes use of the 'print' function below
		 * @param std::ostream&: a reference to an ostream object
		 * @param ChessPiece*: a pointer to a ChessPiece on our ChessBoard
		 * 
		 * @return prints custom output to screen e.g. "Black's Queen"
		 * */
		friend std::ostream& operator << (std::ostream&, ChessPiece*);

		/* Function overloading for the << operator. Makes use of the 'print_letter' function below
		 * @param std::ostream&: a reference to an ostream object
		 * @param ChessPiece&: a reference to a ChessPiece on our ChessBoard
		 * 
		 * @return prints a single letter to screen representing the FEN notation for a piece e.g. "K"
		 * */
		friend std::ostream& operator << (std::ostream&, ChessPiece&);

		/* A pure virtual function to provide the skeleton for checking if a move is 'geometrically' legal for a given piece 
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		virtual bool isLegalMove(const std::string, const std::string, const ChessBoard&) const = 0;
		
		/* A function to get the colour of a chess piece 
		 * 
		 * @return a colour from the Colour enum defined in "headers.h"*/
		Colour getColour();
	
	protected:
		Colour colour;
		
		/* A pure virtual function to provide the skeleton for printing the piece colour and piece type */
		virtual void print(std::ostream&) const = 0;

		/* A pure virtual function to provide the skeleton for printing the appropriate piece letter (as per FEN notation) */
		virtual void print_letter(std::ostream&) const = 0;

};


class King : public ChessPiece {

	public:
		/* constructor */
		King(Colour);
		
		/* destructor */
		~King() override;
		
		/* An override for checking if a move is 'geometrically' legal for a king. 
		 * It also allows for a horizontal move of 2 to let castling be legal
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a refrence to a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;
	
	private:
		/* A function to print King and its colour in words e.g. "White's King"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* A function to print King in FEN notation e.g. "K" for white's king
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

}; 


class Queen : public ChessPiece {

	public:
		/* constructor */
		Queen(Colour);
		
		/* destructor */
		~Queen() override;
	
		/* An override for checking if a move is 'geometrically' legal for a queen. 
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;
		
	private:
		/* A function to print Queen and its colour in words e.g. "White's Queen"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* A function to print Queen in FEN notation e.g. "Q" for white's queen
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

}; 


class Rook : public ChessPiece {

	public:
		/* constructor */
		Rook(Colour);
		
		/* destructor */
		~Rook() override;
	
		/* An override for checking if a move is 'geometrically' legal for a king. 
		 * It also allows for a horizontal move of 2 to let castling be legal
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;
		
	private:
		/* A function to print Rook and its colour in words e.g. "White's Rook"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* A function to print Rook in FEN notation e.g. "R" for white's rook
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

}; 


class Bishop : public ChessPiece {

	public:
		/* constructor */
		Bishop(Colour);
		
		/* destructor */
		~Bishop() override;
	
		/* An override for checking if a move is 'geometrically' legal for a king. 
		 * It also allows for a horizontal move of 2 to let castling be legal
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;
		
	private:
		/* A function to print Bishop and its colour in words e.g. "White's Bishop"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* a function to print bishop in fen notation e.g. "b" for white's bishop
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

};


class Knight : public ChessPiece {

	public:
		/* constructor */
		Knight(Colour);
		
		/* destructor */
		~Knight() override;
	
		/* An override for checking if a move is 'geometrically' legal for a king. 
		 * It also allows for a horizontal move of 2 to let castling be legal
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;

	private:
		/* A function to print Knight and its colour in words e.g. "White's Knight"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* A function to print Knight in FEN notation e.g. "N" for white's knight
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

};


class Pawn : public ChessPiece {

	public:
		/* constructor */
		Pawn(Colour);
		
		/* destructor */
		~Pawn() override;
	
		/* An override for checking if a move is 'geometrically' legal for a king. 
		 * It also allows for a horizontal move of 2 to let castling be legal
		 * @param std::string: a string of length 2 to represent the start position 
		 * @param std::string: a string of length 2 to represent the end position 
		 * @param ChessBoard&: a ChessBoard object for the piece to test the 'legality' of the move
		 *
		 * @return true if the move is geometrically legal, false otherwise
		 * */
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const override;

	private:
		/* A function to print Pawn and its colour in words e.g. "White's Pawn"
		 * @param std::ostream&: a reference to an ostream object */
		void print(std::ostream&) const override;
		
		/* A function to print Pawn in FEN notation e.g. "P" for white's pawn
		 * @param std::ostream&: a reference to an ostream object */
		void print_letter(std::ostream&) const override;

};

#endif

