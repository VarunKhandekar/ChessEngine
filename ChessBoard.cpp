#include "ChessBoard.h"
#include "ChessPieces.h"

// constructor
ChessBoard::ChessBoard(){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			board[row][col] = nullptr;
		}
	}
}

//destructor
ChessBoard::~ChessBoard(){
	destroyBoard();
}


void ChessBoard::destroyBoard(){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			delete board[row][col];
			board[row][col] = nullptr; //prevent pointer being dangling
		}
	}
}


void ChessBoard::displayBoard(){
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
				case 'R': if (col == 7){
							  // king's side castle
							  board[row][col] = new Rook(WHITE, true);
						  }
						  else {
							  // queen's side castle
							  board[row][col] = new Rook(WHITE, false);
						  }
						  break;
				case 'B': board[row][col] = new Bishop(WHITE);
						  break;
				case 'N': board[row][col] = new Knight(WHITE);
						  break;
				case 'P': board[row][col] = new Pawn(WHITE);
						  break;

				// Black pieces
				case 'k': board[row][col] = new King(BLACK);
						  black_king_pos = rowColToPos(row, col);
						  break;
				case 'q': board[row][col] = new Queen(BLACK);
						  break;
				case 'r': if (col == 7){
							  // king's side castle
							  board[row][col] = new Rook(BLACK, true);
						  }
						  else {
							  board[row][col] = new Rook(BLACK, false);
						  }
						  break;
				case 'b': board[row][col] = new Bishop(BLACK);
						  break;
				case 'n': board[row][col] = new Knight(BLACK);
						  break;
				case 'p': board[row][col] = new Pawn(BLACK);
						  break;
				
				default: std::cerr << "Invalid letter provided in the FEN string. Please check!" << std::endl;
						 destroyBoard();
						 return;
			}
			col++;
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

	std::cout << "A new board state is loaded!" << std::endl;
}


void ChessBoard::submitMove(std::string start_pos, std::string end_pos){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);

	// Check if we have a piece at that position in the first place
	if (board[start_row][start_col] == nullptr){
		std::cerr << "There is no piece at position " << start_pos << "!" << std::endl;
		return;
	}

	// Check if the move is even a move
	if (start_pos == end_pos){
		std::cerr << "There is no move submitted!" << std::endl;
		return;
	}

	// Check if the right player is submitting a move
	if (board[start_row][start_col]->getColour() != turn){
		std::cerr << "It is not " << board[start_row][start_col]->getColour(); 
		std::cerr << "'s turn to make a move!" << std::endl;
		return;
	}

	// Check if the move is legal
	
	if (!makeMove(start_pos, end_pos)){
		std::cerr << board[start_row][start_col] << " cannot move to " << end_pos << "!" << std::endl;
		return;
	}
	// if it was, make changes to the board and the king positions if appropriate
	else {
		std::cout << board[start_row][start_col] << " moves from " << start_pos << " to " << end_pos;
		if (board[end_row][end_col] != nullptr){
			std::cout << " taking " << board[end_row][end_col];		
		}
		std::cout << std::endl;

		if (start_pos == white_king_pos){
			white_king_pos = end_pos;
		}
		else if (start_pos == black_king_pos){
			black_king_pos = end_pos;
		}
		delete board[end_row][end_col];
		board[end_row][end_col] = board[start_row][start_col];
		board[start_row][start_col] = nullptr;
	}
	
	//now the move has been made change turn
	turn = (turn == WHITE) ? BLACK : WHITE;
	
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
}

/* Returns true if the move was successfully made */
bool ChessBoard::makeMove(std::string start_pos, std::string end_pos){
	int start_row = posToRow(start_pos);
	int start_col = posToCol(start_pos);
	int end_row = posToRow(end_pos);
	int end_col = posToCol(end_pos);


	// First check if the piece can legally move to the target location
	if (!board[start_row][start_col]->isLegalMove(start_pos, end_pos, *this)){
		return false;
	}

	// Now check if making the move puts 'our' own king in check. We do this by trying to make the move first	
	ChessPiece* start_piece = board[start_row][start_col];
	ChessPiece* end_piece = nullptr;

	end_piece = board[end_row][end_col];
	board[end_row][end_col] = board[start_row][start_col];
	board[start_row][start_col] = nullptr;
	
	
	// Special logic for if we move the king. This needs to be done to check subsequent checks
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
		//revert board as the move was not possible
		board[start_row][start_col] = board[end_row][end_col];
		board[end_row][end_col] = end_piece;
		// set end_piece to a nullptr so when we exit the stack frame, we have no memory deallocation issues
		end_piece=nullptr;
		//now also revert the board's king position
		if (start_piece->getColour()==WHITE){
			if (start_pos == white_king_start){
				white_king_pos = white_king_start;
			}
		}
		else {
			if (start_pos == black_king_start){
				black_king_pos = black_king_start;
			}
		}
		return false;
	}

	// If we reach here, we are not in check, so the move is ok
	// Revert the board. At this stage, we have confirmed the move is legally correct in chess rules
	board[start_row][start_col] = board[end_row][end_col];
	board[end_row][end_col] = end_piece;
	// set end_piece to a nullptr so when we exit the stack frame, we have no memory deallocation issues
	end_piece=nullptr;
	//now also revert the king position if needed
	if (start_pos == white_king_start){
		white_king_pos = white_king_start;
	}	
	else if (start_pos == black_king_start){
		black_king_pos = black_king_start;
	}	

	return true;
}


