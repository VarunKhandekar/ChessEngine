#include "ChessPieces.h"


/* ==============================
 * PARENT CLASS: ChessPiece 
 * ============================== */
//constructor
ChessPiece::ChessPiece(std::string _position, Colour _colour) : position(_position), colour(_colour){
	getPotentialMoves(_position);

}

ChessPiece::~ChessPiece(){
}


void ChessPiece::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: King 
 * ============================== */
//constructor
King::King(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

King::~King(){
}



void King::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: Queen 
 * ============================== */
//constructor
Queen::Queen(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

Queen::~Queen(){
}


void Queen::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: Rook 
 * ============================== */
//constructor
Rook::Rook(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

Rook::~Rook(){
}


void Rook::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: Bishop
 * ============================== */
//constructor
Bishop::Bishop(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

Bishop::~Bishop(){
}


void Bishop::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: Knight 
 * ============================== */
//constructor
Knight::Knight(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

Knight::~Knight(){
}


void Knight::getPotentialMoves(std::string position){
	

}



/* ==============================
 * CHILD CLASS: Pawn
 * ============================== */
//constructor
Pawn::Pawn(std::string _position, Colour _colour) : ChessPiece(_position, _colour) {
	getPotentialMoves(_position);

}

Pawn::~Pawn(){
}


void Pawn::getPotentialMoves(std::string position){
	

}

