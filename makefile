CC=g++ -std=c++11 -g
EXE=asn4

$(EXE)main: main.o room.o room.h event.o event.h game.o game.h wumpus.o wumpus.h stalactites.o stalactites.h gold.o gold.h bats.o bats.h armor.o armor.h hidden.o hidden.h
	$(CC) main.o room.o event.o game.o wumpus.o stalactites.o gold.o bats.o armor.o hidden.o -o $(EXE)

main.o: main.cpp
	$(CC) -c main.cpp

room.o: room.cpp
	$(CC) -c room.cpp

event.o: event.cpp
	$(CC) -c event.cpp

game.o: game.cpp
	$(CC) -c game.cpp

wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp

stalactites.o: stalactites.cpp
	$(CC) -c stalactites.cpp

gold.o: gold.cpp
	$(CC) -c gold.cpp

bats.o: bats.cpp
	$(CC) -c bats.cpp

armor.o: armor.cpp
	$(CC) -c armor.cpp

hidden.o: hidden.cpp
	$(CC) -c hidden.cpp
