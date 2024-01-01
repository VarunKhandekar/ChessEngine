#include "ChessBoard.h"
#include "ChessPieces.h"

/* constructor */
ChessBoard::ChessBoard(){
	// initalise pawn positions to empty strings
	for (int i=0; i<16; i++){
		pawn_positions[i] = "";
	}

	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			board[row][col] = nullptr;
		}
	}
}


/* destructor */
ChessBoard::~ChessBoard(){
	destroyBoard();
}


/* A function to load a board state, and set the pieces up from a FEN string */
void ChessBoard::loadState(const std::string state){
	//start by destroying the board to ensure no memory leaks if a 
	//board had previously been created with pointers to heap
	destroyBoard();

	// create a vector to hold all the delimited parts of our string
	std::vector<std::string> output;
	std::istringstream iss(state);

	// create a string variable called token to hold each delimited value of our 'state' string
	std::string token;
	while (std::getline(iss, token, ' ')) {
	        output.push_back(token);
	}
	

	// loop through element 0 to set up our board
	int row = 0;
	int col = 0;
	int pawn_counter = 0; // also set up a pawn counter to fill up our pawn positions array
	for (int i=0; i<static_cast<int>(output[0].size()); i++){
		//check if we hit our rank delimiter
		if (output[0][i]=='/'){
			row++;
			col = 0;
			if (row > 8){
				std::cerr << "The FEN string is invalid; there are too many rows!" << std::endl;
				// now destroy board to clean up memory
				destroyBoard();
				return;
			}
			continue;
		}
		
		// now check if we have hit a number 
		else if (output[0][i] >= '1' && output[0][i] <= '8'){
			// if we have, move along as many columns as that number and don't do anything
			col += (output[0][i] - 48); 
		} 

		// otherwise set up the chess pieces
		else {
			switch(output[0][i]){
				// White pieces
				case 'K': board[row][col] = new King(WHITE);
						  white_king_pos = rowColToPos(row, col);
						  break;
				case 'Q': board[row][col] = new Queen(WHITE);
						  break;
				case 'R': board[row][col] = new Rook(WHITE);
						  break;
				case 'B': board[row][col] = new Bishop(WHITE);
						  break;
				case 'N': board[row][col] = new Knight(WHITE);
						  break;
				case 'P': board[row][col] = new Pawn(WHITE);
						  pawn_positions[pawn_counter] = rowColToPos(row, col);
						  pawn_counter++;
						  break;

				// Black pieces
				case 'k': board[row][col] = new King(BLACK);
						  black_king_pos = rowColToPos(row, col);
						  break;
				case 'q': board[row][col] = new Queen(BLACK);
						  break;
				case 'r': board[row][col] = new Rook(BLACK);
						  break;
				case 'b': board[row][col] = new Bishop(BLACK);
						  break;
				case 'n': board[row][col] = new Knight(BLACK);
						  break;
				case 'p': board[row][col] = new Pawn(BLACK);
						  pawn_positions[pawn_counter] = rowColToPos(row, col);
						  pawn_counter++;
						  break;
				
				default: std::cerr << "Invalid letter provided in the FEN string. Please check!" << std::endl;
						 destroyBoard();
						 return;
			}
			if (pawn_counter > 16){
				std::cerr << "The FEN string is invalid; there are too many pawns!" << std::endl;
				// now destroy board to clean up memory
				destroyBoard();
				return;
			}

			col++;
			if (col > 8){
				std::cerr << "The FEN string is invalid; there are too many rows!" << std::endl;
				// now destroy board to clean up memory
				destroyBoard();
				return;
			}
		}	
	}

	// check element 1 to get whose turn it is	
	if (output[1] == "w"){
		turn = WHITE;
	}
	else if (output[1] == "b"){
		turn = BLACK;
	}
	else {
		std::cerr << "An incorrect turn letter was provided in the FEN string!" << std::endl;
		destroyBoard();
		return;
	}
	
	// check element 2 to get castling info 
	white_castle_k = false;
	white_castle_q = false;
	black_castle_k = false;
	black_castle_q = false;
	for (int i=0; i<static_cast<int>(output[2].size()); i++){
		switch(output[2][i]){
			case 'K': white_castle_k = true;
					  break;
			case 'Q': white_castle_q = true;
					  break;
			case 'k': black_castle_k = true;
					  break;
			case 'q': black_castle_q = true;
					  break;
		}
	}

	// check element 3 to get en passant info 
	en_passant_target = output[3];

	// check element 4 to get the half move count
	half_move_clock = std::stoi(output[4]);

	// check element 5 to get the full move count
	full_move_counter = std::stoi(output[5]);

	std::cout << "A new board state is loaded!" << std::endl;
}


