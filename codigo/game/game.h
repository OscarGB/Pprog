/**
 * @brief Declaration of struct game and functions in game.c
 * @file game.h
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
#include "graphics.h"

#define PLAYER_OBJ -2 /*!< Id for an object into the player's bag*/
#define DIE_FACES 6 /*!< Faces of the die*/
#define GET_BOOL(x) ("(x==0)? TRUE: FALSE)")
#define DEATH_DESERVED 100 /*!< Maximum number of turns allowed by a random function of game_rules */


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
* @brief Gets the location of the player
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return The id of the player location
*/
Id     game_get_player_location(Game* game);

/**
* @brief It gets the space from a given id
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Id space id
* @return Space pointer with that id
*/
Space* game_get_space(Game* game, Id id);

/**
* @brief It gets the object from a given id
* @author Andrea Ruiz
* @date 17/12/2016
* @param game pointer
* @param Id space id
* @return Object pointer with that id
*/
Object * game_get_object(Game* game, Id id);

/**
* @brief it calls different callbacks depending on the written command
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Command cmd
* @return OK if it was updated
*/
STATUS game_update(Game* game, Command *cmd, Dialogue* dia, Graphics* gra);

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
* @author José Ignacio Gómez, Óscar Gómez, Andrea Ruiz
* @date 29/09/2016
* @param game pointer
* @return void
*/
void   game_print_screen(Game* game, Graphics* gra);

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

<<<<<<< HEAD
=======
/**
* @brief Returns the game die
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return Die pointer
*/
Die * game_get_die(Game * game);

/**
* @brief Returns the link in a concrete position
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return Link pointer
*/
Link * game_get_link_n(Game * game, int n);

/**
* @brief Returns the number of links
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of links)
*/
int game_get_num_links(Game * game);

/**
* @brief Returns the objects in the game (all of them)
* @author Andrea Ruiz
* @date 16/12/2016
* @param Object ** object
* @return pointer to the array of objects
*/	
Object ** game_get_objects(Game * game);

/**
* @brief Returns the number of objects
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of objects)
*/
int game_get_num_objects(Game * game);

/**
* @brief Returns the number of turns
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of objects)
*/

int game_get_turns(Game * game);

/**
* @brief Returns the player pointer
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return player pointer
*/

Player * game_get_player(Game * game);

#endif

