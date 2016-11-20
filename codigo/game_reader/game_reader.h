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


/*
* @brief reads the game table from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 30/09/2016
* @param Game* and a char* (filename)
* @return OK if the table was successfuly read
*/

STATUS game_load_spaces(Game* game, char* filename);


/*
* @brief reads the objects from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param Game* and a char* (filename)
* @return OK if the objects were successfuly read
*/

STATUS game_load_objects(Game* game, char* filename);


/*
* @brief reads the links from a file
* @author 
* @date 08/10/2016
* @param Game* and a char* (filename)
* @return OK if the links were successfuly read
*/

STATUS game_load_links(Game* game, char* filename);

#endif
