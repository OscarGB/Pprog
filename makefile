	CFLAGS = -g -Wall -pedantic -ansi -I codigo/cabeceras 

all: ocabas

debug: CFLAGS += -DDEBUG
debug: ocabas die_test set_test

die_test: die_test.o die.o
	gcc $(CFLAGS) -o die_test die_test.o die.o

set_test: set_test.o set.o
	gcc $(CFLAGS) -o set_test set_test.o set.o

die_test.o: codigo/die/die_test.c
	gcc $(CFLAGS) -c codigo/die/die_test.c

set_test.o: codigo/set/set_test.c
	gcc $(CFLAGS) -c codigo/set/set_test.c

ocabas: game_loop.o game.o callbacks.o space.o command.o game_reader.o player.o object.o set.o die.o
	gcc $(CFLAGS) -o ocabas game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o

command.o: codigo/command/command.c
	gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c
	gcc $(CFLAGS) -c codigo/game/game.c

callbacks.o: codigo/game/callbacks.c
	gcc $(CFLAGS) -c codigo/game/callbacks.c

game_loop.o: codigo/game_loop.c 
	gcc $(CFLAGS) -c codigo/game_loop.c

space.o: codigo/space/space.c
	gcc $(CFLAGS) -c codigo/space/space.c

game_reader.o: codigo/game_reader/game_reader.c
	gcc $(CFLAGS) -c codigo/game_reader/game_reader.c

player.o: codigo/player/player.c
	gcc $(CFLAGS) -c codigo/player/player.c

object.o: codigo/object/object.c
	gcc $(CFLAGS) -c codigo/object/object.c

set.o: codigo/set/set.c
	gcc $(CFLAGS) -c codigo/set/set.c

die.o: codigo/die/die.c
	gcc $(CFLAGS) -c codigo/die/die.c

clean:
	rm -f *.exe ocabas *.o *.tgz

dist:
	tar cvzf s1-cod_OcaBasicaIni-v2.0.tgz codigo/ makefile spaces.dat spaces2.dat
