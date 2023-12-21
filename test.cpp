#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "ChessBoard.h"
#include "ChessPieces.h"
#include "helpers.h"

using namespace std;


bool modifyValue(int& x) {
    x *= 2;
return true;
}

int main(){
	
	//int number = 5;

	//cout << "Original value: " << number << endl;

	// Call the function within an if statement
	//if (!modifyValue(number)) {
	//}
	// Changes made inside the if statement persist outside
	//cout << "Value after if statement: " << number << endl;


//	string a = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";

//	vector<string> output;
		
//	istringstream iss(a);

	// create a string variable called token to hold each delimited value of our state
//	string token;
//	while (getline(iss, token, ' ')) {
//		output.push_back(token);
//	}

//	for (int i=0; i<static_cast<int>(output.size()); i++){
//		cout << output[i] << endl;

//	}
  //  string b = output[2];
	//output[2].find("W") ? cout << "yay" << endl : cout << "boo" << endl;


//	string c = "";

	//c.append(static_cast<char>(50));
	//strcat(c,static_cast<char>(50));
//	c+=static_cast<char>(65+1);
//	c+=static_cast<char>(56-7);

//	cout << c << endl;

	//char g = 'i';
	//switch(g){
	//	case 'i': cout << "success" << endl;
	//			  break;
//
//		default: cout << "fail" << endl;
//
//	}
//	cout << rowColToPos(1,1) << endl;;

	cout << "========================\n\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");

	//cout << inArray("E2", cb.pawn_positions, 16) << endl;
	cb.submitMove("E2", "E4");

	//cout << inArray("E4", cb.pawn_positions, 16) << endl;
	cb.submitMove("H7", "H6");
	cb.submitMove("E4", "E5");
	cb.submitMove("F7", "F5");


	//cout << inArray("E5", cb.pawn_positions, 16) << endl;


	cb.submitMove("E5", "F6");

	cout << '\n';

	//for (int row = 0; row < 8; row++){
	//	for (int col = 0; col < 8; col++){
	//		cout << "(" << row << ", " << col << "): ";
	//		if (cb.board[row][col] == nullptr){
	//			cout << "Pointer is null. We have a blank square." << endl;
	//		}
	//		else if (typeid(*cb.board[row][col]) == typeid(King)) {
	//			cout << "Pointer is pointing to a King object." << endl;
	//		} 
	//		else if (typeid(*cb.board[row][col]) == typeid(Queen)) {
	//			cout << "Pointer is pointing to a Queen object." << endl;
	//		} 
	//		else if (typeid(*cb.board[row][col]) == typeid(Rook)) {
	//			cout << "Pointer is pointing to a Rook object." << endl;
	//		} 
	//		else if (typeid(*cb.board[row][col]) == typeid(Bishop)) {
	//			cout << "Pointer is pointing to a Bishop object." << endl;
	//		} 
	//		else if (typeid(*cb.board[row][col]) == typeid(Knight)) {
	//			cout << "Pointer is pointing to a Knight object." << endl;
	//		} 
	//		else if (typeid(*cb.board[row][col]) == typeid(Pawn)) {
	//			cout << "Pointer is pointing to a Pawn object." << endl;
	//		} 
	//		else{ 
	//			cout << "fail" << endl;
	//		}
					

	//	}

	//}

	//cout << cb.board[0][0] << endl;

	//cout << *cb.board[0][0] << endl;

	cb.displayBoard();

	//cout << cb.board[0][1]->isLegalMove("B8", "A6", cb) << endl;

	cout << "==========" << endl;



	//cb.makeMove("E2", "E4");

	cb.displayBoard();
	
	//cb.makeMove("E7", "E5");

	cb.displayBoard();
	
	//cb.makeMove("F2", "F4");

	cb.displayBoard();

	
	//cout << cb.board[0][4]->isLegalMove("E8", "D8", cb) << endl;
	
	//cout << cb.board[1][4]->isLegalMove("E7", "E5", cb) << endl;
	
	//cout << cb.board[1][4]->isLegalMove("E7", "E4", cb) << endl;

	//cb.submitMove("E1", "E8");
	
	//
	Colour test_col = WHITE;

	cout << !!test_col << endl;
	

	cout << "========================================" <<std::endl;
	string d = "kbQ5/8/2K5/8/8/8/8/8 w ----";
	cb.loadState(d);

	cb.submitMove("C6", "B6");
	cb.displayBoard();
	
	cout << "\n\n========================================" <<std::endl;
	string e = "r3k3/8/8/8/8/8/8/7K b ---q";
	cb.loadState(e);

	cb.submitMove("E8", "C8");
	cb.displayBoard();
	
	cout << "\n\n========================================" <<std::endl;
	string f = "r3k3/4Q3/8/8/8/8/8/7K b ---q";
	cb.loadState(f);

	cb.submitMove("E8", "C8");
	cb.displayBoard();
	
	cout << "\n\n========================================" <<std::endl;
	string g = "r3k3/4Q3/8/8/8/8/8/7K b ---q";
	cb.loadState(g);

	cb.submitMove("E8", "C8");
	cb.displayBoard();
	
	cout << "\n\n========================================" <<std::endl;
	string h = "r3k3/4Q3/8/8/8/8/8/7K b ---q";
	cb.loadState(h);

	cb.submitMove("E8", "C8");
	cb.displayBoard();
	return 0;
}
