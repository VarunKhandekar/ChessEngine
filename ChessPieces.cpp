#include "ChessPieces.h"
#include "ChessBoard.h"

/* ==============================
 * PARENT CLASS: ChessPiece 
 * ============================== */
//constructor
ChessPiece::ChessPiece(Colour _colour) : colour(_colour){
}


ChessPiece::~ChessPiece(){
}

//ChessPiece* ChessPiece::copy(){
//}

Colour ChessPiece::getColour(){
	return colour;
}


std::ostream& operator << (std::ostream& os, ChessPiece* piece){
	piece->print(os);
	return os;
}


std::ostream& operator << (std::ostream& os, ChessPiece& piece){
	piece.print_letter(os);
	return os;
}


/* A function to check if a position, given by a row and column, is a valid position on a chess board */
bool ChessPiece::validBoardPosition(int row, int col){
	if (row < 0 || row > 7 || col < 0 || col > 7){
		return false;
	}
	else {
		return true;
	}
}


/* ==============================
 * CHILD CLASS: King 
 * ============================== */
//constructor
King::King(Colour _colour) : ChessPiece(_colour) {
}


King::~King(){
}


ChessPiece* King::copy(){
	return new King(*this);
}


bool King::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// if you can't castle
	if (!cb.white_castle_k || !cb.white_castle_q){
		if (std::abs(row_delta) > 1 || std::abs(col_delta) > 1){
			return false;
		}
	}
	// if you can castle
	else{
		// ensure the possible castling move is correct
		if (std::abs(col_delta >= 2) && row_delta != 0){
			return false;
		}
		else if (std::abs(row_delta) > 1 || std::abs(col_delta) > 1){
			return false;
		}
	}

	// check for blockages. By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where no move is made
			if (row_change == 0 && col_change == 0){
				continue;
			}
			//check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			//check if the piece is blocked
			if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
				if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
					return false;
				}			
			}
			//check for the castle move. By this stage, row_delta would be 0 anyway so no need to check for that
			if (std::abs(col_delta)==2){
				if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!=nullptr){
					return false;
				}
				// TODO add recursive logic here for checking if castling is feasible. Will need check
			}
		}
	}


	// NOTE: if a king move is feasible, we are good to update the king_position
	// so when we subsequently make the move on the board itself, no further tweaks are needed
	return true;
}


void King::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's King";
	}
	else {
		os << "Black's King";
	}
}


void King::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "K";
	}
	else {
		os << "k";
	}
}


/* ==============================
 * CHILD CLASS: Queen 
 * ============================== */
//constructor
Queen::Queen(Colour _colour) :
	ChessPiece(_colour) {
}


Queen::~Queen(){
}


ChessPiece* Queen::copy(){
	return new Queen(*this);
}


bool Queen::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	// check for validity of the move in terms of file and rank
	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// horizontals, verticals, diagonals
	if (!((row_delta == 0 && std::abs(col_delta) > 0) || 
			(col_delta == 0 && std::abs(row_delta) > 0)|| 
			 std::abs(row_delta) == std::abs(col_delta))){
		return false;
	}

	// check for blockages. 
	// By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where no move is made
			if (row_change == 0 && col_change == 0){
				continue;
			}
			// check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			// check if the piece is blocked 
			// If legitimate, then check for a blockage 
			// Extra queen logic -> see if the desired move is diagonal or not
			if (std::abs(row_delta)==std::abs(col_delta)){
				if (row_change == col_change){
					// case for if we are at our target square
					if (row_change_signed == row_delta && col_change_signed == col_delta){
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
							if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
								return false;
							}			
						}
					}
					// case for if we are en route to target square. Check if not blocked by something
					else { 
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
							return false;
						}
					}
				}
			}
			// we get to here if the hypothesised move is not illegal and is not a diagonal move
			// in such a case, either rows, or cols, will be 0. So a simple else should suffice
			else {
				if ((row_change+start_row) == start_row || 
						(col_change+start_col) == start_col){
					// case for if we are at our target square
					if (row_change_signed == row_delta && col_change_signed == col_delta){
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
							if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
								return false;
							}
						}
					}
					// case for if we are en route to target square. Check if not blocked by something
					else { 
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
							return false;
						}
					}	
				}
			}
		}
	}
	return true;
}


void Queen::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's Queen";
	}
	else {
		os << "Black's Queen";
	}
}


void Queen::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "Q";
	}
	else {
		os << "q";
	}
}


/* ==============================
 * CHILD CLASS: Rook 
 * ============================== */
//constructor
Rook::Rook(Colour _colour, bool _king_side) : 
	ChessPiece(_colour), king_side(_king_side) {
}


Rook::~Rook(){
}


ChessPiece* Rook::copy(){
	return new Rook(*this);
}


bool Rook::isKingSide(){
	return king_side;
}


bool Rook::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	// check for validity of the move in terms of file and rank
	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// horizontals, verticals
	if ((row_delta != 0 && std::abs(col_delta) > 0) || 
			(col_delta != 0 && std::abs(row_delta) > 0)){
		return false;
	}

	// check for blockages. 
	// By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where no move is made
			if (row_change == 0 && col_change == 0){
				continue;
			}
			// check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			// check if the piece is blocked 
			// If legitimate, then check for a blockage (horizontals, verticals)
			if ((row_change+start_row) == start_row || 
					(col_change+start_col) == start_col){
				// case for if we are at our target square
				if (row_change_signed == row_delta && col_change_signed == col_delta){
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
							return false;
						}
					}
				}
				// case for if we are en route to target square. Check if not blocked by something
				else { 
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
						return false;
					}
				}	
			}
		}
	}
	
	

	//if (colour==WHITE){
	//	king_side ? cb.white_castle_k = false : cb.white_castle_q = false;
	//}
	//else {
	//	king_side ? cb.black_castle_k = false : cb.black_castle_q = false;
	//}

	return true;
}


