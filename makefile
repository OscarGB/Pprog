#--------------------------------------------#
# Makefile v2.0                              #
# Author: Óscar Gómez Borzdynski             #
#--------------------------------------------#

DEPS = game command generic space set player object die game_reader link inventory test	#Nombre de las carpetas de los módulos
IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefijo de -I para la inclusión de las carpetas en la compilación

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags de compilación

ALL = ocabas 	#Ejecutables a generar si se llama a make
TEST = link_test die_test inventory_test#set_test link_test space_test	#Ejecutables a generar si se llama a make debug o make test
ALL_DEBUG = $(ALL) $(TEST)

all: $(ALL) #Genera únicamente el juego

test: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
test: $(TEST) #Crea todos los tests

debug: CFLAGS += -DDEBUG	#Se añade el flag -DDEBUG a la compilación
debug: $(ALL_DEBUG) #Crea los tests y el ejecutable del juego

die_test: die_test.o die.o 
	@echo "--->Creando el ejecutable die_test"
	@gcc $(CFLAGS) -o die_test die_test.o die.o

set_test: set_test.o set.o
	@echo "--->Creando el ejecutable set_test"
	@gcc $(CFLAGS) -o set_test set_test.o set.o

link_test: link_test.o link.o
	@echo "--->Creando el ejecutable link_test"
	@gcc $(CFLAGS) -o link_test link_test.o link.o

inventory_test: inventory_test.o inventory.o set.o
	@echo "--->Creando el ejecutable inventory_test"
	@gcc $(CFLAGS) -o inventory_test inventory_test.o inventory.o set.o

space_test: space_test.o space.o set.o
	@echo "--->Creando el ejecutable space_test"
	@gcc $(CFLAGS) -o space_test space_test.o space.o set.o

die_test.o: codigo/test/die_test.c 
	@echo "--->Generando die_test.o"
	@gcc $(CFLAGS) -c codigo/test/die_test.c

set_test.o: codigo/test/set_test.c 
	@echo "--->Generando set_test.o"
	@gcc $(CFLAGS) -c codigo/test/set_test.c

link_test.o: codigo/test/link_test.c
	@echo "--->Generando link_test.o"
	@gcc $(CFLAGS) -c codigo/test/link_test.c

inventory_test.o: codigo/test/inventory_test.c
	@echo "--->Generando inventory_test.o"
	@gcc $(CFLAGS) -c codigo/test/inventory_test.c

space_test.o: codigo/test/space_test.c
	@echo "--->Generando space_test.o"
	@gcc $(CFLAGS) -c codigo/test/space_test.c

ocabas: game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o link.o inventory.o
	@echo "--->Creando el ejecutable JuegoOcaPlus"
	@gcc $(CFLAGS) -o JuegoOcaPlus game_loop.o game.o space.o command.o game_reader.o player.o object.o set.o die.o link.o inventory.o

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

inventory.o: codigo/inventory/inventory.c
	@echo "--->Generandp inventory.o"
	@gcc $(CFLAGS) -c codigo/inventory/inventory.c

clean: #Comando de limpieza del directorio raiz
	@echo "--->Borrando todos los ejecutables y los ficheros de distribución, incluyendo los test y el log"
	@rm -rf *.exe  *.o *.tgz *.log $(ALL_DEBUG) *.out 

dist: #Comando de generación de un comprimido para la distribución del programa
	@echo "--->Creando tgz para la distribución del programa"
	@tar cvzf s1-cod_OcaBasicaIni-v3.0.tgz codigo/ informes_pruebas/ reuniones/ html/ makefile *.dat Doxyfile *.oca

doc: #Comando de generación de la documentación
	@echo "--->Generando documentación mediante Doxygen"
	@nohup doxygen Doxyfile
	@echo "--->Abriendo documentación"
	@firefox html/index.html
