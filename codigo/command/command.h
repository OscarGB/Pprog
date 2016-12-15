/**
 * @brief It defines the command interpreter
 * @file command.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 23/09/2016
 * @revision_history none
 */


#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define CMD_LENGHT 30

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
  ROLL,
  INSPECT,
  GO,
  TURNON,
  TURNOFF,
  OPEN
} T_Command; 

typedef struct _Command Command; /*<! Definition of Command structure */


/*
* @brief reads from keyboard in search of a valid command to execute
* it creates the command inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 23/09/2016
* @param command pointer
* @param the string written by the user
* @return OK if command is changed with user's input
*/

STATUS get_user_input(Command* command, char* input);


/*
* @brief It creates a command, defining its atributes to UNKNOWN and ''
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param none
* @return pointer to the created command
*/

Command* command_create();


/*
* @brief It destroys a command, freeing all the memory
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param pointer to command (to destroy)
* @return none
*/

void command_destroy(Command *com);


/*
* @brief It gives the value of the T_Command inside Command
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param command pointer
* @return T_Command (The T_Command inside the given Command)
*/

T_Command command_get_cmd(Command *com);


/*
* @brief It gives the value of the symbol inside Command
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param command pointer
* @return char (The symbol inside the given Command)
*/

char *command_get_symbol(Command *com);

#endif
