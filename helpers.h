#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>

/* Helper: gets the row number from a position */
int posToRow(std::string);


/* Helper: gets the col number from a position */
int posToCol(std::string);


/* Helper: converts a rown and column to a string position */
std::string rowColToPos(int, int);


/* Helper: data type defined to represent the colour of the piece */
enum Colour{
	WHITE = 0,
	BLACK = 1
};


/* Helper: operator overloading to output the Colour enum defined above into text e.g. WHITE becomes "White" */
std::ostream& operator << (std::ostream& os, Colour colour);

#endif

