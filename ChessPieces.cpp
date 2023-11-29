#include "ChessPieces.h"
#include "ChessBoard.h"

/* ==============================
 * PARENT CLASS: ChessPiece 
 * ============================== */
//constructor
ChessPiece::ChessPiece(char* _position, Colour _colour) : position(_position), colour(_colour){
}


ChessPiece::~ChessPiece(){
}


Colour ChessPiece::getColour(){
	return colour;
}


std::vector<std::string>& ChessPiece::getPotentialMoves(){
	return potential_moves;
}

void ChessPiece::displayPotentialMoves(){
	for (int i=0; i<static_cast<char>(potential_moves.size()); i++){
		std::cout << potential_moves[i] << "; ";
	}
	std::cout << std::endl;
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
King::King(char* _position, Colour _colour, bool _has_moved) : 
	ChessPiece(_position, _colour), has_moved(_has_moved) {
	//calculatePotentialMoves(_position, chessboard);
}


King::~King(){
}


bool King::hasMoved(){
	return has_moved;
}


void King::calculatePotentialMoves(const ChessBoard& chessboard){
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;
	for (int row_delta = -1; row_delta <= 1; row_delta++){
		for (int col_delta = -1; col_delta <= 1; col_delta++){
			// ignore the case where no move is made
			if (!(row_delta == 0 && col_delta == 0)){
				int new_row = row_position + row_delta;
				int new_col = col_position + col_delta; 

				// if the new postion is valid and not blocked by a piece of the same colour,
				// add it to our vector of potential moves
				if (validBoardPosition(new_row, new_col)){

					if (chessboard.board[new_row][new_col]->getColour()!=colour){
						//std::cout << rowColToPos(new_row, new_col) << std::endl;
						potential_moves.push_back(rowColToPos(new_row, new_col));
					}
				}
			}
		}
	}
	// check if the king has moved. If it hasn't there is the potential for it to castle
	if (!has_moved){

		potential_moves.push_back(rowColToPos(row_position, col_position + 2)); //castle king's side
		potential_moves.push_back(rowColToPos(row_position, col_position - 2)); //castle queen's side
	}
}

bool King::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}
	
	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	if (has_moved){
		if (std::abs(row_delta) > 1 || std::abs(col_delta) > 1){
			return false;
		}
	}
	else{
		// ensure the castling move is correct
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			//check if the piece is blocked
			if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour){
				return false;
			}
			//check for the castle move
			if (std::abs(col_delta)==2){
				if (cb.board[start_row+row_change][start_col+col_change]!=nullptr){
					return false;
				}
				// TODO add recursive logic here for checking if castling is feasible. Will need check
			}
		}
	}

	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
	}
	
	if (colour==WHITE){
		//cb.white_king_position = end_pos;	
	}
	else {
		//cb.black_king_position = end_pos;	
	}
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
Queen::Queen(char* _position, Colour _colour) :
	ChessPiece(_position, _colour) {
	//calculatePotentialMoves(_position, chessboard);

}


Queen::~Queen(){
}


void Queen::calculatePotentialMoves(const ChessBoard& chessboard){
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;

	for (int row_delta = -7; row_delta <= 7; row_delta++){
		for (int col_delta = -7; col_delta <= 7; col_delta++){
			// ignore the case where no move is made
			if (!(row_delta == 0 && col_delta == 0)){
				int new_row = row_position + row_delta;
				int new_col = col_position + col_delta; 
				// if the new postion is valid, add it to our vector of potential moves
				if (validBoardPosition(new_row, new_col)){
					// horizontals, verticals, diagonals
					if (chessboard.board[new_row][new_col]->getColour()!=colour){
					}

					if (new_row == row_position || new_col == col_position || std::abs(row_delta) == std::abs(col_delta)){
						//std::cout << rowColToPos(new_row, new_col) << std::endl;
						potential_moves.push_back(rowColToPos(new_row, new_col));
					}
				}
			}
		}
	}
}

bool Queen::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
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
	// horizontals, verticals, diagonals
	if ((row_delta != 0 && std::abs(col_delta) > 0) || 
			(col_delta != 0 && std::abs(row_delta) > 0)|| 
			 std::abs(row_delta) != std::abs(col_delta)){
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			// check if the piece is blocked
			// first filter on legitimate moves for the piece. 
			// If legitimate, then check for a blockage (horizontals, verticals, diagonals)
			if ((row_change+start_row) == start_row || 
					(col_change+start_col) == start_col || 
					std::abs(row_change) == std::abs(col_change)){
				if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour){
					return false;
				}
			} //no need for an else here, as we would just continue on to the next item in our loop		
		}
	}
	
	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
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
Rook::Rook(char* _position, Colour _colour, bool _has_moved) : 
	ChessPiece(_position, _colour), has_moved(_has_moved) {
	//calculatePotentialMoves(_position, chessboard);
	if (_position[0] == 'H'){
		king_side = true;
	}
	else {
		king_side = false;
	}
}


