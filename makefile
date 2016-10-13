	CFLAGS = -g -Wall -pedantic -ansi -I codigo/cabeceras

all: ocabas

ocabas: game_loop.o game.o space.o command.o game_reader.o player.o object.o
	gcc $(CFLAGS) -o ocabas game_loop.o game.o space.o command.o game_reader.o player.o object.o

command.o: codigo/command/command.c
	gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c
	gcc $(CFLAGS) -c codigo/game/game.c

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

clean:
	rm -f *.exe ocabas *.o *.tgz

dist:
	tar cvzf s1-cod_OcaBasicaIni-v2.0.tgz codigo/ makefile spaces.dat spaces2.dat
