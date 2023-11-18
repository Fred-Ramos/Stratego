#stratego executable and its dependecies
#object code needs "-c" 

stratego.exe : main.o game.o board.o piece.o
	g++ main.o game.o board.o piece.o -o stratego.exe

main.o : logic/main.cpp logic/game.cpp logic/game.h logic/board.cpp logic/board.h logic/piece.cpp logic/piece.h
	g++ -Wall -c logic/main.cpp

game.o : logic/game.cpp logic/game.h
	g++ -Wall -c logic/game.cpp

board.o : logic/board.cpp logic/board.h
	g++ -Wall -c logic/board.cpp

piece.o : logic/piece.cpp logic/piece.h
	g++ -Wall -c logic/piece.cpp

clean :
	rm *.o stratego.exe