chess: ChessMain.o ChessBoard.o ChessPieces.o helpers.o
	g++ -g -Wall ChessMain.o ChessBoard.o ChessPieces.o helpers.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -g -Wall -c ChessMain.cpp

play: play.o ChessBoard.o ChessPieces.o helpers.o
	g++ -g -Wall play.o ChessBoard.o ChessPieces.o helpers.o -o play

play.o: play.cpp ChessBoard.h
	g++ -g -Wall -c play.cpp

test: test.o ChessBoard.o ChessPieces.o helpers.o
	g++ -g -Wall test.o ChessBoard.o ChessPieces.o helpers.o -o test

test.o: test.cpp ChessBoard.h
	g++ -g -Wall -c test.cpp

helpers.o: helpers.h helpers.cpp
	g++ -g -Wall -c helpers.cpp

ChessBoard.o: ChessBoard.h ChessBoard.cpp ChessPieces.h helpers.h
	g++ -g -Wall -c ChessBoard.cpp

ChessPieces.o: ChessPieces.h ChessPieces.cpp helpers.h
	g++ -g -Wall -c ChessPieces.cpp

clean:
	rm -f *.o chess test
