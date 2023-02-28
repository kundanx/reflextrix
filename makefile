all: compile link run

compile:
	g++ -Isrc/include  -c main.cpp	Game.cpp

link:
	g++ main.o Game.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	main.exe