/* A function to print the chessboard to the screen */
void ChessBoard::displayBoard() const{
	std::cout << "    A   B   C   D   E   F   G   H \n";
	std::cout << "  +===+===+===+===+===+===+===+===+\n";
	for (int row = 0; row < 8; row++){
		std::cout << 8-row << " |";
		for (int col = 0; col < 8; col ++){
			if (board[row][col] == nullptr){
				std::cout << "   " << "|";
			}
			else{
				std::cout << " " << *board[row][col] << " |";
			}
		}
		std::cout << "\n";
		//for all but the last row
		if (row != 7){
			std::cout << "  +---+---+---+---+---+---+---+---+\n";
		}
	}
	std::cout << "  +===+===+===+===+===+===+===+===+" << std::endl;
}


/* A function to get a chess piece from the chess board */
ChessPiece* ChessBoard::getPiece(const int row, const int col) const{
	if (row >= 0 && row < 8 && col >=0 && col < 8){
		return board[row][col];
	}
	else {
		std::cerr << "Invalid row and column input provided." << std::endl;
		return nullptr;
	}
}


/* A function to get the location of the white king on out board */
std::string ChessBoard::getWhiteKingPos() const{
	return white_king_pos;
}


/* A function to get the location of the black king on out board */
std::string ChessBoard::getBlackKingPos() const{
	return black_king_pos;
}


/* A function to get the location of the square that a pawn needs to move into to perform en passant */
std::string ChessBoard::getEnPassantTarget() const{
	return en_passant_target;
}


/* A function that returns true if a given row and column on our board represents a piece of the given colour */
bool ChessBoard::isOwnPiece(int row, int col, Colour colour) const{
	return board[row][col]!=nullptr && board[row][col]->getColour()==colour;
}


/* A function that returns true if a given row and column on our board represents a piece of the opposite colour to the one given */
bool ChessBoard::isEnemyPiece(int row, int col, Colour colour) const{
	return board[row][col]!=nullptr && board[row][col]->getColour()!=colour;
}


