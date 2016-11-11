/**
 * @brief It defines the functionality of the player
 * @file player.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 30/09/2016
 * @revision_history none
 */

#ifndef PLAYER_H
#define PLAYER_H
#define MAX_OBJECTS 1 /*Used to know the bag size*/

#include "types.h"
#include "object.h"

typedef struct _Player Player; /*<!Definition of the player structure*/


/*
* @brief creates a new player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto
* @date 01/10/2016 (modified 08/11/2016)
* @param the id of the player
* @return Player* (created player)
*/

Player* player_create(Id id);


/*
* @brief destroys a player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto
* @date 01/10/2016 (modified 08/11/2016)
* @param player pointer
* @return STATUS (OK if the player was successfuly destroyed)
*/

STATUS player_destroy(Player* player);


/*
* @brief sets the player's name
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer and char* (player's name)
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_name(Player* player, char* name);


/*
* @brief sets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer and the location id
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_location(Player* player, Id location);


/*
* @brief gets the name of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return char* (player's name)
*/

const char* player_get_name(Player *player);


/*
* @brief gets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return location id
*/

const Id player_get_location(Player *player);


/*
* @brief it points the player object to NULL and returns
the object
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return Object* (the dropped object)
*/

Object* player_drop_object(Player *player);


/*
* @brief if the bag isn't full, it places an object
in the bag
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param Player*, Object* (the picked object)
* @return BOOL(TRUE if the object was picked)
*/

BOOL player_pick_object(Player *player, Object* object);


/*
* @brief It return the symbol of the Object that the player has
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 23/10/2016
* @param Player pointer
* @return char (The symbol, if an error occurs it returns CHAR_ERROR)
*/

char player_get_object_symbol (Player* player);

#endif
