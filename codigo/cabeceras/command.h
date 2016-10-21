/* ===================================================================
File: command.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the command interpreter

Revision history: none

=================================================================== */


#ifndef COMMAND_H
#define COMMAND_H

/*Enumeration of valid commands*/
typedef enum enum_Command { 
  NO_CMD = -2, 
  UNKNOWN, 
  QUIT, 
  NEXT,
  JUMP, 
  BACK,
  PICK,
  DROP,
  ROLL
} T_Command; 

typedef struct _Command Command;


/* --------------------------------------------------------------------
Function: get_user_input()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads from keyboard in search of a valid command to execute
			it creates the command inside

Input: none

Output: Command (returns the command that has been written by the user)

------------------------------------------------------------------- */
Command* get_user_input();

/* --------------------------------------------------------------------
Function: command_create()

Date: 21/10/2016 

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates a command, defining its atributes tu UNKNOWN and ''

Input: none

Output: Command* (The created command)

------------------------------------------------------------------- */
Command* command_create();

/* --------------------------------------------------------------------
Function: command_destroy()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroys a command, freeing all the memory

Input: Command* (The command to destroy)

Output: void

------------------------------------------------------------------- */
void command_destroy(Command *com);

/* --------------------------------------------------------------------
Function: command_get_cmd()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gives the value of the T_Command inside Command

Input: Command* (The command to inspect)

Output: T_Command (The T_Command inside the given Command)

------------------------------------------------------------------- */
T_Command command_get_cmd(Command *com);

/* --------------------------------------------------------------------
Function: command_get_symbol()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: IT gives the value of the symbol inside Command

Input: Command* (The command to inspect)

Output: char (The symbol inside the given Command)

------------------------------------------------------------------- */
char command_get_symbol(Command *com);

#endif
