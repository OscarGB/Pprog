/* ===================================================================
File: game_loop.c

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the game loop

Revision history: none

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "command.h"

/* --------------------------------------------------------------------
Function: main()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: function main for the program, runs the game.

Input: 	int argc (number of arguments)
		char *[argv] (number of arguments)

Output: int 1 if ERROR, 0 if OK

------------------------------------------------------------------- */

int main(int argc, char *argv[]){
  	Game game;
  	Command *command = NULL;

	if (argc < 2){
	fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
	return 1;
	}
	if (game_init_from_file(&game, argv[1]) == ERROR){
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}

	command = command_create();
	if(!command){
		fprintf(stderr, "Command couldnt be created\n");
	}
	while ((command_get_cmd(command) != QUIT) && !game_is_over(&game)){
		 game_print_screen(&game);
		 get_user_input(command);
		 game_update(&game, command);
		}
	game_destroy(&game);
	command_destroy(command);
	return 0;
}
