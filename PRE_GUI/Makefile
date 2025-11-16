#stratego executable and its dependecies
#object code needs "-c" 

stratego.exe : main.o game.o board.o piece.o
	g++ main.o game.o board.o piece.o -o stratego.exe

main.o : src/main.cpp src/game.cpp src/game.h src/board.cpp src/board.h src/piece.cpp src/piece.h
	g++ -Wall -c src/main.cpp

game.o : src/game.cpp src/game.h
	g++ -Wall -c src/game.cpp

board.o : src/board.cpp src/board.h
	g++ -Wall -c src/board.cpp

piece.o : src/piece.cpp src/piece.h
	g++ -Wall -c src/piece.cpp

clean :
	rm *.o stratego.exe