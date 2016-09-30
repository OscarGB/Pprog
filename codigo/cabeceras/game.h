/* ===================================================================
File: game.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the game interface for each command 

Revision history: none

=================================================================== */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"

typedef struct _Game{
  Id player_location;
  Id object_location;
  Space* spaces[MAX_SPACES + 1];
} Game;


/* --------------------------------------------------------------------
Function: game_init()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it creates an empty game table with no player/object location
if the game pointer has been already initialized, we have decided to destroy 
the previous game

Input: Game* (game pointer)

Output: OK if the game has been successfuly initialized, ERROR if not

------------------------------------------------------------------- */
STATUS game_init(Game* game);

/* --------------------------------------------------------------------
Function: game_init_from_file()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it creates a game table loading spaces from a file

Input: Game* (game pointer) and char* filename (the name of the 
read file)

Output: OK if the game has been successfuly initialized

------------------------------------------------------------------- */
STATUS game_init_from_file(Game* game, char* filename);

/* --------------------------------------------------------------------
Function: game_update

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it calls different callbacks depending on the written command

Input: Game* and a command (cmd)

Output: OK if everything went OK

------------------------------------------------------------------- */
STATUS game_update(Game* game, T_Command cmd);

/* --------------------------------------------------------------------
Function: game_destroy()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it destroys a given game

Input: Game*

Output: OK if the game was successfuly destroyed

------------------------------------------------------------------- */
STATUS game_destroy(Game* game);

/* --------------------------------------------------------------------
Function: game_is_over()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: ends the game

Input: Game*

Output: -

------------------------------------------------------------------- */
BOOL   game_is_over(Game* game);

/* --------------------------------------------------------------------
Function: game_print_screen()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints on screen the data of the game (player/object situation)

Input: Game*

Output: void

------------------------------------------------------------------- */
void   game_print_screen(Game* game);

/* --------------------------------------------------------------------
Function: game_print_data()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints on screen the actual game state

Input: Game*

Output: void

------------------------------------------------------------------- */
void   game_print_data(Game* game);

#endif
