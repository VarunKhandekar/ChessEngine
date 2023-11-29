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
				case 'K': board[row][col] = new King(rowColToPos(row, col), WHITE, false);
						  white_king_position = rowColToPos(row, col);
						  break;
				case 'Q': board[row][col] = new Queen(rowColToPos(row, col), WHITE);
						  break;
				case 'R': board[row][col] = new Rook(rowColToPos(row, col), WHITE, false);
						  break;
				case 'B': board[row][col] = new Bishop(rowColToPos(row, col), WHITE);
						  break;
				case 'N': board[row][col] = new Knight(rowColToPos(row, col), WHITE);
						  break;
				case 'P': board[row][col] = new Pawn(rowColToPos(row, col), WHITE, false);
						  break;

				// Black pieces
				case 'k': board[row][col] = new King(rowColToPos(row, col), BLACK, false);
						  black_king_position = rowColToPos(row, col);
						  break;
				case 'q': board[row][col] = new Queen(rowColToPos(row, col), BLACK);
						  break;
				case 'r': board[row][col] = new Rook(rowColToPos(row, col), BLACK, false);
						  break;
				case 'b': board[row][col] = new Bishop(rowColToPos(row, col), BLACK);
						  break;
				case 'n': board[row][col] = new Knight(rowColToPos(row, col), BLACK);
						  break;
				case 'p': board[row][col] = new Pawn(rowColToPos(row, col), BLACK, false);
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
	
	// check element 2 to get castling info TODO fix this
	//std::cout << output[2].find("K") << std::endl;
	output[2].find("K") ? white_castle_k = true : white_castle_k = false;
	output[2].find("Q") ? white_castle_q = true : white_castle_q = false;
	output[2].find("k") ? black_castle_k = true : black_castle_k = false;
	output[2].find("q") ? black_castle_q = true : black_castle_q = false;

	std::cout << "A new board state is loaded!" << std::endl;
}


void ChessBoard::submitMove(char* start_pos, char* end_pos){

	//std::cout << posToRow(start_pos) << std::endl;
	//std::cout << posToCol(start_pos) << std::endl;
	ChessPiece* current_piece = board[posToRow(start_pos)][posToCol(start_pos)];

	//std::cout << current_piece << std::endl;

	// Check if we have a piece at that position in the first place
	if (current_piece == nullptr){
		std::cerr << "There is no piece at position " << start_pos << "!" << std::endl;
		return;
	}

	// Check if the move is even a move
	if (start_pos == end_pos){
		std::cerr << "There is no move submitted!" << std::endl;
		return;
	}

	// Check if the right player is submitting a move
	if (current_piece->getColour() != turn){
		std::cerr << "It is not " << current_piece->getColour(); 
		std::cerr << "'s turn to make a move!" << std::endl;
		return;
	}

	// Check if the hypothesised move is even within the feasible set of moves
	





	//if (std::find(current_piece->getPotentialMoves().begin(), current_piece->getPotentialMoves().end(), end_pos) 
	//		
	//		== current_piece->getPotentialMoves().end()){
	//	std::cerr << current_piece << " cannot move to " << end_pos << "!" << std::endl;
	//	return;
	//}

	// Check if the move is legal
	

	// Check if the opponent is now in check
	// if yes:
	//	Check if the opponent is in checkmate
	// if no:
	//	Check if the opponent is in stalemate
	//	
	//	

	
	
	// Make the move. Delete start pointer
	// Consider if the target square is empty or opposing piece
	// If opposing piece, delete the pointer there (and assign to null). Reassign to start position pointer


	//




	//if all good, update board and change turn

}

bool ChessBoard::isCheck(Colour colour) const{
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]->getColour()!=colour){
				continue;
			}

		}

	}
	return false;
}


bool ChessBoard::isCheckmate(Colour colour){
	return true;
}


bool ChessBoard::isStalemate(Colour colour){
	return true;
}


//TODO could put each check into a void function


bool ChessBoard::validMove(char* start_pos, char* end_pos){
	// MAKE PRELIMINARY CHECKS ON THE SUBMITTED MOVE
	ChessPiece* current_piece = board[posToRow(start_pos)][posToCol(start_pos)];

	// Check if we have a piece at that position in the first place
	if (current_piece == nullptr){
		std::cerr << "There is no piece at position " << start_pos << "!" << std::endl;
		return false;
	}

	// Check if the move is even a move
	if (start_pos == end_pos){
		std::cerr << "There is no move submitted!" << std::endl;
		return false;
	}

	// Check if the right player is submitting a move
	if (current_piece->getColour() != turn){
		std::cerr << "It is not " << current_piece->getColour(); 
		std::cerr << "'s turn to make a move!" << std::endl;
		return false;
	}

	// Check if the hypothesised move is even within the feasible set of moves	
	if (std::find(current_piece->getPotentialMoves().begin(), current_piece->getPotentialMoves().end(), end_pos) 
			== current_piece->getPotentialMoves().end()){
		std::cerr << current_piece << " cannot move to " << end_pos << "!" << std::endl;
		return false;
	}
 
	// Check if the path is blocked
	

	return true;
}


