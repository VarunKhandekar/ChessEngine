#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>

/* Helper: gets the row number from a position */
int posToRow(char*);


/* Helper: gets the col number from a position */
int posToCol(char*);


/* Helper: converts a rown and column to a string position */
//char* rowColToPos(int, int);


enum Colour{
	WHITE = 0,
	BLACK = 1
};

std::ostream& operator << (std::ostream& os, Colour colour);

#endif

