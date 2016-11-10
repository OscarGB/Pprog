/**
 * @brief Declaration of struct game and functions in game.c
 * @file game.c
 * @author Óscar Gómez, José Ignacio Gómez, Óscar pinto
 * @version 1.0
 * @date 9/11/2016
 */

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

/**
* @brief it creates an empty game table with no player/object location
* if the game pointer has been already initialized, we have decided to destroy 
* the previous game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it was successfuly initialized
*/
Game* game_init(Game* game);

/**
* @brief it creates a game table loading spaces from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer and a filename
* @return OK if it was successfuly initialized
*/
STATUS game_init_from_file(Game* game, char* filename);

/**
* @brief it calls different callbacks depending on the written command
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Command cmd
* @return OK if it was updated
*/
STATUS game_update(Game* game, Command *cmd);

/**
* @brief it destroys a given game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer 
* @return OK if the game was successfuly destroyed
*/
STATUS game_destroy(Game* game);

/**
* @brief ends the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return FALSE
*/
BOOL   game_is_over(Game* game);

/**
* @brief prints on screen the data of the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return void
*/
void   game_print_screen(Game* game);

/**
* @brief Prints on screen the actual game state
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return void
*/
void   game_print_data(Game* game);


/**
* @brief it adds an space to the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param space pointer (added space)
* @return OK if it was added
*/
STATUS game_add_space(Game* game, Space* space); 

/**
* @brief Adds an object to the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 27/10/2016
* @param game pointer
* @param object pointer (added)
* @return OK if it was added
*/
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
