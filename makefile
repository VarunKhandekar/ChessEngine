chess: ChessMain.o ChessBoard.o ChessPieces.o
	g++ -g -Wall ChessMain.o ChessBoard.o ChessPieces.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h ChessPieces.h
	g++ -g -Wall -c ChessMain.cpp

ChessBoard.o: ChessBoard.h ChessBoard.cpp ChessPieces.h
	g++ -g -Wall -c ChessBoard.cpp

ChessPieces.o: ChessPieces.h ChessPieces.cpp
	g++ -g -Wall -c ChessPieces.cpp

clean:
	rm -f *.o traffic test
