/**
 * @brief It defines the game loop
 * @file game_loop.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 23/09/2016
 * @revision_history none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "command.h"
#include "types.h"
#include "graphics.h"
#include "dialogue.h"


/*
* @brief function for checking flags.
* checks the arguments and set flags
* @author José Ignacio Gómez
* @date 18/11/2016
* @param int argc (number of arguments)
* @param char **[argv] (number of arguments)
* @param int *flag (log flag)
* @param int *nvflag (no verbose flag)
* @return int -1 if ERROR, the position of the log file if OK
*/
int check_flags(int argc, char **argv, int *flag, int *nvflag) {
	int position = 0;

	if (argc < 2){
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return -1;
	}

	/*Log mode*/
	if(argc >= 3){
		if(strcmp(argv[2], "-l") == 0){
			if(argc >= 4 && argv[3][0] != '-'){	
				*flag = 1; /*Activating log mode*/

				if(argc == 5){
					if(strcmp(argv[4], "-nv") == 0){
						*nvflag = 1; /*Activating no verbose mode*/
					}
					else {
						printf("Use: %s <game_data_file> -l <log_file> [-nv]\n", argv[0]);
						return -1;
					}

				}
				position = 3; /*Number of the argument of the log*/
			}
			else {
				printf("Use: %s <game_data_file> -l <log_file> [-nv]\n", argv[0]);
				return -1;
			}
		}

		else if(strcmp(argv[2], "-nv") == 0){
			*nvflag = 1;

			if(argc == 5){
				if(strcmp(argv[3], "-l") == 0){
					if(argv[4][0] != '-'){
						*flag = 1;
						position = 4; /*Number of the argument of the log file*/
					}
					else {
						printf("Use: %s <game_data_file> -nv [-l <log_file>]\n", argv[0]);
						return -1;
					}

				}

				else {
					printf("Use: %s <game_data_file> -nv [-l <log_file>]\n", argv[0]);
					return -1;
				}
			}
			else if(argc == 4){
				printf("Use: %s <game_data_file> -nv [-l <log_file>]\n", argv[0]);
				return -1;
			}
		}

		else {
			printf("Use: %s <game_data_file> [-nv] [ -l <log_file> ]\n", argv[0]);
			return -1;
		}
	}

	return position;
}

/**
* @brief Prints the file for the log
* @author Óscar Gómez
* @date 25/11/2016
* @param Command* command (The command itself)
* @param STATUS log (The status if the command was succesfully executed)
* @param FILE* l (The file where it's going to print)
* @return void
*/

void print_log(Command* command, STATUS log, FILE* l){
	if(!l || !command){
		return;
	}
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
				fprintf(l, "Quit : OK\n");
			}
			else{
				fprintf(l, "Quit : ERROR\n");
			}
			break;
		case GO:
			if(log == OK){
				fprintf(l, "Go %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l,"Go %s : ERROR\n", command_get_symbol(command));
			}
			break;
		
		case PICK:
			if(log == OK){
				fprintf(l, "Pick %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Pick %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case DROP:
			if(log == OK){
				fprintf(l, "Drop %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Drop %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case ROLL:
			if(log == OK){
				fprintf(l, "Roll : OK\n");
			}
			else{
				fprintf(l, "Roll : ERROR\n");
			}
			break;
		case INSPECT:
			if(log == OK){
				fprintf(l, "Inspect %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Inspect %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case TURNON:
			if(log == OK){
				fprintf(l, "Turn on %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Turn on %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case TURNOFF:
			if(log == OK){
				fprintf(l, "Turn off %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Turn off %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case OPEN:
			if(log == OK){
				fprintf(l, "Open %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Open %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case NO_CMD:
			fprintf(l, "NO_CMD\n");
			break;
		default: /* We must never arrive here*/
		    fprintf(l, "ERROR\n");
	}
	return;
}

/*
* @brief function main for the program, runs the game.
* it creates the command inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 23/09/2016
* @param int argc (number of arguments)
         char *[argv] (number of arguments)
* @return int 1 if ERROR, 0 if OK
*/
int main(int argc, char *argv[]){
	Graphics* gra = NULL;
  	Game * game = NULL; /*Game pointer*/
  	Command *command = NULL; /*Command pointer*/
  	Dialogue * dialogue = NULL; /*Dialogue pointer*/
  	FILE *l = NULL; /*Log file*/
  	int flag = 0; /*Flag if its on log mode*/
  	STATUS log; /*Variable for the creation of log file*/
  	int nvflag = 0; /*Variable for the -nv flag*/
	int file_pos = 0; /*In case we use a log file, this is its argument-position*/

	file_pos = check_flags(argc, argv, &flag, &nvflag);
	if(file_pos == -1){
		return -1;
	}

	if(flag == 1){
		l = fopen(argv[file_pos], "w");
		if(!l){
			return -1;
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
		fprintf(stderr, "Command couldn't be created\n");
		game_destroy(game);
		return 1;
	}

	gra = graphics_create();
	if(!gra){
		fprintf(stderr, "Graphics couldn't be created\n");
		game_destroy(game);
		command_destroy(command);
		return 1;
	}

	dialogue = dialogue_create(command);
	if(!dialogue){
		fprintf(stderr, "Dialogue couldn't be created\n");
		game_destroy(game);
		command_destroy(command);
		graphics_destroy(gra);
		return 1;
	}

	while ((command_get_cmd(command) != QUIT) && !game_is_over(game)){
		if(nvflag != 1){ 
			game_print_screen(game, gra);
		}
		scan_from_screen(gra, command);
		log = game_update(game, command, dialogue, gra);
		/*Log mode*/
		if(flag == 1){
			print_log(command, log, l); 	
		}
	}
	graphics_destroy(gra);
	game_destroy(game);
	command_destroy(command);
	/*Log mode*/
	if(flag == 1){
		fclose(l);
	}
	return 0;
}
