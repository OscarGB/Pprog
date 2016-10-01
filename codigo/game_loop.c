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
  	T_Command command = NO_CMD;
	if (argc < 2){
	fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
	return 1;
	}
	if (game_init_from_file(&game, argv[1]) == ERROR){
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}
	while ((command != QUIT) && !game_is_over(&game)){
		 game_print_screen(&game);
		 command = get_user_input();
		 game_update(&game, command);
		}
	game_destroy(&game);
	return 0;
}
