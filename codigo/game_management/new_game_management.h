/**
 * @brief It defines the rutine that reads a file to prepare the game
 * @file game_reader.h
 * @author Óscar Gómez, José Ignacio Gómez, Óscar Pinto
 * @version 2.0
 * @date 30/09/2016
 * @revision_history Upgrade to 2.0 (18/12/2016)
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "space.h"
#include "object.h"
#include "game.h"
#include "types.h"


/**
* @brief inserts a space in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game* and a char* (line)
* @return OK if the space was succesfully inserted
*/

STATUS game_load_space(Game* game, char* line);


/**
* @brief inserts a object in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game* and a char* (line)
* @return OK if the object was succesfully inserted
*/

STATUS game_load_object(Game* game, char* line);


/**
* @brief inserts a link in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game* and a char* (line)
* @return OK if the link was succesfully inserted
*/

STATUS game_load_link(Game* game, char* line);

/**
* @brief inserts a player in game
* @author Óscar Pinto Santamaría
* @date 18/12/2016
* @param Game* and a char* (line)
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
* @param FILE* file, Link* link
* @return OK if the link was succesfully printed
*/

STATUS print_link_save(FILE *f, Link *link);

/**
* @brief prints a given object to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Object* object
* @return OK if the object was succesfully printed
*/

STATUS print_object_save(FILE *f, Object *object);

/**
* @brief prints a given player to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Player* player
* @return OK if the player was succesfully printed
*/

STATUS print_player_save(FILE *f, Player *player);

/**
* @brief creates savegame file with current state of the game
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game, char* savepath
* @return OK if the player was succesfully printed
*/

STATUS game_save(Game* game, char* savepath);

/**
* @brief loads game from file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game, char* path
* @return OK if the player was succesfully printed
*/

STATUS game_load(Game* game, char* path);

#endif
