DEPS = game command generic space set player object die game_reader	#Nombre de las carpetas de los módulos
IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefijo de -I para la inclusión de las carpetas en la compilación

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags de compilación

ALL = ocabas 	#Ejecutables a generar si se llama a make

ALL_DEBUG = $(ALL) die_test set_test	#Ejecutables a generar si se llama a make debug

all: $(ALL)

debug: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
debug: $(ALL_DEBUG)

die_test: die_test.o die.o 
	gcc $(CFLAGS) -o die_test die_test.o die.o

set_test: set_test.o set.o
	gcc $(CFLAGS) -o set_test set_test.o set.o

die_test.o: codigo/die/die_test.c 
	gcc $(CFLAGS) -c codigo/die/die_test.c

set_test.o: codigo/set/set_test.c 
	gcc $(CFLAGS) -c codigo/set/set_test.c

ocabas: game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o
	gcc $(CFLAGS) -o ocabas game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o

command.o: codigo/command/command.c 
	gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c 
	gcc $(CFLAGS) -c codigo/game/game.c

game_loop.o: codigo/game_loop/game_loop.c 
	gcc $(CFLAGS) -c codigo/game_loop/game_loop.c

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
	rm -f *.exe  *.o *.tgz *.log $(ALL_DEBUG)	#Borrado de todos los ejecutables, incluyendo los test

dist:
	tar cvzf s1-cod_OcaBasicaIni-v2.1.tgz codigo/ makefile *.dat