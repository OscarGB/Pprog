#--------------------------------------------#
# Makefile v2.0                              #
# Author: Óscar Gómez Borzdynski             #
#--------------------------------------------#

DEPS = game command generic space set player object die game_reader link inventory test	#Nombre de las carpetas de los módulos
IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefijo de -I para la inclusión de las carpetas en la compilación

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags de compilación

ALL = JuegoOcaPlus 	#Ejecutables a generar si se llama a make
TEST = link_test die_test player_test inventory_test space_test set_test	#Ejecutables a generar si se llama a make debug o make test
ALL_DEBUG = $(ALL) $(TEST)

all: $(ALL) #Genera únicamente el juego

test: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
test: $(TEST) #Crea todos los tests

debug: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
debug: $(ALL_DEBUG) #Crea los tests y el ejecutable del juego

die_test: die_test.o die.o 
	@echo "--->Creating executable die_test"
	@gcc $(CFLAGS) -o die_test die_test.o die.o

player_test: player_test.o player.o inventory.o set.o
	@echo "--->Creating executable player_test"
	@gcc $(CFLAGS) -o player_test player_test.o player.o inventory.o set.o

set_test: set_test.o set.o
	@echo "--->Creating executable set_test"
	@gcc $(CFLAGS) -o set_test set_test.o set.o

link_test: link_test.o link.o
	@echo "--->Creating executable link_test"
	@gcc $(CFLAGS) -o link_test link_test.o link.o

inventory_test: inventory_test.o inventory.o set.o
	@echo "--->Creating executable inventory_test"
	@gcc $(CFLAGS) -o inventory_test inventory_test.o inventory.o set.o

space_test: space_test.o space.o set.o
	@echo "--->Creating executable space_test"
	@gcc $(CFLAGS) -o space_test space_test.o space.o set.o

die_test.o: codigo/test/die_test.c 
	@echo "--->Generating die_test.o"
	@gcc $(CFLAGS) -c codigo/test/die_test.c

player_test.o: codigo/test/player_test.c 
	@echo "--->Generating player_test.o"
	@gcc $(CFLAGS) -c codigo/test/player_test.c

set_test.o: codigo/test/set_test.c 
	@echo "--->Generating set_test.o"
	@gcc $(CFLAGS) -c codigo/test/set_test.c

link_test.o: codigo/test/link_test.c
	@echo "--->Generating link_test.o"
	@gcc $(CFLAGS) -c codigo/test/link_test.c

inventory_test.o: codigo/test/inventory_test.c
	@echo "--->Generating inventory_test.o"
	@gcc $(CFLAGS) -c codigo/test/inventory_test.c

space_test.o: codigo/test/space_test.c
	@echo "--->Generating space_test.o"
	@gcc $(CFLAGS) -c codigo/test/space_test.c

JuegoOcaPlus: game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o link.o inventory.o
	@echo "--->Creating executable JuegoOcaPlus"
	@gcc $(CFLAGS) -o JuegoOcaPlus game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o link.o inventory.o

command.o: codigo/command/command.c 
	@echo "--->Generating command.o"
	@gcc $(CFLAGS) -c codigo/command/command.c
 
game.o: codigo/game/game.c 
	@echo "--->Generating game.o"
	@gcc $(CFLAGS) -c codigo/game/game.c

game_loop.o: codigo/game_loop/game_loop.c 
	@echo "--->Generating game_loop.o"
	@gcc $(CFLAGS) -c codigo/game_loop/game_loop.c

space.o: codigo/space/space.c 
	@echo "--->Generating space.o"
	@gcc $(CFLAGS) -c codigo/space/space.c

game_reader.o: codigo/game_reader/game_reader.c 
	@echo "--->Generating game_reader.o"
	@gcc $(CFLAGS) -c codigo/game_reader/game_reader.c

player.o: codigo/player/player.c 
	@echo "--->Generating player.o"
	@gcc $(CFLAGS) -c codigo/player/player.c

object.o: codigo/object/object.c 
	@echo "--->Generating object.o"
	@gcc $(CFLAGS) -c codigo/object/object.c

set.o: codigo/set/set.c 
	@echo "--->Generating set.o"
	@gcc $(CFLAGS) -c codigo/set/set.c

die.o: codigo/die/die.c
	@echo "--->Generating die.o"
	@gcc $(CFLAGS) -c codigo/die/die.c

link.o: codigo/link/link.c
	@echo "--->Generating link.o"
	@gcc $(CFLAGS) -c codigo/link/link.c

inventory.o: codigo/inventory/inventory.c
	@echo "--->Generating inventory.o"
	@gcc $(CFLAGS) -c codigo/inventory/inventory.c

clean: #Comando de limpieza del directorio raiz
	@echo "--->Deleting all executables, distributing  files, tests and logs"
	@rm -rf *.exe  *.o *.tgz *.log $(ALL_DEBUG) *.out 

dist: #Comando de generación de un comprimido para la distribución del programa
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile
	@echo "--->Creating tgz for program's distribution"
	@tar cvzf s1-cod_OcaBasicaIni-v3.0.tgz codigo/ informes_pruebas/ reuniones/ html/ makefile *.dat Doxyfile *.oca test_games/

doc: #Comando de generación de la documentación
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile

opendoc: #Comando para abrir la documentación
	@echo "--->Opening documentation"
	@firefox html/index.html
