/* ===================================================================
File: command.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the command interpreter

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
  BACK
} T_Command; 

T_Command get_user_input();

#endif
