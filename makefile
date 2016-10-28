CFLAGS = -g -Wall -pedantic -ansi

DEPS = codigo/command/command.h codigo/die/die.h ./game/game.h codigo/game_reader/game_reader.h codigo/object/object.h codigo/player/player.h codigo/set/set.h codigo/space/space.h codigo/generic/types.h

all: ocabas

debug: CFLAGS += -DDEBUG
debug: ocabas die_test set_test

die_test: die_test.o die.o 
	gcc $(CFLAGS) -o die_test die_test.o die.o

set_test: set_test.o set.o
	gcc $(CFLAGS) -o set_test set_test.o set.o

die_test.o: codigo/die/die_test.c $(DEPS)
	gcc $(CFLAGS) -c codigo/die/die_test.c

set_test.o: codigo/set/set_test.c $(DEPS)
	gcc $(CFLAGS) -c codigo/set/set_test.c

ocabas: game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o
	gcc $(CFLAGS) -o ocabas game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o

command.o: codigo/command/command.c $(DEPS)
	gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c $(DEPS)
	gcc $(CFLAGS) -c codigo/game/game.c

game_loop.o: codigo/game_loop.c $(DEPS)
	gcc $(CFLAGS) -c codigo/game_loop.c

space.o: codigo/space/space.c $(DEPS)
	gcc $(CFLAGS) -c codigo/space/space.c

game_reader.o: codigo/game_reader/game_reader.c $(DEPS)
	gcc $(CFLAGS) -c codigo/game_reader/game_reader.c

player.o: codigo/player/player.c $(DEPS)
	gcc $(CFLAGS) -c codigo/player/player.c

object.o: codigo/object/object.c $(DEPS)
	gcc $(CFLAGS) -c codigo/object/object.c

set.o: codigo/set/set.c $(DEPS)
	gcc $(CFLAGS) -c codigo/set/set.c

die.o: codigo/die/die.c $(DEPS)
	gcc $(CFLAGS) -c codigo/die/die.c

clean:
	rm -f *.exe ocabas *.o *.tgz *.log

dist:
	tar cvzf s1-cod_OcaBasicaIni-v2.1.tgz codigo/ makefile spaces.dat spaces2.dat
