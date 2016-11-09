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
#include "player.h"
#include "object.h"
#include "set.h"
#include "die.h"
#include "link.h"


typedef struct _Game Game;

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
Game* game_init(Game* game);

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

Input: Game* and a Command (cmd)

Output: OK if everything went OK

------------------------------------------------------------------- */
STATUS game_update(Game* game, Command *cmd);

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


/* --------------------------------------------------------------------
Function: game_add_space()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: adds spaces to the game table

Input: Game* and Space* (adding space)

Output: OK if the space was successfuly added

------------------------------------------------------------------- */
STATUS game_add_space(Game* game, Space* space); 

/* --------------------------------------------------------------------
Function: game_add_object

Date: 27/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Adds an object to the game

Input: Game* (The game to change)
       Object* (The object to add)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS game_add_object(Game* game, Object* object);

/**
* @brief Adds a link to the game
* @author Óscar Gómez
* @date 4/11/2016
* @param Game *game (The game to change)
* @param Link *link (The link to add)
* @return Status (OK if it was added, ERROR if wasn't)
*/
STATUS game_add_link(Game *game, Link* link);


#endif