void Rook::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's Rook";
	}
	else {
		os << "Black's Rook";
	}
}


void Rook::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "R";
	}
	else {
		os << "r";
	}
}


/* ==============================
 * CHILD CLASS: Bishop
 * ============================== */
//constructor
Bishop::Bishop(Colour _colour) : ChessPiece(_colour) {
}


Bishop::~Bishop(){
}


ChessPiece* Bishop::copy(){
	return new Bishop(*this);
}


bool Bishop::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;
	
	// check for validity of the move in terms of file and rank
	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// diagonals only
	if (std::abs(row_delta) != std::abs(col_delta)){
		return false;
	}

	// check for blockages. 
	// By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where no move is made
			if (row_change == 0 && col_change == 0){
				continue;
			}
			// check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			// check if the piece is blocked
			// If legitimate, then check for a blockage (only diagonals)
			if (row_change == col_change){
				// case for if we are at our target square
				if (row_change_signed == row_delta && col_change_signed == col_delta){
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
						if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
							return false;
						}			
					}
				}
				// case for if we are en route to target square. Check if not blocked by something
				else { 
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
						return false;
					}
				}
			}
		}
	}

	return true;
}


void Bishop::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's Bishop";
	}
	else {
		os << "Black's Bishop";
	}
}


void Bishop::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "B";
	}
	else {
		os << "b";
	}
}


/* ==============================
 * CHILD CLASS: Knight 
 * ============================== */
//constructor
Knight::Knight(Colour _colour) : ChessPiece(_colour) {
}


Knight::~Knight(){
}


ChessPiece* Knight::copy(){
	return new Knight(*this);
}


bool Knight::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	// check for validity of the move in terms of file and rank
	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// special 2x1 knight move
	if (!((std::abs(row_delta) == 2 && std::abs(col_delta) == 1) || 
				(std::abs(col_delta) == 2 && std::abs(row_delta) == 1))){
		return false;
	}

	// check for blockages. 
	// By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where no move is made
			if (row_change == 0 && col_change == 0){
				continue;
			}
			// check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			// check if the piece is blocked
			// If legitimate, then check for a blockage (special knight move)
			if ((row_change == 2 && col_change == 1) || 
				(col_change == 2 && row_change == 1)){
				if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!= nullptr){
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
						return false;
					}			
				}
			}
		}
	}
	
	return true;
}


void Knight::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's Knight";
	}
	else {
		os << "Black's Knight";
	}
}


void Knight::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "N";
	}
	else {
		os << "n";
	}
}


/* ==============================
 * CHILD CLASS: Pawn
 * ============================== */
//constructor
Pawn::Pawn(Colour _colour, bool _has_moved) : 
	ChessPiece(_colour), has_moved(_has_moved) {
}


Pawn::~Pawn(){
}


ChessPiece* Pawn::copy(){
	return new Pawn(*this);
}


bool Pawn::isLegalMove(std::string start_pos, std::string end_pos, ChessBoard& cb){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}

	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;
	
	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	
	if (colour == WHITE){
		// check for validity of the move
		// if the piece has already moved, it can only move one row at a time
		// white moves up the board i.e. to a lower row index
		if (has_moved){
			if (!(row_delta == -1 && std::abs(col_delta) <= 1)){
				return false;
			}
		}
		else {
			if (!((row_delta == -2 && col_delta == 0) || 
					(row_delta == -1 && std::abs(col_delta) <= 1))){
				return false;
			}
		}
	}
	else {
		// black moves down the board i.e. to a higher row index
		if (has_moved){
			if (!(row_delta == 1 && std::abs(col_delta) <= 1)){
				return false;
			}
		}
		else {
			if (!((row_delta == 2 && col_delta == 0) || 
					(row_delta == 1 && std::abs(col_delta) <= 1))){
				return false;
			}
		}
	}
	

	// check for blockages. 
	// By this stage, we know the submitted move has the potential to be valid
	for (int row_change = 0; row_change <= std::abs(row_delta); row_change++){
		for (int col_change = 0; col_change <= std::abs(col_delta); col_change++){
			// skip the case where the pawn makes no progress
			if (row_change == 0){
				continue;
			}
			// check if we need to move in the 'negative' direction for either rows or cols
			int row_change_signed = row_change;
			int col_change_signed = col_change;
			if (std::signbit(row_delta)){
				row_change_signed = row_change*-1;
			}
			if (std::signbit(col_delta)){
				col_change_signed = col_change*-1;
			}
			// check if the piece is blocked
			// Consider a move straight up/down the board
			if (std::abs(col_delta)==0){
				if ((start_col+col_change_signed) == start_col){
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]!=nullptr){
						return false;
					}
				}
			}
			// By this time, the move should be ok. This condition would then be for taking
			else {
				if (col_change==row_change){
					//We first see if it is a nullptr
					if (cb.board[start_row+row_change_signed][start_col+col_change_signed]==nullptr){
						return false;
					}
					// now we check if it's a piece of the same colour		
					else if (cb.board[start_row+row_change_signed][start_col+col_change_signed]->getColour()==colour){
						return false;
					}	
				}		
			}
		}
	}
	
	//has_moved = true;
	return true;
}

void Pawn::print(std::ostream& os){
	if (this->colour == WHITE){
		os << "White's Pawn";
	}
	else {
		os << "Black's Pawn";
	}
}


void Pawn::print_letter(std::ostream& os){
	if (this->colour == WHITE){
		os << "P";
	}
	else {
		os << "p";
	}
}


