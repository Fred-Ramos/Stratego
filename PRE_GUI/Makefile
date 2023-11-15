#stratego executable and its dependecies
#object code needs "-c" 

stratego.exe : main.o game.o board.o piece.o
	g++ main.o game.o board.o piece.o -o stratego.exe

main.o : main.cpp game.cpp game.o board.cpp board.h piece.cpp piece.h
	g++ -Wall -c main.cpp

game.o : game.cpp game.h
	g++ -Wall -c game.cpp

board.o : board.cpp board.h
	g++ -Wall -c board.cpp

piece.o : piece.cpp piece.h
	g++ -Wall -c piece.cpp

clean :
	rm *.o stratego.exe