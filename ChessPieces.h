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
		char* position;
		Colour colour;
		std::vector<std::string> potential_moves;
		
		// TODO make this pure virtual
		//virtual bool isLegalMove(std::string, std::string, const ChessBoard&) = 0;

		//function to move piece.
		//position changes, potential moves update

	public:
		//std::string position;
		// constructor
		ChessPiece(char*, Colour);

		//destructor
		virtual ~ChessPiece();

		friend std::ostream& operator << (std::ostream&, ChessPiece*);

		friend std::ostream& operator << (std::ostream&, ChessPiece&);

	
		/* A pure virtual function to provide the skeleton for printing the piece colour and piece type */
		virtual void print(std::ostream&) = 0;
		virtual void calculatePotentialMoves(const ChessBoard&) = 0;
		virtual bool isLegalMove(char*, const ChessBoard&) = 0;

		/* A pure virtual function to provide the skeleton for printing the appropriate piece letter (FEN notation) */
		virtual void print_letter(std::ostream&) = 0;
		
		bool validBoardPosition(int, int);

		Colour getColour();

		std::vector<std::string>& getPotentialMoves();

		void displayPotentialMoves();

};


class King : public ChessPiece {

	public:
		King(char*, Colour, bool);
		//TODO add overrides to these for all child classes
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);



		~King() override;
		//bool isLegalMove(std::string, std::string, const ChessBoard&) override;
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

		bool hasMoved();
	
	private:
		bool has_moved;
}; 


class Queen : public ChessPiece {

	public:
		Queen(char*, Colour);
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);
		~Queen() override;

		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;
	

}; 


class Rook : public ChessPiece {

	public:
		Rook(char*, Colour, bool);
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);
		~Rook() override;
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

		bool hasMoved();

		bool isKingSide();

	private:
		bool has_moved;
		bool king_side;
}; 


class Bishop : public ChessPiece {

	public:
		Bishop(char*, Colour);
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);
		~Bishop() override;
		
		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;

};


class Knight : public ChessPiece {

	public:
		Knight(char*, Colour);
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);
		~Knight() override;

		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;
	

};


class Pawn : public ChessPiece {

	public:
		Pawn(char*, Colour, bool);
		void calculatePotentialMoves(const ChessBoard&) override;
		bool isLegalMove(char*, const ChessBoard&);
		~Pawn() override;

		void print(std::ostream&) override;
		void print_letter(std::ostream&) override;
		
	private:
		bool has_moved;
		

};

#endif
