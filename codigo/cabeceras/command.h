/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Óscar Gómez, Jose Ignacio Gómez
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

typedef enum enum_Command {
  NO_CMD = -2, 
  UNKNOWN, 
  QUIT, 
  NEXT, 
  BACK
} T_Command;

T_Command get_user_input();

#endif
