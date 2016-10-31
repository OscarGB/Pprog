/* ===================================================================
File: command.c

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the command interpreter

Revision history: none

=================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

#define CMD_LENGHT 30

struct _Command{
	T_Command cmd; /*The command*/
	char symbol; /*A symbol for TAKE and DROP commands*/
};

/* --------------------------------------------------------------------
Function: get_user_action()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads from keyboard in search of a valid command to execute
			it creates the command inside

action: none

Output: Command (returns the command that has been written by the user)

------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------
Function: command_create()

Date: 21/10/2016 

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates a command, defining its atributes tu UNKNOWN and ''

action: none

Output: Command* (The created command)

------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------
Function: command_destroy()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroys a command, freeing all the memory

action: Command* (The command to destroy)

Output: void

------------------------------------------------------------------- */
void command_destroy(Command *com){
	if(!com){
		return;
	}
	free(com);
	return;
}

/* --------------------------------------------------------------------
Function: command_get_cmd()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gives the value of the T_Command inside Command

action: Command* (The command to inspect)

Output: T_Command (The T_Command inside the given Command)

------------------------------------------------------------------- */
T_Command command_get_cmd(Command *com){
	if(!com){
		return UNKNOWN;
	}
	return com->cmd;
}

/* --------------------------------------------------------------------
Function: command_get_symbol()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: IT gives the value of the symbol inside Command

action: Command* (The command to inspect)

Output: char (The symbol inside the given Command)

------------------------------------------------------------------- */
char command_get_symbol(Command *com){
	if(!com){
		return UNKNOWN;
	}
	return com->symbol;
}