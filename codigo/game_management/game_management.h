/**
 * @brief It defines the rutine that reads a file to prepare the game
 * @file game_management.h
 * @author Óscar Gómez, José Ignacio Gómez, Óscar Pinto
 * @version 2.0
 * @date 30/09/2016
 * @revision_history Upgrade to 2.0 (18/12/2016)
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"
#include "object.h"
#include "game.h"
#include "types.h"


/**
* @brief inserts a space in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game* 
* @param char* (line)
* @return OK if the space was succesfully inserted
*/

STATUS game_load_space(Game* game, char* line);


/**
* @brief inserts a object in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game*
* @param char* (line)
* @return OK if the object was succesfully inserted
*/

STATUS game_load_object(Game* game, char* line);


/**
* @brief inserts a link in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game*
* @param char* (line)
* @return OK if the link was succesfully inserted
*/

STATUS game_load_link(Game* game, char* line);

/**
* @brief inserts a player in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game*
* @param char* (line)
* @return OK if the player was succesfully inserted
*/

STATUS game_load_player(Game* game, char* savepath);

/**
* @brief prints a given space to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Space* space
* @return OK if the space was succesfully printed
*/

STATUS print_space_save(FILE *f, Space* space);

/**
* @brief prints a given link to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file
* @param Link* link
* @return OK if the link was succesfully printed
*/

STATUS print_link_save(FILE *f, Link *link);

/**
* @brief prints a given object to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file
* @param Object* object
* @return OK if the object was succesfully printed
*/

STATUS print_object_save(FILE *f, Object *object);

/**
* @brief prints a given player to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file
* @param Player* player
* @return OK if the player was succesfully printed
*/

STATUS print_player_save(FILE *f, Player *player);

/**
* @brief saves a game in the given file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game
* @param char* savepath
* @return OK or ERROR
*/

STATUS game_save(Game* game, char* savepath);

/**
* @brief loads a game from the given file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game
* @param char* savepath
* @return OK or ERROR
*/

STATUS game_load(Game* game, char* path);

#endif
