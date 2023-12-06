#include "ChessPieces.h"
#include "ChessBoard.h"

/* ==============================
 * PARENT CLASS: ChessPiece 
 * ============================== */
/* constructor */
ChessPiece::ChessPiece(Colour _colour) : colour(_colour){
}


/* destructor */
ChessPiece::~ChessPiece(){
}


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


/* ==============================
 * CHILD CLASS: King 
 * ============================== */
/* constructor */
King::King(Colour _colour) : ChessPiece(_colour) {
}


/* destructor */
King::~King(){
}


bool King::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const{
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// get magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	// no move case
	if (row_delta == 0 && col_delta == 0){
		return false;
	}
	// if we are moving too many rows or too many columns
	if (std::abs(row_delta) > 1){
		return false;
	}
	if (std::abs(row_delta) == 1 && std::abs(col_delta) > 1){
		return false;
	}
	// checking for the castle move
	if (std::abs(row_delta) == 0 && std::abs(col_delta) > 2){
		return false;
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
			if (cb.isOwnPiece(start_row+row_change_signed, start_col+col_change_signed, colour)){
					return false;
			}
			//check for the castle move. By this stage, row_delta would be 0 anyway so no need to check for that
			if (std::abs(col_delta)==2){
				if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed) !=nullptr){
					return false;
				}
			}
		}
	}
	return true;
}


/* */
void King::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's King";
	}
	else {
		os << "Black's King";
	}
}


/* */
void King::print_letter(std::ostream& os) const {
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
/* constructor */
Queen::Queen(Colour _colour) :
	ChessPiece(_colour) {
}


/* destructor */
Queen::~Queen(){
}


/* */
bool Queen::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const {
	
	// A queen is just a combo of a rook and a bishop
	Rook* test_rook = new Rook(colour);
	Bishop* test_bishop = new Bishop(colour);
	
	bool legal_move = false;
	if (test_rook->isLegalMove(start_pos, end_pos, cb) || test_bishop->isLegalMove(start_pos, end_pos, cb)){
		legal_move = true;
	}

	delete test_rook;
	delete test_bishop;

	return legal_move;
}


void Queen::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's Queen";
	}
	else {
		os << "Black's Queen";
	}
}


void Queen::print_letter(std::ostream& os) const {
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
/* constructor */
Rook::Rook(Colour _colour) : ChessPiece(_colour) {
}


/* destructor */
Rook::~Rook(){
}


bool Rook::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const{
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
			// check if the piece is blocked (horizontals, verticals)
			if ((row_change+start_row) == start_row || 
					(col_change+start_col) == start_col){
				// case for if we are at our target square
				if (row_change_signed == row_delta && col_change_signed == col_delta){
					if (cb.isOwnPiece(start_row+row_change_signed, start_col+col_change_signed, colour)){
							return false;
					}
				}
				// case for if we are en route to target square. Check if not blocked by something
				else { 
					if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed)!= nullptr){
						return false;
					}
				}	
			}
		}
	}
	
	return true;
}


void Rook::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's Rook";
	}
	else {
		os << "Black's Rook";
	}
}


void Rook::print_letter(std::ostream& os) const {
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
/* constructor */
Bishop::Bishop(Colour _colour) : ChessPiece(_colour) {
}


/* destructor */
Bishop::~Bishop(){
}


bool Bishop::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const{
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
			// check if the piece is blocked (only diagonals)
			if (row_change == col_change){
				// case for if we are at our target square
				if (row_change_signed == row_delta && col_change_signed == col_delta){
					if (cb.isOwnPiece(start_row+row_change_signed, start_col+col_change_signed, colour)){
							return false;
					}
				}
				// case for if we are en route to target square. Check if not blocked by something
				else { 
					if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed) != nullptr){
						return false;
					}
				}
			}
		}
	}

	return true;
}


void Bishop::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's Bishop";
	}
	else {
		os << "Black's Bishop";
	}
}


void Bishop::print_letter(std::ostream& os) const {
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
/* constructor */
Knight::Knight(Colour _colour) : ChessPiece(_colour) {
}


/* destructor */
Knight::~Knight(){
}


bool Knight::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const{
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
			// check if the piece is blocked (special knight logic)
			if ((row_change == 2 && col_change == 1) || 
				(col_change == 2 && row_change == 1)){
				if (cb.isOwnPiece(start_row+row_change_signed, start_col+col_change_signed, colour)){
					return false;
				}
			}
		}
	}
	
	return true;
}


void Knight::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's Knight";
	}
	else {
		os << "Black's Knight";
	}
}


void Knight::print_letter(std::ostream& os) const {
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
/* constructor */
Pawn::Pawn(Colour _colour) : ChessPiece(_colour) {
}


/* destructor */
Pawn::~Pawn(){
}


bool Pawn::isLegalMove(const std::string start_pos, const std::string end_pos, const ChessBoard& cb) const{
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
		if (start_row != 6){
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
		if (start_row != 1){
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
					if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed)!=nullptr){
						return false;
					}
				}
			}
			// By this time, the move should be ok. This condition would then be for taking an enemy piece
			else {
				if (col_change==row_change){
					//We first see if it is a nullptr
					if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed)==nullptr){
						return false;
					}
					// now we check if it's a piece of the same colour		
					else if (cb.getPiece(start_row+row_change_signed, start_col+col_change_signed)->getColour()==colour){
						return false;
					}	
				}		
			}
		}
	}
	
	return true;
}


void Pawn::print(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "White's Pawn";
	}
	else {
		os << "Black's Pawn";
	}
}


void Pawn::print_letter(std::ostream& os) const {
	if (this->colour == WHITE){
		os << "P";
	}
	else {
		os << "p";
	}
}


