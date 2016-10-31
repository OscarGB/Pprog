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
#include <string.h>
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
  	Game game; /*Game pointer*/
  	Command *command = NULL; /*Command pointer*/
  	FILE *f = NULL; /*Log file*/
  	int flag = 0; /*Flag if its on log mode*/
  	STATUS log; /*Variable for the creation of log file*/

	if (argc < 2){
	fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
	return 1;
	}
	/*Log mode*/
	if(argc == 4){
		if(strcmp(argv[2], "-l") == 0){
			f = fopen(argv[3], "w");
			if(f == NULL){
				fprintf(stderr, "Error initializing log file\n");
				return 1;
			}
			flag = 1;
		}
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
		 log = game_update(&game, command);
		 /*Log mode*/
		 if(flag == 1){
		 	switch (command_get_cmd(command)) {
			  case UNKNOWN:
			  	if(log == OK){
			  		fprintf(f, "UNKNOWN : OK\n");
			  	}
			  	else{
			  		fprintf(f, "UNKNOWN : ERROR\n");
			  	}
			  	break;
			  case QUIT:
			  	if(log == OK){
			  		fprintf(f, "QUIT : OK\n");
			  	}
			  	else{
			  		fprintf(f, "QUIT : ERROR\n");
			  	}
			  	break;
			  case NEXT:
			    if(log == OK){
			  		fprintf(f, "NEXT : OK\n");
			  	}
			  	else{
			  		fprintf(f,"NEXT : ERROR\n");
			  	}
			  	break;
			  case BACK:
			    if(log == OK){
			  		fprintf(f, "BACK : OK\n");
			  	}
			  	else{
			  		fprintf(f, "BACK : ERROR\n");
			  	}
			  	break;
			  case JUMP:
			    if(log == OK){
			  		fprintf(f, "JUMP : OK\n");
			  	}
			  	else{
			  		fprintf(f, "JUMP : ERROR\n");
			  	}
			  	break;
			  case PICK:
			    if(log == OK){
			  		fprintf(f, "PICK : OK\n");
			  	}
			  	else{
			  		fprintf(f, "PICK : ERROR\n");
			  	}
			  	break;
			  case DROP:
			    if(log == OK){
			  		fprintf(f, "DROP : OK\n");
			  	}
			  	else{
			  		fprintf(f, "DROP : ERROR\n");
			  	}
			  	break;
			  case ROLL:
			    if(log == OK){
			  		fprintf(f, "ROLL : OK\n");
			  	}
			  	else{
			  		fprintf(f, "ROLL : ERROR\n");
			  	}
			  	break;
			  case NO_CMD:
			  	fprintf(f, "NO_CMD\n");
			    break;
			  default: /* We must never arrive here*/
			    fprintf(f, "ERROR\n");
			  }
		 	}
		}
	game_destroy(&game);
	command_destroy(command);
	/*Log mode*/
	if(flag == 1){
		fclose(f);
	}
	return 0;
}
