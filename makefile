CFLAGS = -g -Wall -pedantic -ansi

all: oca 

oca: game_loop.o game.o space.o command.o
	gcc $(CFLAGS) -o oca game_loop.o game.o space.o command.o

command.o: codigo/command/command.c codigo/command/command.h
	gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c codigo/game/game.h codigo/command/command.h codigo/space/space.h
	gcc $(CFLAGS) -c codigo/game/game.c

game_loop.o: codigo/game_loop.c codigo/game/game.h codigo/command/command.h codigo/space/space.h
	gcc $(CFLAGS) -c codigo/game_loop.c

space.o: codigo/space/space.c codigo/space/space.h codigo/types.h
	gcc $(CFLAGS) -c codigo/space/space.c

clean:
	rm -f  *.exe oca *.o