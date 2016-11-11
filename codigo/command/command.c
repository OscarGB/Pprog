/**
 * @brief It implements the command interpreter
 * @file command.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 23/09/2016
 * @revision_history none
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

#define CMD_LENGHT 30

struct _Command{
	T_Command cmd; /*<!The command*/
	char symbol; /*<!A symbol for TAKE and DROP commands*/
};


/*
* @brief reads from keyboard in search of a valid command to execute
* it creates the command inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 23/09/2016
* @param command pointer
* @return OK if command is changed with user's input
*/

STATUS get_user_input(Command* command){
	char action[CMD_LENGHT]; /*The action written*/
	char input[CMD_LENGHT]; /*The real input*/
	char symbol; /*The character for TAKE and DROP*/
	char* toks = NULL; /*String for tokenization*/

	if(command == NULL){
		return ERROR;
	}
	if (fgets (input, WORD_SIZE, stdin) != NULL){
		toks = strtok(input, " \n");
		if(toks != NULL){/*If theres nothing written -> NO_CMD*/
			strcpy(action, toks);
			toks = strtok(NULL, " \n");
			if(toks != NULL){ /*If there is a symbol -> set the symbol to the introduced valor*/
				symbol = toks[0];
			}
			else{/*If there's not a symbol we set to E*/
				symbol = E;
				command->symbol = E;
			}

			#ifdef DEBUG
				printf("Leido: %s\n", input); /*Debug case*/
			#endif

			/*Detecting what command was written*/
			if (!strcmp(action, "q") || !strcmp(action, "quit")){
				command->cmd = QUIT;
			}
			else if (!strcmp(action, "n") || !strcmp(action, "next")){
				command->cmd = NEXT;
			}
			else if (!strcmp(action, "b") || !strcmp(action, "back")){
				command->cmd = BACK;
			}
			else if (!strcmp(action, "j") || !strcmp(action, "jump")){
				command->cmd = JUMP;
			}
			else if (!strcmp(action, "p") || !strcmp(action, "pick")){
				command->cmd = PICK;

				command->symbol = symbol;
			}
			else if (!strcmp(action, "d") || !strcmp(action, "drop")){
				command->cmd = DROP;

				command->symbol = symbol;
			}
			else if (!strcmp(action, "r") || !strcmp(action, "roll")){
				command->cmd = ROLL;
			}
			else if (!strcmp(action, "i") || !strcmp(action, "inspect")){
				command->cmd = INSPECT;

				command->symbol = symbol;
			}
			else if (!strcmp(action, "g") || !strcmp(action, "go")){
				command->cmd = GO;

				command->symbol = symbol;
			}
			else{
				command->cmd = UNKNOWN;
			}
		}
		else{
			command->cmd = NO_CMD;
		}
	}
	return OK;
}


/*
* @brief It creates a command, defining its atributes to UNKNOWN and ''
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param none
* @return pointer to the created command
*/

Command* command_create(){
	Command* newcom; /*The new command*/
	newcom = (Command *) malloc (sizeof(Command));
	if(!newcom){
		return NULL;
	}
	/*Default values*/
	newcom->cmd = UNKNOWN;
	newcom->symbol = 'E';
	return newcom;
}

/*
* @brief It destroys a command, freeing all the memory
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param pointer to command (to destroy)
* @return none
*/

void command_destroy(Command *com){
	if(!com){
		return;
	}
	free(com);
	return;
}


/*
* @brief It gives the value of the T_Command inside Command
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param command pointer
* @return T_Command (The T_Command inside the given Command)
*/

T_Command command_get_cmd(Command *com){
	if(!com){
		return UNKNOWN;
	}
	return com->cmd;
}


/*
* @brief It gives the value of the symbol inside Command
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param command pointer
* @return char (The symbol inside the given Command)
*/

char command_get_symbol(Command *com){
	if(!com){
		return UNKNOWN;
	}
	return com->symbol;
}
