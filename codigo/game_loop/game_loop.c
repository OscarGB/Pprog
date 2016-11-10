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
  	Game * game = NULL; /*Game pointer*/
  	Command *command = NULL; /*Command pointer*/
  	FILE *l = NULL; /*Log file*/
  	int flag = 0; /*Flag if its on log mode*/
  	STATUS log; /*Variable for the creation of log file*/
	int nvflag = 0; /*Variable for the no verbose mode*/

	if (argc < 2){
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}

	/*Log mode*/
	if(argc == 4){
		if(strcmp(argv[2], "-l") == 0){
			l = fopen(argv[3], "w");
			if(l == NULL){
				fprintf(stderr, "Error initializing log file\n");
				return 1;
			}
			flag = 1;
		}
	}

	game = game_init(game);
	if(!game){
		return ERROR;
	}


	if (game_init_from_file(game, argv[1]) == ERROR){
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}

	command = command_create();
	if(!command){
		fprintf(stderr, "Command couldnt be created\n");
		game_destroy(game);
	}
	while ((command_get_cmd(command) != QUIT) && !game_is_over(game)){
		 if (nvflag == 0){
		 	game_print_screen(game);
		 	/*get_file_input(command, file);*/
		 }
		 get_user_input(command);
		 log = game_update(game, command);
		 /*Log mode*/
		 if(flag == 1){
		 	switch (command_get_cmd(command)) {
			  case UNKNOWN:
			  	if(log == OK){
			  		fprintf(l, "UNKNOWN : OK\n");
			  	}
			  	else{
			  		fprintf(l, "UNKNOWN : ERROR\n");
			  	}
			  	break;
			  case QUIT:
			  	if(log == OK){
			  		fprintf(l, "QUIT : OK\n");
			  	}
			  	else{
			  		fprintf(l, "QUIT : ERROR\n");
			  	}
			  	break;
			  case NEXT:
			    if(log == OK){
			  		fprintf(l, "NEXT : OK\n");
			  	}
			  	else{
			  		fprintf(l,"NEXT : ERROR\n");
			  	}
			  	break;
			  case BACK:
			    if(log == OK){
			  		fprintf(l, "BACK : OK\n");
			  	}
			  	else{
			  		fprintf(l, "BACK : ERROR\n");
			  	}
			  	break;
			  case JUMP:
			    if(log == OK){
			  		fprintf(l, "JUMP : OK\n");
			  	}
			  	else{
			  		fprintf(l, "JUMP : ERROR\n");
			  	}
			  	break;
			  case PICK:
			    if(log == OK){
			  		fprintf(l, "PICK : OK\n");
			  	}
			  	else{
			  		fprintf(l, "PICK : ERROR\n");
			  	}
			  	break;
			  case DROP:
			    if(log == OK){
			  		fprintf(l, "DROP : OK\n");
			  	}
			  	else{
			  		fprintf(l, "DROP : ERROR\n");
			  	}
			  	break;
			  case ROLL:
			    if(log == OK){
			  		fprintf(l, "ROLL : OK\n");
			  	}
			  	else{
			  		fprintf(l, "ROLL : ERROR\n");
			  	}
			  	break;
			  case INSPECT:
			    if(log == OK){
			  		fprintf(l, "INSPECT : OK\n");
			  	}
			  	else{
			  		fprintf(l, "INSPECT : ERROR\n");
			  	}
			  	break;
			  case NO_CMD:
			  	fprintf(l, "NO_CMD\n");
			    break;
			  default: /* We must never arrive here*/
			    fprintf(l, "ERROR\n");
			  }
		 	}
		}
	game_destroy(game);
	command_destroy(command);
	/*Log mode*/
	if(flag == 1){
		fclose(l);
	}
	return 0;
}