Rook::~Rook(){
}


bool Rook::hasMoved(){
	return has_moved;
}


bool Rook::isKingSide(){
	return king_side;
}


void Rook::calculatePotentialMoves(const ChessBoard& chessboard){	
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;

	for (int row_delta = -7; row_delta <= 7; row_delta++){
		for (int col_delta = -7; col_delta <= 7; col_delta++){
			// ignore the case where no move is made
			if (!(row_delta == 0 && col_delta == 0)){
				int new_row = row_position + row_delta;
				int new_col = col_position + col_delta; 
				// if the new postion is valid, add it to our vector of potential moves
				if (validBoardPosition(new_row, new_col)){
					// only up or down moves are valid
					if (new_row == row_position || new_col == col_position){
						//std::cout << rowColToPos(new_row, new_col) << std::endl;
						potential_moves.push_back(rowColToPos(new_row, new_col));
					}
				}
			}
		}
	}
}

bool Rook::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			// check if the piece is blocked
			// first filter on legitimate moves for the piece. 
			// If legitimate, then check for a blockage (horizontals, verticals)
			if ((row_change+start_row) == start_row || 
					(col_change+start_col) == start_col){
				if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour){
					return false;
				}
			} //no need for an else here, as we would just continue on to the next item in our loop		
		}
	}
	
	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
	}
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
Bishop::Bishop(char* _position, Colour _colour) :
	ChessPiece(_position, _colour) {
	//calculatePotentialMoves(_position, chessboard);

}


Bishop::~Bishop(){
}


void Bishop::calculatePotentialMoves(const ChessBoard& chessboard){
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;

	for (int row_delta = -7; row_delta <= 7; row_delta++){
		for (int col_delta = -7; col_delta <= 7; col_delta++){
			// ignore the case where no move is made
			if (!(row_delta == 0 && col_delta == 0)){
				int new_row = row_position + row_delta;
				int new_col = col_position + col_delta; 
				// if the new postion is valid, add it to our vector of potential moves
				if (validBoardPosition(new_row, new_col)){
					// only diagonal moves are valid
					if (std::abs(row_delta) == std::abs(col_delta)){
						//std::cout << rowColToPos(new_row, new_col) << std::endl;
						potential_moves.push_back(rowColToPos(new_row, new_col));
					}
				}
			}	
		}
	}
}

bool Bishop::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			// check if the piece is blocked
			// first filter on legitimate moves for the piece. 
			// If legitimate, then check for a blockage (only diagonals)
			if (std::abs(row_change) == std::abs(col_change)){
				if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour){
					return false;
				}
			} //no need for an else here, as we would just continue on to the next item in our loop		
		}
	}
	
	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
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
Knight::Knight(char* _position, Colour _colour) :
	ChessPiece(_position, _colour) {
	//calculatePotentialMoves(_position, chessboard);
}


Knight::~Knight(){
}


void Knight::calculatePotentialMoves(const ChessBoard& chessboard){
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;

	for (int row_delta = -2; row_delta <= 2; row_delta++){
		for (int col_delta = -2; col_delta <= 2; col_delta++){
			// ignore the case where no move is made
			if (!(row_delta == 0 && col_delta == 0)){
				int new_row = row_position + row_delta;
				int new_col = col_position + col_delta; 
				// if the new postion is valid, add it to our vector of potential moves
				if (validBoardPosition(new_row, new_col)){
					// only diagonal mvoes are valid
					if ((std::abs(row_delta) == 2 && std::abs(col_delta) == 1) || 
							(std::abs(row_delta) == 1 && std::abs(col_delta) == 2) ){
						if (chessboard.board[new_row][new_col]->getColour()!=colour){
							//std::cout << rowColToPos(new_row, new_col) << std::endl;
							potential_moves.push_back(rowColToPos(new_row, new_col));
						}					
					}
				}
			}	
		}
	}
}

