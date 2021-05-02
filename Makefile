straights : main.o cards.o game.o players.o
	g++ main.o cards.o game.o players.o -o straights
main.o : main.cc game.h cards.h players.h
	g++ -std=c++14 -Werror=vla -c main.cc
game.o : game.cc game.h players.h cards.h
	g++ -std=c++14 -c game.cc
players.o : players.cc players.h cards.h
	g++ -std=c++14 -c players.cc
cards.o : cards.cc cards.h
	g++ -std=c++14 -c cards.cc