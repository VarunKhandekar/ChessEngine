#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "helpers.h"

std::ostream& operator << (std::ostream&, Colour);

class ChessBoard;


class ChessPiece {
	protected:
		Colour colour;

	public:
		// constructor
		ChessPiece(Colour);

		//destructor
		virtual ~ChessPiece();

		friend std::ostream& operator << (std::ostream&, ChessPiece*);

		friend std::ostream& operator << (std::ostream&, ChessPiece&);

	
		/* A pure virtual function to provide the skeleton for printing the piece colour and piece type */
		virtual void print(std::ostream&) = 0;
		virtual bool isLegalMove(std::string, std::string, ChessBoard&) = 0;

		/* A pure virtual function to provide the skeleton for printing the appropriate piece letter (FEN notation) */
		virtual void print_letter(std::ostream&) = 0;
		
		Colour getColour();

};


class King : public ChessPiece {

	public:
		King(Colour);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~King() override;
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

}; 


class Queen : public ChessPiece {

	public:
		Queen(Colour);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~Queen() override;
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

}; 


class Rook : public ChessPiece {

	public:
		Rook(Colour, bool);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~Rook() override;
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

		bool isKingSide();

	private:
		bool king_side;
}; 


class Bishop : public ChessPiece {

	public:
		Bishop(Colour);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~Bishop() override;
		
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

};


class Knight : public ChessPiece {

	public:
		Knight(Colour);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~Knight() override;

		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

};


class Pawn : public ChessPiece {

	public:
		Pawn(Colour);
		bool isLegalMove(std::string, std::string, ChessBoard&);
		~Pawn() override;

		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

};

#endif
