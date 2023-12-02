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


enum Colour{
	WHITE = 0,
	BLACK = 1
};

std::ostream& operator << (std::ostream& os, Colour colour);

#endif

