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
#include "command.h"

#define CMD_LENGHT 30

/* --------------------------------------------------------------------
Function: get_user_input()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads from keyboard in search of a valid command to execute

Input: none

Output: T_Command (returns the command that has been written by the user)

------------------------------------------------------------------- */

T_Command get_user_input(){
	T_Command cmd = NO_CMD;
	char input[CMD_LENGHT] = "";  
	if (scanf("%s", input) > 0){
		if (!strcmp(input, "q") || !strcmp(input, "quit")){
			cmd = QUIT;
		}
		else if (!strcmp(input, "n") || !strcmp(input, "next")){
			cmd = NEXT;
		}
		else if (!strcmp(input, "b") || !strcmp(input, "back")){
			cmd = BACK;
		}
		else{
			cmd = UNKNOWN;
		}
	}
	return cmd;
}
