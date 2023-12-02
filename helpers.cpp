#include "helpers.h"

/* Helper: gets the row number from a position */
int posToRow(std::string pos){
	//convert ASCII to appropriate integer
	return 56 - pos[1];
}


/* Helper: gets the col number from a position */
int posToCol(std::string pos){
	// convert ASCII to appropriate integer e.g. "8" goes to 0, "1" goes to 7, based on rank order of chessboard
	return pos[0] - 65;
}


/* Helper: converts a rown and column to a string position */
std::string rowColToPos(int row, int col){
	std::string position = "";
	
	position += static_cast<char>(65 + col); // add file
	position += static_cast<char>(56 - row); // add rank
	
	return position;
}


std::ostream& operator << (std::ostream& os, Colour colour){
	switch(colour){
		case WHITE: os << "White";
			break;
		case BLACK: os << "Black";
			break;
		default:
			break;
	}
	return os;
}
