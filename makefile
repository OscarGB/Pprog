DEPS = game command generic space set player object die game_reader link	#Nombre de las carpetas de los módulos
IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefijo de -I para la inclusión de las carpetas en la compilación

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags de compilación

ALL = ocabas 	#Ejecutables a generar si se llama a make

ALL_DEBUG = $(ALL) die_test set_test	#Ejecutables a generar si se llama a make debug

all: $(ALL)

debug: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
debug: $(ALL_DEBUG)

die_test: die_test.o die.o 
	@echo "--->Creando el ejecutable die_test"
	@gcc $(CFLAGS) -o die_test die_test.o die.o

set_test: set_test.o set.o
	@echo "--->Creando el ejecutable set_test"
	@gcc $(CFLAGS) -o set_test set_test.o set.o

die_test.o: codigo/die/die_test.c 
	@echo "--->Generando die_test.o"
	@gcc $(CFLAGS) -c codigo/die/die_test.c

set_test.o: codigo/set/set_test.c 
	@echo "--->Generando set_test.o"
	@gcc $(CFLAGS) -c codigo/set/set_test.c

ocabas: game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o
	@echo "--->Creando el ejecutable ocabas"
	@gcc $(CFLAGS) -o ocabas game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o

command.o: codigo/command/command.c 
	@echo "--->Generando command.o"
	@gcc $(CFLAGS) -c codigo/command/command.c

game.o: codigo/game/game.c 
	@echo "--->Generando game.o"
	@gcc $(CFLAGS) -c codigo/game/game.c

game_loop.o: codigo/game_loop/game_loop.c 
	@echo "--->Generando game_loop.o"
	@gcc $(CFLAGS) -c codigo/game_loop/game_loop.c

space.o: codigo/space/space.c 
	@echo "--->Generando space.o"
	@gcc $(CFLAGS) -c codigo/space/space.c

game_reader.o: codigo/game_reader/game_reader.c 
	@echo "--->Generando game_reader.o"
	@gcc $(CFLAGS) -c codigo/game_reader/game_reader.c

player.o: codigo/player/player.c 
	@echo "--->Generando player.o"
	@gcc $(CFLAGS) -c codigo/player/player.c

object.o: codigo/object/object.c 
	@echo "--->Generando object.o"
	@gcc $(CFLAGS) -c codigo/object/object.c

set.o: codigo/set/set.c 
	@echo "--->Generando set.o"
	@gcc $(CFLAGS) -c codigo/set/set.c

die.o: codigo/die/die.c
	@echo "--->Generando die.o"
	@gcc $(CFLAGS) -c codigo/die/die.c

link.o: codigo/link/link.c
	@echo "--->Generando link.o"
	@gcc $(CFLAGS) -c codigo/link/link.c

clean:
	@echo "--->Borrando todos los ejecutables, incluyendo los test y el log"
	@rm -f *.exe  *.o *.tgz *.log $(ALL_DEBUG)

dist:
	@echo "--->Creando tgz para la distribución del programa"
	@tar cvzf s1-cod_OcaBasicaIni-v3.0.tgz codigo/ makefile *.dat