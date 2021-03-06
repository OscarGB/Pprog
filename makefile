#--------------------------------------------#
# Makefile v2.0                              #
# Author: Óscar Gómez Borzdynski             #
#--------------------------------------------#


DEPS = game command generic space set player object die game_management link inventory test graphic_engine game_rules dialogue	#Name of the module's folders

IDEPS = $(addprefix -Icodigo/, $(DEPS))	#Prefix -I for the compilation with headers

NCURSES = -lncurses

CFLAGS = -g -Wall -pedantic -ansi $(IDEPS)	#Flags for standard compilation

ALL = JuegoConv 	#Executables to make with a make call
TEST = object_test link_test die_test player_test inventory_test space_test set_test graphic_engine_test dialogue_test game_rules_test game_management_test	#Executables to make with make test or make debug
ALL_DEBUG = $(ALL) $(TEST) #Executables to make with make debug

all: $(ALL) #Generates only the main game

test: CFLAGS += -DDEBUG	#Adition of DEBUG macro
test: $(TEST) #Generates the tests

nocolors: CFLAGS += -DNO_COLORS	#Adition of NO_COLORS macro for execution without colors
nocolors: $(ALL_DEBUG) #Generates the tests and the main game without colors

debug: CFLAGS += -DDEBUG	#Adition of DEBUG macro
debug: $(ALL_DEBUG) #Generates the tests and the main game

game_rules_test: game_rules_test.o game_rules.o game.o space.o player.o object.o link.o inventory.o set.o command.o dialogue.o graphic_engine.o game_management.o die.o
	@echo "--->Creating executable game_rules_test"
	@gcc $(CFLAGS) -o game_rules_test game_rules_test.o game_rules.o game.o space.o player.o object.o link.o inventory.o set.o command.o dialogue.o graphic_engine.o game_management.o die.o $(NCURSES)

game_management_test: game_management_test.o game_management.o inventory.o set.o game.o space.o player.o object.o link.o command.o dialogue.o graphic_engine.o die.o
	@echo "--->Creating executable game_management_test"
	@gcc $(CFLAGS) -o game_management_test game_management_test.o game_management.o inventory.o set.o game.o space.o player.o object.o link.o command.o dialogue.o graphic_engine.o die.o $(NCURSES)

dialogue_test: dialogue_test.o dialogue.o
	@echo "--->Creating executable dialogue_test"
	@gcc $(CFLAGS) -o dialogue_test dialogue_test.o dialogue.o command.o graphic_engine.o $(NCURSES)

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

graphic_engine_test: graphic_engine_test.o graphic_engine.o command.o
	@echo "--->Creating executable graphic_engine_test"
	@gcc $(CFLAGS) -o graphic_engine_test graphic_engine_test.o graphic_engine.o command.o $(NCURSES)

dialogue_test.o: codigo/test/dialogue_test.c 
	@echo "--->Generating dialogue_test.o"
	@gcc $(CFLAGS) -c codigo/test/dialogue_test.c $(NCURSES)

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

graphic_engine_test.o: codigo/test/graphic_engine_test.c
	@echo "--->Generating graphic_engine_test.o"
	@gcc $(CFLAGS) -c codigo/test/graphic_engine_test.c $(NCURSES)

game_management_test.o: codigo/test/game_management_test.c
	@echo "--->Generating game_management_test.o"
	@gcc $(CFLAGS) -c codigo/test/game_management_test.c

game_rules_test.o: codigo/test/game_rules_test.c
	@echo "--->Generating game_rules_test.o"
	@gcc $(CFLAGS) -c codigo/test/game_rules_test.c $(NCURSES)

JuegoConv: game_loop.o dialogue.o game_rules.o graphic_engine.o game.o space.o command.o game_management.o player.o object.o set.o die.o link.o inventory.o
	@echo "--->Creating executable JuegoConv"
	@gcc $(CFLAGS) -o JuegoConv game_loop.o dialogue.o game_rules.o graphic_engine.o game.o space.o command.o game_management.o player.o object.o set.o die.o link.o inventory.o $(NCURSES)

graphic_engine.o: codigo/graphic_engine/graphic_engine.c
	@echo "--->Generating graphic_engine.o"
	@gcc $(CFLAGS) -c codigo/graphic_engine/graphic_engine.c $(NCURSES)

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
	@echo "--->Deleting all executables, distributing  files, tests, saved games and logs"
	@rm -rf *.exe  *.o *.tgz *.log $(ALL_DEBUG) *.out Saves/*

dist: #Command to make the distributable file
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile
	@echo "--->Creating tgz for program's distribution"
	@tar cvzf s1-cod_JuegoConv-v4.0.tgz codigo/ informes_pruebas/ guia_juego/ Saves/ script.sh comentarios.txt reuniones/ html/ makefile *.dat Doxyfile Music/

doc: #Command to generate the documentation
	@echo "--->Generating documentation with Doxygen"
	@nohup doxygen Doxyfile

opendoc: #Command to open the documentation
	@echo "--->Opening documentation"
	@firefox html/index.html
