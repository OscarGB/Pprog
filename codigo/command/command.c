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
	T_Command cmd;
	char symbol;
};

/* --------------------------------------------------------------------
Function: get_user_input()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads from keyboard in search of a valid command to execute
			it creates the command inside

Input: none

Output: Command (returns the command that has been written by the user)

------------------------------------------------------------------- */

Command* get_user_input(){
	Command *cmd = NULL;
	char input[CMD_LENGHT];
	char symbol; 

	cmd = command_create();
	if(!cmd){
		return NULL;
	} 

	if (scanf("%s %c", input, &symbol) > 0){
		if (!strcmp(input, "q") || !strcmp(input, "quit")){
			cmd->cmd = QUIT;
		}
		else if (!strcmp(input, "n") || !strcmp(input, "next")){
			cmd->cmd = NEXT;
		}
		else if (!strcmp(input, "b") || !strcmp(input, "back")){
			cmd->cmd = BACK;
		}
		else if (!strcmp(input, "j") || !strcmp(input, "jump")){
			cmd->cmd = JUMP;
		}
		else if (!strcmp(input, "p") || !strcmp(input, "pick")){
			cmd->cmd = PICK;
			cmd->symbol = symbol;
		}
		else if (!strcmp(input, "d") || !strcmp(input, "drop")){
			cmd->cmd = DROP;
		}
		else if (!strcmp(input, "r") || !strcmp(input, "roll")){
			cmd->cmd = ROLL;
		}
		else{
			cmd->cmd = UNKNOWN;
		}
	}
	return cmd;
}

/* --------------------------------------------------------------------
Function: command_create()

Date: 21/10/2016 

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates a command, defining its atributes tu UNKNOWN and ''

Input: none

Output: Command* (The created command)

------------------------------------------------------------------- */
Command* command_create(){
	Command* newcom;
	newcom = (Command *) malloc (sizeof(Command));
	if(!newcom){
		return NULL;
	}
	newcom->cmd = UNKNOWN;
	newcom->symbol = 'E';
	return newcom;
}

/* --------------------------------------------------------------------
Function: command_destroy()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroys a command, freeing all the memory

Input: Command* (The command to destroy)

Output: void

------------------------------------------------------------------- */
void command_destroy(Command *com){
	if(!com){
		return;
	}
	free(com);
}

/* --------------------------------------------------------------------
Function: command_get_cmd()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gives the value of the T_Command inside Command

Input: Command* (The command to inspect)

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

Input: Command* (The command to inspect)

Output: char (The symbol inside the given Command)

------------------------------------------------------------------- */
char command_get_symbol(Command *com){
	if(!com){
		return UNKNOWN;
	}
	return com->symbol;
}