/* A function to submit a move from one position to another. */ 
void ChessBoard::submitMove(const std::string start_pos, const std::string end_pos){
	int	start_row = posToRow(start_pos);
	int	start_col = posToCol(start_pos);
	int	end_row = posToRow(end_pos);
	int	end_col = posToCol(end_pos);
	
	// error checking on position inputs
	if (start_row < 0 || start_row > 7 || start_col < 0 || start_col > 7 ||
			end_row < 0 || end_row > 7 || end_col < 0 || end_col > 7){
		std::cerr << "Incorrect inputs provided." << std::endl;
		return;
	}

	// Check if we have a piece at that position in the first place
	if (getPiece(start_row, start_col) == nullptr){
		std::cerr << "There is no piece at position " << start_pos << "!" << std::endl;
		return;
	}

	// Check if the move is even a move
	if (start_pos == end_pos){
		std::cerr << "There is no move submitted!" << std::endl;
		return;
	}

	// Check if the right player is submitting a move
	if (getPiece(start_row, start_col)->getColour() != turn){
		std::cerr << "It is not " << getPiece(start_row, start_col)->getColour(); 
		std::cerr << "'s turn to make a move!" << std::endl;
		return;
	}

	if (half_move_clock >= 50){
		char draw;
		std::cout << "The fifty-move rule has been met. Would " << turn << " like a draw (y or n?" << std::endl;
		std::cin >> draw;
		if (draw == 'y'){
			std::cout << "The match is drawn." << std::endl;
			return;
		}
	}

	// See what sort of move we are making. We have different logic if it is a castle
	// If it is a castle move
	if (isCastleMove(start_pos, end_pos)){
		if (tryCastleMove(start_pos, end_pos)){
			half_move_clock++;
			// get character output for which side we're castling to
			std::string side = ((posToCol(end_pos) - posToCol(start_pos)) == 2) ? "king" : "queen";
			std::cout << getPiece(start_row, start_col) << " castles to the " << side << "'s side" << std::endl;
			
			// Move Rook
			//queen's side castle
			if (posToCol(end_pos) == 2){
				makeBoardMove(start_row, 0, start_row, 3);
			}
			//king's side castle
			else {
				makeBoardMove(start_row, 7, start_row, 5);
			}	
			
			// Move King
			makeBoardMove(start_row, start_col, end_row, end_col);
			updateKingPosition(start_pos, end_pos);
		}
		// Otherwise return error message
		else {
			std::cerr << getPiece(start_row, start_col) << " cannot move to " << end_pos << "!" << std::endl;
			return;
		}
	}
	// Regular and en passant move
	else {
		if (tryMove(start_pos, end_pos)){
			half_move_clock++;
			std::cout << getPiece(start_row, start_col) << " moves from " << start_pos << " to " << end_pos;
			if (getPiece(end_row, end_col) != nullptr){
				half_move_clock = 0;
				std::cout << " taking " << getPiece(end_row, end_col);		
			}
			else if (end_pos == en_passant_target){
				half_move_clock = 0;
				std::cout << " taking " << getPiece(posToRow(en_passant_pawn_pos), posToCol(en_passant_pawn_pos));
				std::cout << " by en passant";
			}
			std::cout << std::endl;
			updateKingPosition(start_pos, end_pos);
			
			// check for rook moves. If we move a rook and we could previouly castle in that direction, we can no longer do so
			if (start_pos == "A1" && white_castle_q){
				white_castle_q = false;
			}
			else if (start_pos == "H1" && white_castle_k){
				white_castle_k = false;

			}
			else if (start_pos == "A8" && black_castle_q){
				black_castle_q = false;
			
			}
			else if (start_pos == "H8" && black_castle_k){
				black_castle_k = false;
			}

			makeBoardMove(start_row, start_col, end_row, end_col);

			// sets or resets the board's en passant status as required
			// also updates the board's pawn positions and the half move clock if needed
			setEnPassantStatus(start_pos, end_pos);
		}
		// Otherwise return error message
		else {
			std::cerr << getPiece(start_row, start_col) << " cannot move to " << end_pos << "!" << std::endl;
			return;
		}
	}

	

	//now the move has been made change turn
	turn = (turn == WHITE) ? BLACK : WHITE;

	if (turn == BLACK){
		full_move_counter++;
	}
	
	// Check if the opponent is now in check
	// if yes, Check if the opponent is in checkmate
	if (isCheck(turn)){
		if (isCheckmate(turn)){
			std::cout << turn << " is in checkmate" << std::endl;
			return;
		}
		else {
			std::cout << turn << " is in check" << std::endl;
			return;
		}
	}
	// Check if the opponent is in stalemate	
	else {
		if (isStalemate(turn)){
			std::cout << turn << " is in stalemate" << std::endl;
			return;
		}
	}
	if (half_move_clock == 75){
		std::cout << "The half-move clock has reached 75. The game is now drawn" << std::endl;
		return;
	}
	
}


/* A function to delete all heap pointers on our board and assign them to NULL */
void ChessBoard::destroyBoard(){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			delete board[row][col];
			board[row][col] = nullptr; //prevent pointer being dangling
		}
	}
}


/* A function to update the location of a colour's king */
void ChessBoard::updateKingPosition(const std::string start_pos, const std::string end_pos){
	if (start_pos == white_king_pos){
		white_king_pos = end_pos;
		white_castle_k = false;
		white_castle_q = false;
	}
	else if (start_pos == black_king_pos){
		black_king_pos = end_pos;
		black_castle_k = false;
		black_castle_q = false;
	}
}


