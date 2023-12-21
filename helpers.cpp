#include "helpers.h"

/* Helper: gets the row number from a position */
int posToRow(const std::string pos){
	//convert ASCII to appropriate integer e.g. "8" goes to 0, "1" goes to 7, based on rank order of chessboard
	return 56 - pos[1];
}


/* Helper: gets the col number from a position */
int posToCol(const std::string pos){
	// convert ASCII letter to appropriate integer
	return pos[0] - 65;
}


/* Helper: converts a rown and column to a string position */
std::string rowColToPos(const int row, const int col){
	std::string position = "";
	
	position += static_cast<char>(65 + col); // add file
	position += static_cast<char>(56 - row); // add rank
	
	return position;
}


/* Helper: operator overloading to output the Colour enum defined above into text e.g. WHITE becomes "White" */
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


/* Helper: checks if a given string is in a string array, returning the index */
int inArray(const std::string pos, const std::string* string_array, const int array_length) {
	for (int i=0; i<array_length; i++) {
		if (pos == string_array[i]){
			return i;
		}
	}
	return -1;
}
