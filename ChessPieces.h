#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <iostream>
#include <string>
#include <cmath>
#include "helpers.h"

std::ostream& operator << (std::ostream&, Colour);

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
		 * @return prints custom output to screen e.g. "Black's Queen"
		 * */
		friend std::ostream& operator << (std::ostream&, ChessPiece*);

		/* Function overloading for the << operator. Makes use of the 'print_letter' function below
		 * @param std::ostream&: a reference to an ostream object
		 * @param ChessPiece&: a reference to a ChessPiece on our ChessBoard
		 * @return prints a single letter to screen representing the FEN notation for a piece e.g. "K"
		 * */
		friend std::ostream& operator << (std::ostream&, ChessPiece&);

		
		/* A pure virtual function to provide the skeleton for checking if a move is 'geometrically' legal for a given piece */
		virtual bool isLegalMove(const std::string, const std::string, const ChessBoard&) const = 0;
		
		/* A function to get the colour of a chess piece 
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
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;
		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

}; 


class Queen : public ChessPiece {

	public:
		/* constructor */
		Queen(Colour);
		
		/* destructor */
		~Queen() override;
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;
		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

}; 


class Rook : public ChessPiece {

	public:
		/* constructor */
		Rook(Colour);
		
		/* destructor */
		~Rook() override;
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;
		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

}; 


class Bishop : public ChessPiece {

	public:
		/* constructor */
		Bishop(Colour);
		
		/* destructor */
		~Bishop() override;
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;
		
		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

};


class Knight : public ChessPiece {

	public:
		/* constructor */
		Knight(Colour);
		
		/* destructor */
		~Knight() override;
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;

		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

};


class Pawn : public ChessPiece {

	public:
		/* constructor */
		Pawn(Colour);
		
		/* destructor */
		~Pawn() override;
		bool isLegalMove(const std::string, const std::string, const ChessBoard&) const;

		void print(std::ostream&) const override;
		void print_letter(std::ostream&) const override;

};

#endif
