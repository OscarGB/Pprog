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
#define MAX_OBJECTS 1000 /*!< Max amount of objects (1000)*/

#include "types.h"
#include "object.h"
#include "inventory.h"

typedef struct _Player Player; /*<!Definition of the player structure*/


/**
* @brief creates a new player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
* @date 01/10/2016 (modified 08/11/2016)
* @param the id of the player
* @return Player* (created player)
*/

Player* player_create(Id id);


/**
* @brief destroys a player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
* @date 01/10/2016 (modified 08/11/2016)
* @param player pointer
* @return STATUS (OK if the player was successfuly destroyed)
*/

STATUS player_destroy(Player* player);


/**
* @brief sets the player's name
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @param char* (player's name)
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_name(Player* player, char* name);


/**
* @brief sets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer 
* @param Id location id
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_location(Player* player, Id location);


/**
* @brief gets the name of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return char* (player's name)
*/

const char* player_get_name(Player *player);


/**
* @brief gets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return location id
*/

const Id player_get_location(Player *player);


/**
* @brief deletes the item of the bag so the player drops it
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param player pointer
* @param Id id of the object to drop
* @return BOOL (TRUE if the object was dropped)
*/

BOOL player_drop_object(Player *player, Id id);


/**
* @brief if the bag isn't full, it places an object
in the bag
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param Player*
* @param Id id of the picked object
* @return BOOL(TRUE if the object was picked)
*/

BOOL player_pick_object(Player *player, Id id);


/**
* @brief returns the size of the player's bag
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 24/11/2016
* @param Player*
* @return size of the bag (int)
*/

int player_get_bag_size(Player *player);

/**
* @brief Search for an item in the bag
* @author José Ignacio Gómez
* @date 9/12/2016
* @param Player*, id
* @return BOOL
*/
BOOL player_has_object(Player *player, Id id);

/**
* @brief Gets the inventory of the player
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Player*
* @return Inventory*
*/
Inventory* player_get_inventory(Player* player);

/**
* @brief Returns the id of the player
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Player* player
* @return Id (id from player)
*/
Id player_get_id(Player* player);


#endif
