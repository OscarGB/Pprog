#--------------------------------------------#
# Makefile v2.0                              #
# Author: Óscar Gómez Borzdynski             #
#--------------------------------------------#


DEPS = game command generic space set player object die game_management link inventory test graphics game_rules dialogue	#Name of the module's folders

IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefix -I for the compilation with headers

NCURSES = -lncurses

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags for standard compilation

ALL = JuegoOcaPlus 	#Executables to make with a make call
TEST = object_test link_test die_test player_test inventory_test space_test set_test graphics_test	#Executables to make with make test or make debug
ALL_DEBUG = $(ALL) $(TEST) #Executables to make with make debug

all: $(ALL) #Generates only the main game

test: CFLAGS += -DDEBUG	#Adition of DEBUG macro
test: $(TEST) #Generates the tests

nocolors: CFLAGS += -DNO_COLORS	#Adition of NO_COLORS macro for execution without colors
nocolors: $(ALL_DEBUG) #Generates the tests and the main game without colors

debug: CFLAGS += -DDEBUG	#Adition of DEBUG macro
debug: $(ALL_DEBUG) #Generates the tests and the main game

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

object_test: object_test.o object.o
	@echo "--->Creating executable object_test"
	@gcc $(CFLAGS) -o object_test object_test.o object.o

inventory_test: inventory_test.o inventory.o set.o
	@echo "--->Creating executable inventory_test"
	@gcc $(CFLAGS) -o inventory_test inventory_test.o inventory.o set.o

space_test: space_test.o space.o set.o
	@echo "--->Creating executable space_test"
	@gcc $(CFLAGS) -o space_test space_test.o space.o set.o

graphics_test: graphics_test.o graphics.o command.o
	@echo "--->Creating executable graphics_test"
	@gcc $(CFLAGS) -o graphics_test graphics_test.o graphics.o command.o $(NCURSES)

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

object_test.o: codigo/test/object_test.c
	@echo "--->Generating object_test.o"
	@gcc $(CFLAGS) -c codigo/test/object_test.c

inventory_test.o: codigo/test/inventory_test.c
	@echo "--->Generating inventory_test.o"
	@gcc $(CFLAGS) -c codigo/test/inventory_test.c

space_test.o: codigo/test/space_test.c
	@echo "--->Generating space_test.o"
	@gcc $(CFLAGS) -c codigo/test/space_test.c

graphics_test.o: codigo/test/graphics_test.c
	@echo "--->Generating graphics_test.o"
	@gcc $(CFLAGS) -c codigo/test/graphics_test.c $(NCURSES)

JuegoOcaPlus: game_loop.o dialogue.o game_rules.o graphics.o game.o space.o command.o game_management.o player.o object.o set.o die.o link.o inventory.o
	@echo "--->Creating executable JuegoOcaPlus"
	@gcc $(CFLAGS) -o JuegoOcaPlus game_loop.o dialogue.o game_rules.o graphics.o game.o space.o command.o game_management.o player.o object.o set.o die.o link.o inventory.o $(NCURSES)

graphics.o: codigo/graphics/graphics.c
	@echo "--->Generating graphics.o"
	@gcc $(CFLAGS) -c codigo/graphics/graphics.c $(NCURSES)

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

game_management.o: codigo/game_management/game_management.c 
	@echo "--->Generating game_management.o"
	@gcc $(CFLAGS) -c codigo/game_management/game_management.c

dialogue.o: codigo/dialogue/dialogue.c
	@echo "--->Generating dialogue.o"
	@gcc $(CFLAGS) -c codigo/dialogue/dialogue.c

game_rules.o: codigo/game_rules/game_rules.c
	@echo "--->Generating game_rules.o"
	@gcc $(CFLAGS) -c codigo/game_rules/game_rules.c

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

clean: #Command to clean the root
	@echo "--->Deleting all executables, distributing  files, tests and logs"
	@rm -rf *.exe  *.o *.tgz *.log $(ALL_DEBUG) *.out 

dist: #Command to make the distributable file
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile
	@echo "--->Creating tgz for program's distribution"
	@tar cvzf s1-cod_OcaBasicaIni-v3.0.tgz codigo/ informes_pruebas/ comentarios.txt reuniones/ html/ makefile *.dat Doxyfile *.oca test_games/

doc: #Command to generate the documentation
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile

opendoc: #Command to open the documentation
	@echo "--->Opening documentation"
	@firefox html/index.html
