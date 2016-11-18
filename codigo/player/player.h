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
#define MAX_OBJECTS 10 /*Used to know the bag size*/

#include "types.h"
#include "object.h"

typedef struct _Player Player; /*<!Definition of the player structure*/


/*
* @brief creates a new player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
* @date 01/10/2016 (modified 08/11/2016)
* @param the id of the player
* @return Player* (created player)
*/

Player* player_create(Id id);


/*
* @brief destroys a player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
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
* @brief deletes the item of the bag so the player drops it
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param player pointer, id of the object to drop
* @return BOOL (TRUE if the object was dropped)
*/

BOOL player_drop_object(Player *player, Id id);


/*
* @brief if the bag isn't full, it places an object
in the bag
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param Player*, id of the picked object
* @return BOOL(TRUE if the object was picked)
*/

BOOL player_pick_object(Player *player, Id id);

#endif
