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
  DROP
} T_Command; 


/* --------------------------------------------------------------------
Function: get_user_input()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads from keyboard in search of a valid command to execute

Input: none

Output: T_Command (returns the command that has been written by the user)

------------------------------------------------------------------- */
T_Command get_user_input();

#endif
