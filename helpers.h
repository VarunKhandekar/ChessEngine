#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>

/* Helper: gets the row number from a position */
int posToRow(const std::string);


/* Helper: gets the col number from a position */
int posToCol(const std::string);


/* Helper: converts a rown and column to a string position */
std::string rowColToPos(const int, const int);


/* Helper: data type defined to represent the colour of the piece */
enum Colour{
	WHITE = 0,
	BLACK = 1
};


/* Helper: operator overloading to output the Colour enum defined above into text e.g. WHITE becomes "White" */
std::ostream& operator << (std::ostream& os, Colour colour);


/* Helper: checks if a given string is in a string array, returning the index */
int inArray(const std::string, const std::string*, const int);

#endif

