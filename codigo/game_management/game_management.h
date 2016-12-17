/**
 * @brief It defines the rutine that reads a file to prepare the game
 * @file game_reader.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 30/09/2016
 * @revision_history none
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "space.h"
#include "object.h"
#include "game.h"
#include "types.h"


/**
* @brief reads the game table from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 30/09/2016
* @param Game* and a char* (filename)
* @return OK if the table was successfuly read
*/

STATUS game_load_spaces(Game* game, char* filename);


/**
* @brief reads the objects from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param Game* and a char* (filename)
* @return OK if the objects were successfuly read
*/

STATUS game_load_objects(Game* game, char* filename);


/**
* @brief reads the links from a file
* @author 
* @date 08/10/2016
* @param Game* and a char* (filename)
* @return OK if the links were successfuly read
*/

STATUS game_load_links(Game* game, char* filename);

/**
* @brief reads the player from a file
* @author Óscar Pinto Santamaría
* @date 16/10/2016
* @param Game* and a char* (filename)
* @return OK if the player were successfuly read
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
