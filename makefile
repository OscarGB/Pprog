CFLAGS = -g -Wall -pedantic -ansi

all: oca clean_o

oca: game_loop.o game.o space.o command.o
	gcc $(CFLAGS) -o oca game_loop.o game.o space.o command.o

command.o: command.c command.h
	gcc $(CFLAGS) -c command.c

game.o: game.c game.h command.h space.h
	gcc $(CFLAGS) -c game.c

game_loop.o: game_loop.c game.h command.h space.h
	gcc $(CFLAGS) -c game_loop.c

space.o: space.c space.h types.h
	gcc $(CFLAGS) -c space.c

clean_o:
	rm -f *.o


clean:
	rm -f  *.exe oca