/* A function to move the pieces around on board. It moves a piece from the start position to the end position */
void ChessBoard::makeBoardMove(const int start_row, const int start_col, const int end_row, const int end_col){
	// extra logic for en passant
	if (inArray(rowColToPos(start_row, start_col), pawn_positions, 16) != -1 && 
			rowColToPos(end_row, end_col) == en_passant_target){
		delete board[posToRow(en_passant_pawn_pos)][posToCol(en_passant_pawn_pos)];
		board[posToRow(en_passant_pawn_pos)][posToCol(en_passant_pawn_pos)] = nullptr; //no dangling pointer
	}
	else {
		delete board[end_row][end_col];
	}

	// check if we need to do a pawn promotion or not
	if (pawnPromotion(start_row, start_col, end_row, end_col)){
		char piece;
		std::cout << "Pawn is being promoted. ";
		do
		{
			std::cout << "Please enter the piece you would like (Q, R, B or N): " << std::endl;
			std::cin >> piece;
			switch(piece){
				case 'Q': board[end_row][end_col] = new Queen(getPiece(start_row, start_col)->getColour());
						  break;
				case 'q': board[end_row][end_col] = new Queen(getPiece(start_row, start_col)->getColour());
						  break;
				case 'R': board[end_row][end_col] = new Rook(getPiece(start_row, start_col)->getColour());
						  break;
				case 'r': board[end_row][end_col] = new Rook(getPiece(start_row, start_col)->getColour());
						  break;
				case 'B': board[end_row][end_col] = new Bishop(getPiece(start_row, start_col)->getColour());
						  break;
				case 'b': board[end_row][end_col] = new Bishop(getPiece(start_row, start_col)->getColour());
						  break;
				case 'N': board[end_row][end_col] = new Knight(getPiece(start_row, start_col)->getColour());
						  break;
				case 'n': board[end_row][end_col] = new Knight(getPiece(start_row, start_col)->getColour());
						  break;
				default: std::cout << piece << " is not a correct letter. Please try again." << std::endl;
						 piece = '0';
						 break;
			}
		}
		while (piece == '0');
	}
	else {
		board[end_row][end_col] = board[start_row][start_col];
	}
	
	board[start_row][start_col] = nullptr;
}


/* A function to try and make a move from a given start position to another */
bool ChessBoard::tryMove(const std::string start_pos, const std::string end_pos){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// First check if the piece can 'geometrically' move to the target location
	if (!board[start_row][start_col]->isLegalMove(start_pos, end_pos, *this)){
		return false;
	}

	// Now check if making the move puts 'our' own king in check. We do this by trying to make the move first	
	bool valid_move;
	ChessPiece* start_piece = getPiece(start_row, start_col);
	ChessPiece* end_piece = getPiece(end_row, end_col);

	board[end_row][end_col] = board[start_row][start_col];
	board[start_row][start_col] = nullptr;

	// Extra logic needed for if the move is en passant
	int en_passant_pawn_row;
	int en_passant_pawn_col;
	if (end_pos == en_passant_target){
		en_passant_pawn_row = posToRow(en_passant_pawn_pos);
		en_passant_pawn_col = posToCol(en_passant_pawn_pos);
		end_piece = getPiece(en_passant_pawn_row, en_passant_pawn_col);
		board[en_passant_pawn_row][en_passant_pawn_col] = nullptr;
	}
	
	// Special logic for if we move the king. This needs to be done to check subsequent checks 
	// and be able to revert the king position if the move is not feasible
	// define these strings outside first so they don't disappear after the if code blocks
	std::string white_king_start = "";
	std::string black_king_start = "";
	if (start_pos == white_king_pos){
		white_king_pos = end_pos;
		white_king_start = start_pos;
	}
	if (start_pos == black_king_pos){
		black_king_pos = end_pos;
		black_king_start = start_pos;
	}

	if (isCheck(start_piece->getColour())){
		valid_move = false;
	}
	else {
		valid_move = true;
	}
	
	// Revert the board. At this stage, we have confirmed whether the move is valid according to chess rules
	board[start_row][start_col] = board[end_row][end_col];
	// special logic for if the move was an en passant move
	if (end_pos == en_passant_target){
		board[en_passant_pawn_row][en_passant_pawn_col] = end_piece;
		board[end_row][end_col] = nullptr;
	} else{
		board[end_row][end_col] = end_piece;
	}
	
	// set end_piece to a nullptr so when we exit the stack frame, we have no memory deallocation issues
	end_piece = nullptr;
	// now also revert the king position if needed
	if (start_pos == white_king_start){
		white_king_pos = white_king_start;
	}	
	else if (start_pos == black_king_start){
		black_king_pos = black_king_start;
	}	

	return valid_move;
}


/* A function to check if a given move is a castle move or not. This simply checks if the king is moving 2 horizontally or not */
bool ChessBoard::isCastleMove(const std::string start_pos, const std::string end_pos){
	// check to confirm we are moving a king
	if (!(start_pos == white_king_pos || start_pos == black_king_pos)){
		return false;
	}

	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);	

	// get magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;
	// check move magnitudes are what we expect for a castle
	if (std::abs(col_delta) != 2 || row_delta != 0){
		return false;
	}
	return true;
}


