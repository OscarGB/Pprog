/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include "command.h"

#define CMD_LENGHT 30

T_Command get_user_input(){
T_Command cmd = NO_CMD;char input[CMD_LENGHT] = "";  
if (scanf("%s", input) > 0){if (!strcmp(input, "q") || !strcmp(input, "quit")){cmd = QUIT;}else if (!strcmp(input, "n") || !strcmp(input, "next")){cmd = NEXT;}else if (!strcmp(input, "b") || !strcmp(input, "back")){cmd = BACK;}else{cmd = UNKNOWN;}}
return cmd;
}
