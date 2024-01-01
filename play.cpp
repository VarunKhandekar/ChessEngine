#include <iostream>
//#include <string>
#include "ChessBoard.h"
//#include "ChessPieces.h"i

using namespace std;

int main() {
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";
	
	ChessBoard cb;
	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	cout << '\n';

	cb.displayBoard();
	string str_from, str_to;
	while (true) {
		cout << "Input next move (format: E2 E4, enter '0' to quit): ";
		cin >> str_from;
		if (str_from == "0") break;
		cin >> str_to;

		if (str_from[0] > 'Z')
			str_from[0] = str_from[0] - ('a' - 'A');
		if (str_to[0] > 'Z')
			str_to[0] = str_to[0] - ('a' - 'A');

		if (str_from[0] < 'A' || str_from[0] > 'H')
			continue;
		if (str_from[1] < '1' || str_from[1] > '8')
			continue;
		if (str_to[0] < 'A' || str_to[0] > 'H')
			continue;
		if (str_to[1] < '1' || str_to[1] > '8')
			continue;

		cb.submitMove(str_from, str_to);
		cb.displayBoard();
	    }
	return 0;
}
