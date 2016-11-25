/**
 * @brief It implements the functionality of the player
 * @file player.c
 * @author Óscar Gómez, José Ignacio Gómez, Andrea Ruiz
 * @version 1.0
 * @date 30/09/2016
 * @revision_history none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "inventory.h"


struct _Player {
	Id id; /*<!Id of the player*/
	char name[WORD_SIZE +1]; /*<!Name of the player*/
	Id location; /*<!Location in the game*/
	Inventory* bag; /*<!Inventory of the player */
};/*!<Player structure*/


/*
* @brief creates a new player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
* @date 01/10/2016 (modified 08/11/2016)
* @param the id of the player
* @return Player* (created player)
*/

Player* player_create(Id id){


	Player *newPlayer = NULL; /*New player to create*/

	if(id == NO_ID)
		return NULL;

	newPlayer = (Player *) malloc (sizeof(Player));

	if(!newPlayer) {
		return NULL;
	}

	/*Default values*/

	newPlayer->id = id;

	newPlayer->name[0] = '\0';

	newPlayer->location = NO_ID;

	newPlayer->bag = inventory_create(MAX_OBJECTS);

	return newPlayer;
}


/*
* @brief destroys a player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto, Andrea Ruiz
* @date 01/10/2016 (modified 08/11/2016)
* @param player pointer
* @return STATUS (OK if the player was successfuly destroyed)
*/

STATUS player_destroy(Player* player){

	if(!player) {
		return ERROR;
	}
	
	inventory_destroy(player->bag);
	free(player);
	player = NULL;

	return OK;
}


/*
* @brief sets the player's name
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer and char* (player's name)
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_name(Player* player, char* name) {
	if (!player || !name) {
		return ERROR;
	}

	if (!strcpy(player->name, name)) {
		return ERROR;
	}

	return OK;
}


/*
* @brief sets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer and the location id
* @return STATUS (OK if the name was successfuly set)
*/

STATUS player_set_location(Player* player, Id location) {
	if (!player || location == NO_ID){
		return ERROR;
	}

	player->location = location;

	return OK;
}


/*
* @brief gets the name of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return char* (player's name)
*/

const char* player_get_name(Player* player) {
	if (!player || strcmp(player->name, "\0") == 0) {
		return NULL;
	}

	return player->name;
}


/*
* @brief gets the location of the player
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return location id
*/

const Id player_get_location (Player* player) {
	if (!player){
		return NO_ID;
	}

	return player->location;
}


/*
* @brief deletes the item of the bag so the player drops it
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param player pointer, id of the object to drop
* @return BOOL (TRUE if the object was dropped)
*/

BOOL player_drop_object (Player* player, Id id){

	if (!player || inventory_is_empty(player->bag) || id == NO_ID){
		return FALSE;
	}

	if(inventory_delete_item(player->bag, id))
		return TRUE;

	return FALSE;

}


/*
* @brief if the bag isn't full, it places an object
in the bag
* @author Óscar Gómez, Jose Ignacio Gómez, Andrea Ruiz
* @date 01/10/2016
* @param Player*, id of the picked object
* @return BOOL(TRUE if the object was picked)
*/

BOOL player_pick_object (Player* player, Id id){

	if(player == NULL || id == NO_ID || inventory_is_full(player->bag)){
		return FALSE;
	}

	if(inventory_add_item(player->bag, id) == ERROR) return FALSE;

	return TRUE;
}

int player_get_bag_size(Player *player){

	 if(!player) return -1;

	 return inventory_get_size(player->bag);
}