/* A function to try and make a castle move. This includes relevant checks to ensure a castle move is valid */
bool ChessBoard::tryCastleMove(const std::string start_pos, const std::string end_pos){
	// check to confirm we are moving a king
	if (!(start_pos == white_king_pos || start_pos == black_king_pos)){
		return false;
	}
	
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);	
		
	// get magnitudes of the move
	int row_delta = end_row - start_row;
	int col_delta = end_col - start_col;

	if (row_delta != 0 || std::abs(col_delta) != 2){
		return false;
	}

	// check castle based on board state and submitted positions.
	// The board state positions should automatically ensure the relevant king is in the right row
	if (getPiece(start_row, start_col)->getColour() == WHITE){
		// castling isn't feasible
		if (!(white_castle_k || white_castle_q)){
			return false;
		}
		else {
			// check if king's side castle
			if (col_delta == 2 && !white_castle_k){
				return false;
			}
			// check if queen's side castle
			else if (col_delta == -2 && !white_castle_q){
				return false;
			}
		}
	}
	else {
		// castling isn't feasible
		if (!(black_castle_k || black_castle_q)){
			return false;
		}
		else {
			// check for king's side castle
			if (col_delta == 2 && !black_castle_k){
				return false;
			}
			// check for queen's side castle
			else if (col_delta == -2 && !black_castle_q){
				return false;
			}
		}
	}

	// ensure the king is not already in check. If so, we cannot castle.
	if (isCheck(getPiece(start_row, start_col)->getColour())){
		return false;
	}
	
	// Check if we can move the king to the right position. Need to ensure king doesn't move through check
	for (int col_change=0; col_change <= std::abs(col_delta); col_change++){
		if (col_change == 0){
			continue;
		}
		int col_change_signed = col_change;
		if (std::signbit(col_delta)){
			col_change_signed = col_change*-1;
		}
		// don't need to worry about the rook end point being an enemy piece
		// as the king would not have been able to make the move in the first piece so we would never even reach here
		if (!tryMove(start_pos, rowColToPos(start_row, start_col + col_change_signed))){
			return false;
		}
	}

	// We can in theory move the king to the right spot. Now get the appropriate rook and try to move it.
	// Queen's side
	if (col_delta < 0){
		if (!tryMove(rowColToPos(start_row, 0), rowColToPos(start_row, 3))){
			return false;
		}
	}
	//king's side
	else {
		if (!tryMove(rowColToPos(start_row, 7), rowColToPos(start_row, 5))){
			return false;
		}
	}

	return true;
}


/* A function to check if a given move is one that leads to pawn promotion */
bool ChessBoard::pawnPromotion(const int start_row, const int start_col, const int end_row, const int end_col){
	// check if piece that was moving was a pawn
	if (inArray(rowColToPos(start_row, start_col), pawn_positions, 16) != -1){
		if (getPiece(start_row, start_col)->getColour() == WHITE && end_row == 0){
			return true;
		}
		else if (getPiece(start_row, start_col)->getColour() == BLACK && end_row == 7){
			return true;
		}
	}
	return false;
}


/* A function to update the array which contains the locations of pawns on the board */
void ChessBoard::updatePawnPositions(const std::string start_pos, const std::string end_pos){
	// check if a pawn was captured
	if (inArray(end_pos, pawn_positions, 16) != -1){
		pawn_positions[inArray(end_pos, pawn_positions, 16)] = "";
	}
	// check if a pawn was captured by en passant
	else if (inArray(start_pos, pawn_positions, 16) != -1 && end_pos == en_passant_target){
		pawn_positions[inArray(en_passant_pawn_pos, pawn_positions, 16)] = "";
	}
	// now make update if we were moving a pawn in the first place
	if (inArray(start_pos, pawn_positions, 16) != -1){
		pawn_positions[inArray(start_pos, pawn_positions, 16)] = end_pos;
		// reset half move clock
		half_move_clock = 0;
	}
}


/* A function to set the en passant status for the board. Sets if a pawn moves 2, resets otherwise */
void ChessBoard::setEnPassantStatus(const std::string start_pos, const std::string end_pos) {
	// by the time this function is used, we are assuming the move is valid and doable
	int	start_row = posToRow(start_pos);
	int	start_col = posToCol(start_pos);
	int	end_row = posToRow(end_pos);
	//int end_col = posToCol(end_pos);

	int row_delta = end_row-start_row;

	// check if the piece is a pawn moving forwards by 2
	if (inArray(start_pos, pawn_positions, 16) < 16 && std::abs(row_delta) == 2){
		en_passant_target = rowColToPos(start_row + row_delta/2, start_col);
		en_passant_pawn_pos = end_pos;
		// now we can update pawn positions as we have now checked whether the start_pos is a pawn
		updatePawnPositions(start_pos, end_pos);
	}
	// the piece is not a pawn moving 2 spaces, so en passant states revert to 'nothing'
	else {
		updatePawnPositions(start_pos, end_pos);
		en_passant_target = "-";
		en_passant_pawn_pos = "-";
	}
}


