#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <iostream>
#include <string>
#include <vector>


enum Colour{
	WHITE = 0,
	BLACK = 1,
};

class ChessPiece {
	protected:
		std::string position;
		Colour colour;
		std::vector<std::string> potential_moves;
		

		// TODO make this pure virtual
		virtual void getPotentialMoves(std::string);
		//function to move piece.
		//position changes, potential moves update

	public:
		// constructor
		ChessPiece(std::string, Colour);
		//destructor
		virtual ~ChessPiece();

};


class King : public ChessPiece {

	public:
		King(std::string, Colour);
		//TODO add overrides to these for all child classes
		void getPotentialMoves(std::string);
		~King() override;
}; 


class Queen : public ChessPiece {

	public:
		Queen(std::string, Colour);
		void getPotentialMoves(std::string);
		~Queen() override;
}; 


class Rook : public ChessPiece {

	public:
		Rook(std::string, Colour);
		void getPotentialMoves(std::string);
		~Rook() override;
}; 


class Bishop : public ChessPiece {

	public:
		Bishop(std::string, Colour);
		void getPotentialMoves(std::string);
		~Bishop() override;

};


class Knight : public ChessPiece {

	public:
		Knight(std::string, Colour);
		void getPotentialMoves(std::string);
		~Knight() override;

};


class Pawn : public ChessPiece {

	public:
		Pawn(std::string, Colour);
		void getPotentialMoves(std::string);
		~Pawn() override;

	//private:
	//	bool has_moved;

}; 


#endif