bool ChessBoard::isCheck(Colour colour){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]!=nullptr){
				if (board[row][col]->getColour()!=colour){
					if (colour==WHITE){
						if (makeMove(rowColToPos(row, col), white_king_pos)){
							return true;
						}
					}
					else {
						if (makeMove(rowColToPos(row, col), black_king_pos)){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

/* Can we block a check. True if we can */
bool ChessBoard::blockCheck(std::string target_pos, Colour colour){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]!=nullptr){
				if (board[row][col]->getColour()==colour){
					// if we can't block or take
					if (makeMove(rowColToPos(row, col), target_pos)){
						return true;
					}
				}
			}
		}
	}
	return false;
}


bool ChessBoard::isCheckmate(Colour colour){
	// get starting king position to help with offsets for checking if we can protect' the king
	std::string king_start_pos = "";
	if (colour == WHITE){
		king_start_pos = white_king_pos;
	}
	else {
		king_start_pos = black_king_pos;
	}

	// check if the king can move one space in any direction legally	
	for (int row_delta = -1; row_delta <= 1; row_delta++){
		for (int col_delta = -1; col_delta <= 1; col_delta++){
			std::string new_pos = rowColToPos(posToRow(king_start_pos) + row_delta, posToCol(king_start_pos) + col_delta);
			// recall make move will alter the king's position and the board if a move was legal. So we must revert it
			if (makeMove(king_start_pos, new_pos)){
				return false;
			}
		}
	}

	// If we get here, the king cannot move anywhere
	// For a potential efficiency improvement, we also check if we can check the king from two locations
	// Given the king can't move, this means we are in checkmate
	int check_count = 0;
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]!=nullptr){
				if (board[row][col]->getColour()!=colour){
					if (makeMove(rowColToPos(row, col), king_start_pos)){
						check_count++;
						if (check_count > 1){
							return true;
						}

						//if true, we have found our checking piece. Now see if we can take or block it
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
								//diagonal check logic
								if (std::abs(row_delta) == std::abs(col_delta)){
									if (std::abs(row_change_signed) == std::abs(col_change_signed)){ 
										//check if we can't block the check
										if (blockCheck(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
													posToCol(king_start_pos)+col_change_signed), colour)){
											return false;
										} 
									}


								}
								//horizontal check logic
								else if (row_delta == 0){
									if (std::abs(row_change_signed) == 0){
										if (blockCheck(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
													posToCol(king_start_pos)+col_change_signed), colour)){
											return false;
										}
									}

								}
								//vertical check logic
								else if (col_delta == 0){
									if (std::abs(col_change_signed) == 0){
										if (blockCheck(rowColToPos(posToRow(king_start_pos)+row_change_signed, 
													posToCol(king_start_pos)+col_change_signed), colour)){
											return false;
										}
										else {
											check_count++;
											if (check_count > 1){
												return true;
											}
										} 
									}
								}
								// knight check logic
								else if ((std::abs(row_delta) == 2 && std::abs(col_delta) == 1) ||
										(std::abs(row_delta) == 1 && std::abs(col_delta) == 2) ){
									if (blockCheck(rowColToPos(row, col), colour)){
										return false;
									}
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



bool ChessBoard::isStalemate(Colour colour){
	//loop through rows and cols
	//for all pieces of same colour, try making a legal move to any square on the board.
	//if nothing is legal, we have a stalemate
	for (int row=0; row < 8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]!=nullptr){
				if (board[row][col]->getColour()==colour){
					// now loop through our board again to check each position as potential move for a given piece
					for (int row2=0; row2<8; row2++){
						for (int col2=0; col2<8; col2++){
							if (makeMove(rowColToPos(row, col), rowColToPos(row2, col2))){
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}


