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

struct _Command{
	T_Command cmd; /*!<The command*/
	char symbol[50]; /*!<A symbol for TAKE and DROP and INSPECT and TURN commands*/
};/*!<Command structure*/


/*
* @brief reads from keyboard in search of a valid command to execute
* it creates the command inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 23/09/2016
* @param command pointer
* @param the string written by the user
* @return OK if command is changed with user's input
*/

STATUS get_user_input(Command* command, char* input){
	char action[CMD_LENGHT]; /*The action written*/
	/*char input[CMD_LENGHT];*/ /*The real input*/
	char symbol[50]; /*The character for TAKE and DROP*/
	char* toks = NULL; /*String for tokenization*/

	if(command == NULL || input == NULL){
		return ERROR;
	}
	
	toks = strtok(input, " \n");
	if(toks != NULL){/*If theres nothing written -> NO_CMD*/
		strcpy(action, toks);
		toks = strtok(NULL, " \n");
		if(toks != NULL){ /*If there is a symbol -> set the symbol to the introduced valor*/
			strcpy(symbol, toks);
		}
		else{/*If there's not a symbol we set to E*/
			symbol[0] = '\0';
			command->symbol[0] = '\0';
		}

		#ifdef DEBUG
			printf("Leido: %s\n", input); /*Debug case*/
		#endif


		/*Detecting what command was written*/
		if (!strcmp(action, "q") || !strcmp(action, "quit")){
			command->cmd = QUIT;
		}
		else if (!strcmp(action, "p") || !strcmp(action, "pick")){

			command->cmd = PICK;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "d") || !strcmp(action, "drop")){
			command->cmd = DROP;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "r") || !strcmp(action, "roll")){
			command->cmd = ROLL;
		}
		else if (!strcmp(action, "i") || !strcmp(action, "inspect")){
			command->cmd = INSPECT;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "g") || !strcmp(action, "go")){
			command->cmd = GO;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "turnon")){
			command->cmd = TURNON;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "turnoff")){
			command->cmd = TURNOFF;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "open")){
			command->cmd = OPEN;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "save") || !strcmp(action, "s")){
			command->cmd = SAVE;

			strcpy(command->symbol, symbol);
		}
		else if (!strcmp(action, "load") || !strcmp(action, "l")){
			command->cmd = LOAD;

			strcpy(command->symbol, symbol);
		}
		else{
			command->cmd = UNKNOWN;
		}
	}
	else{
		command->cmd = NO_CMD;
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
	newcom->symbol[0] = '\0';
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

char *command_get_symbol(Command *com){
	if(!com){
		return '\0';
	}
	return com->symbol;
}

/**
* @brief Copies a command to another
* @author Óscar Gómez
* @date 16-12-2016
* @param Command *to (The command where you copy)
* @param Command *from (The command to copy)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS command_copy(Command *to, Command *from){
	if(!to || !from){
		return ERROR;
	}
	to->cmd = from->cmd;
	strcpy(to->symbol, from->symbol);
	return OK;
}