bool Knight::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
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
	// special 2x1 knight move
	if ((std::abs(row_delta) == 2 && std::abs(col_delta) != 1) || 
			(std::abs(col_delta) == 2 && std::abs(row_delta) != 1)){
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			// check if the piece is blocked
			// first filter on legitimate moves for the piece. 
			// If legitimate, then check for a blockage (special knight move)
			if ((std::abs(row_change) == 2 && std::abs(col_change) == 1) || 
				(std::abs(col_change) == 2 && std::abs(row_change) == 1)){
				if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour){
					return false;
				}
			} //no need for an else here, as we would just continue on to the next item in our loop		
		}
	}
	
	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
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
Pawn::Pawn(char* _position, Colour _colour, bool _has_moved) : 
	ChessPiece(_position, _colour), has_moved(_has_moved) {
	//calculatePotentialMoves(_position, chessboard);
}


Pawn::~Pawn(){
}


void Pawn::calculatePotentialMoves(const ChessBoard& chessboard){
	int row_position = posToRow(position);
	int col_position = posToCol(position);

	//std::cout << row_position << std::endl;
	//std::cout << col_position << std::endl;
	if (colour == WHITE){
		// White moves 'up the board' i.e. from higher row index to lower. Go to -1 to prevent a horizontal move featuring
		int row_delta = -1;
		for (int col_delta = -1; col_delta <= 1; col_delta++){
			int new_row = row_position + row_delta;
			int new_col = col_position + col_delta; 
			// if the new postion is valid, consider add it to our vector of potential moves
			if (validBoardPosition(new_row, new_col)){
				potential_moves.push_back(rowColToPos(new_row, new_col));
			}
		}
		// check if the pawn has moved yet. If it has not, it can only move one square at a time
		if (!has_moved){
			potential_moves.push_back(rowColToPos(row_position - 2, col_position));
		}

	}
	else {
		// Black moves 'down the board' i.e. from lower row index to higher. Go from 1 to prevent a horizontal move featuring
		int row_delta = 1;
		for (int col_delta = -1; col_delta <= 1; col_delta++){
			int new_row = row_position + row_delta;
			int new_col = col_position + col_delta; 
			// if the new postion is valid, consider adding it to our vector of potential moves
			if (validBoardPosition(new_row, new_col)){
				// check if the pawn has moved yet. If it has, it can only move one square at a time
				potential_moves.push_back(rowColToPos(new_row, new_col));	
			}
		}
		// check if the pawn has moved yet. If it has not, it can only move one square at a time
		if (!has_moved){
			potential_moves.push_back(rowColToPos(row_position + 2, col_position));
		}
	}
}

bool Pawn::isLegalMove(char* end_pos, const ChessBoard& cb){
	int start_row = posToRow(position);
	int start_col = posToCol(position);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// check target is on our board
	if (end_row > 7 || end_row < 0 || end_col > 7 || end_col < 0){
		return false;
	}

	// check magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;
	
	if (colour == WHITE){
		// check for validity of the move
		// if the piece has already moved, it can only move one row at a time
		// white moves up the board i.e. to a lower row index
		if (has_moved){
			if (!(row_delta == -1 && std::abs(col_delta) == 1)){
				return false;
			}
		}
		else {
			if (!((row_delta == 2 && col_delta == 0) || 
					(row_delta == 1 && std::abs(col_delta)))){
				return false;
			}
		}
	}
	else {
		// black moves down the board i.e. to a higher row index
		if (has_moved){
			if (!(row_delta == 1 && std::abs(col_delta) == 1)){
				return false;
			}
		}
		else {
			if (!((row_delta == 2 && col_delta == 0) || 
					(row_delta == 1 && std::abs(col_delta)))){
				return false;
			}
		}
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
			if (std::signbit(row_delta)){
				row_change*=-1;
			}
			if (std::signbit(col_delta)){
				col_change*=-1;
			}
			// check if the piece is blocked
			// first filter on legitimate moves for the piece. 
			// If legitimate, then check for a blockage (a move straight up/down the board)
			if ((col_change+start_col) == start_col){
				if (cb.board[start_row+row_change][start_col+col_change]!=nullptr){
					return false;
				}
			}
			// if the pawn takes. Can only take if it is an enemy colour
			if (std::abs(col_change)==std::abs(row_change)){
				if (cb.board[start_row+row_change][start_col+col_change]->getColour()==colour ||
						cb.board[start_row+row_change][start_col+col_change]==nullptr){
					return false;
				}	
			}		
		}
	}
	
	// check if making this move puts ourselves in check
	if (cb.isCheck(colour)){
		return false;
	}
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


