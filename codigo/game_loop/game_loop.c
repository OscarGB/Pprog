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
#include <unistd.h>
#include <dirent.h>
#include "game.h"
#include "command.h"
#include "types.h"
#include "graphic_engine.h"
#include "dialogue.h"
#include "game_rules.h"


/**
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
		if(strcmp(argv[2], "NO_RULES") == 0)
			return position;
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
		case HELP:
			if(log == OK){
				fprintf(l, "Help : OK\n");
			}
			else{
				fprintf(l, "Help : ERROR\n");
			}
			break;
		case SAVE:
			if(log == OK){
				fprintf(l, "Save %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Save %s : ERROR\n", command_get_symbol(command));
			}
			break;
		case LOAD:
			if(log == OK){
				fprintf(l, "Load %s : OK\n", command_get_symbol(command));
			}
			else{
				fprintf(l, "Load %s : ERROR\n", command_get_symbol(command));
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

/**
* @brief load function
* @author Óscar Gómez
* @date 22/12/2016
* @param Command* cmd
* @param Dialogue* dia
* @param Graphics* gra
* @return OK
*/
STATUS load(Command* cmd, Dialogue* dia, Graphics* gra){

	int i=0;
	DIR *dir;
	struct dirent *ent;
	char savegames[256]="";
	char *symbol = NULL;

	if(!dia || !gra || !cmd)
		return ERROR;

	/*This if only shows available files for load*/
	symbol = command_get_symbol(cmd);
	if(!strcmp(symbol, "show")){
		if ((dir = opendir ("Saves")) != NULL) {
		  while ((ent = readdir (dir)) != NULL && i<=7) {
			if ( !strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") ){
    			 continue;
			} else {
		    		strcat(savegames, ent->d_name);
		    		strcat(savegames, "\n");
		    		i++;
			}
		 }
		  if(!strcmp(savegames, "")){
			dialogue_load_show(gra, dia, "No saved files\n", OK);
		  }else{
		  	dialogue_load_show(gra, dia, savegames, OK);
		  }
		  closedir (dir);
		  return OK;
		} else{
			dialogue_load_show(gra, dia, savegames, ERROR);
		  	return ERROR;
		}
	}
	return OK;
}

/**
* @brief function main for the program, runs the game.
* it creates the command inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 23/09/2016
* @param int argc (number of arguments)
* @param char *[argv] (number of arguments)
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
	char input[CMD_LENGHT];
	char path[256];
	int rflag = 1; /*Flag for game_rules deactivation*/
	int i;

	file_pos = check_flags(argc, argv, &flag, &nvflag);
	
	for(i=2; i<argc; i++){
		if(strcmp(argv[i], "NO_RULES") == 0)
			rflag = 0;
	}	

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

	gra = graphics_create(nvflag);
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
	dialogue_start_game(gra);
	system("aplay -q Music/StartTune.wav");


	while ((command_get_cmd(command) != QUIT) && !game_is_over(game)){
		if(nvflag != 1){ 
			game_print_screen(game, gra);
			scan_from_screen(gra, command);
		}
		if(nvflag == 1){
			fgets(input, CMD_LENGHT, stdin);
			get_user_input(command, input);
		}
		if(command_get_cmd(command) != LOAD){
			log = game_update(game, command, dialogue, gra);
		}
		else{
			if(strcmp(command_get_symbol(command), "show") == 0){
				log = load(command, dialogue, gra);
			}
			else{
				strcpy(path, "Saves/");
				strcat(path, command_get_symbol(command));
				strcat(path, ".s");

				if(access(path, F_OK) != -1){
		    	game_destroy(game);      

					game = game_init(game);

					if(game){
						log = game_init_from_file(game, path);
						dialogue_load(gra, dialogue, command_get_symbol(command), log);
					}else{

						dialogue_load(gra, dialogue, command_get_symbol(command), ERROR);

						log = ERROR;
					}
	  		}
	  		else{
	  			dialogue_load(gra, dialogue, command_get_symbol(command), ERROR);

					log = ERROR;
	  		}
			}
		}
		/*Log mode*/
		if(flag == 1){
			print_log(command, log, l); 	
		}
		if(rflag == 1 && game_get_endgame(game)!=TRUE && command_get_cmd(command)!=QUIT)
			pick_aleat_function(game, gra);
	}
	graphics_destroy(gra);
	game_destroy(game);
	command_destroy(command);
	dialogue_destroy(dialogue);
	/*Log mode*/
	if(flag == 1){
		fclose(l);
	}
	return 0;
}