/* A function to check if a particular colour is in check */
bool ChessBoard::isCheck(Colour colour){
	// get king starting position
	std::string king_start_pos = (colour==WHITE) ? white_king_pos : black_king_pos;

	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (isEnemyPiece(row, col, colour)){
				if (getPiece(row, col)->isLegalMove(rowColToPos(row, col), king_start_pos, *this)){
					return true;
				}
			}
		}
	}
	return false;
}


/* Can a piece of the colour specified move to the location specified. True if we can */
bool ChessBoard::moveOwnPiece(const std::string target_pos, Colour colour){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (isOwnPiece(row, col, colour)){	
				if (tryMove(rowColToPos(row, col), target_pos)){
					return true;
				}
			}
		}
	}
	return false;
}


/* A function to check if a given colour is in checkmate */
bool ChessBoard::isCheckmate(Colour colour){
	// get starting king position to help with offsets for checking if we can protect' the king
	std::string king_start_pos = (colour==WHITE) ? white_king_pos : black_king_pos;

	// check if the king can validly move one space in any direction (not just if it is geometrically legal)
	// this is to ensure that the king doesn't take a checking piece if the checking piece is protected
	for (int row_delta = -1; row_delta <= 1; row_delta++){
		for (int col_delta = -1; col_delta <= 1; col_delta++){
			std::string new_pos = rowColToPos(posToRow(king_start_pos) + row_delta, posToCol(king_start_pos) + col_delta);
			if (tryMove(king_start_pos, new_pos)){
				return false;
			}
		}
	}

	// If we get here, the king cannot move anywhere
	// As a potential efficiency improvement, we also check if we can check the king from two locations
	// Given the king can't move, this means we are in checkmate
	int check_count = 0;
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (isEnemyPiece(row, col, colour)){	
				if (getPiece(row, col)->isLegalMove(rowColToPos(row, col), king_start_pos, *this)){
				// if we are here, we have found our checking piece. Now see if we can take or block it
					check_count++;
					if (check_count > 1){
						return true;
					}

					int row_delta = row - posToRow(king_start_pos);
					int col_delta = col - posToCol(king_start_pos);	
					
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
							// diagonal check logic
							if (std::abs(row_delta) == std::abs(col_delta)){
								if (std::abs(row_change_signed) == std::abs(col_change_signed)){ 
									//check if we can't block the check
									if (moveOwnPiece(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
												posToCol(king_start_pos)+col_change_signed), colour)){
										return false;
									} 
								}
							}
							// horizontal check logic
							else if (row_delta == 0){
								if (std::abs(row_change_signed) == 0){
									if (moveOwnPiece(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
												posToCol(king_start_pos)+col_change_signed), colour)){
										return false;
									}
								}
							}
							// vertical check logic
							else if (col_delta == 0){
								if (std::abs(col_change_signed) == 0){
									if (moveOwnPiece(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
												posToCol(king_start_pos)+col_change_signed), colour)){
										return false;
									}
								}
							}
							// knight check logic
							else if ((std::abs(row_delta) == 2 && std::abs(col_delta) == 1) ||
									(std::abs(row_delta) == 1 && std::abs(col_delta) == 2) ){
								if (moveOwnPiece(rowColToPos(row, col), colour)){
									return false;
								}
							}
						}
					}
				}
			}
		}
	}

	return true;
}


/* A function to check if a given colour is in stalemate */ 
bool ChessBoard::isStalemate(Colour colour){
	// for all pieces of same colour, try making a legal move to any square on the board.
	// if nothing is legal, we have a stalemate
	for (int row=0; row < 8; row++){
		for (int col=0; col<8; col++){
			if (isOwnPiece(row, col, colour)){
				// now loop through our board again to check each position as potential move for a given piece
				std::string start_pos = rowColToPos(row, col);
				for (int row2=0; row2<8; row2++){
					for (int col2=0; col2<8; col2++){
						if (tryMove(start_pos, rowColToPos(row2, col2))){
							return false;
						}
					}
				}	
			}
		}
	}
	return true;
}
