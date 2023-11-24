#include "ChessBoard.h"

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


/* Helper: gets the row number from a position */
int ChessBoard::posToRow(std::string pos){
	// convert ASCII to appropriate integer
	return pos[0] - 65;
}


/* Helper: gets the col number from a position */
int ChessBoard::posToCol(std::string pos){
	// convert ASCII to appropriate integer e.g. "8" goes to 0, "1" goes to 7, based on rank order of chessboard
	return 56 - pos[1];
}


/* Helper: converts a rown and column to a string position */
std::string ChessBoard::rowColToPos(int row, int col){
	std::string position = "";

	position +=static_cast<char>(65 + row); //add file
	position +=static_cast<char>(56 - col); //add rank

	return position;
}


void ChessBoard::destroyBoard(){
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			delete board[row][col];
			board[row][col] = nullptr; //prevent pointer being dangling
		}
	}
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
				case 'K': board[row][col] = new ChessPiece(rowColToPos(row, col), WHITE);
						  break;
				case 'Q': board[row][col] = new Queen(rowColToPos(row, col), WHITE);
						  break;
				case 'R': board[row][col] = new Rook(rowColToPos(row, col), WHITE);
						  break;
				case 'B': board[row][col] = new Bishop(rowColToPos(row, col), WHITE);
						  break;
				case 'N': board[row][col] = new Knight(rowColToPos(row, col), WHITE);
						  break;
				case 'P': board[row][col] = new Pawn(rowColToPos(row, col), WHITE);
						  break;

				// Black pieces
				case 'k': board[row][col] = new King(rowColToPos(row, col), BLACK);
						  break;
				case 'q': board[row][col] = new Queen(rowColToPos(row, col), BLACK);
						  break;
				case 'r': board[row][col] = new Rook(rowColToPos(row, col), BLACK);
						  break;
				case 'b': board[row][col] = new Bishop(rowColToPos(row, col), BLACK);
						  break;
				case 'n': board[row][col] = new Knight(rowColToPos(row, col), BLACK);
						  break;
				case 'p': board[row][col] = new Pawn(rowColToPos(row, col), BLACK);
						  break;
				
				default: std::cerr << "Invalid letter provided in the FEN string. Please check!" << std::endl;
						 destroyBoard();
						 return;
			}
		}

	}

	// check element 1 to get whose turn it is	
	if (output[1] == 'w'){
		turn = WHITE;
	}
	else if (output[1] == 'b'){
		turn = BLACK;
	}
	else {
		std::cerr << "An incorrect turn letter was provided in the FEN string!" << std::endl;
		destroyBoard();
		return
	}
	
	// check element 2 to get castling info
	output[2].find("K") ? white_castle_k = true : white_castle_k = false;
	output[2].find("Q") ? white_castle_q = true : white_castle_q = false;
	output[2].find("k") ? black_castle_k = true : black_castle_k = false;
	output[2].find("q") ? black_castle_q = true : black_castle_q = false;


}



void ChessBoard::submitMove(std::string start_pos, std::string end_pos){
	//do checks


	//change turn

}

