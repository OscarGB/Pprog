/**
 * @brief It implements the functionality of the player
 * @file player.c
 * @author Óscar Gómez, José Ignacio Gómez
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

struct _Player {
	Id id; /*<!Id of the player*/
	char name[WORD_SIZE +1]; /*<!Name of the player*/
	Id location; /*<!Location in the game*/
	Object *object[MAX_OBJECTS]; /*<!We've set MAX_OBJECTS
								as 1, in order to prepare 
								the bag creation*/
								/*We left it this way because in the I3 we will use
								the inventory*/
};


/*
* @brief creates a new player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto
* @date 01/10/2016 (modified 08/11/2016)
* @param the id of the player
* @return Player* (created player)
*/

Player* player_create(Id id){
	int i;

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

	for(i=0; i<MAX_OBJECTS; i++){
		newPlayer->object[i]=NULL; 
	} /*We set all for free() compatibility (avoid double free) the first one because we havent done the bag yet*/

	return newPlayer;
}


/*
* @brief destroys a player
* @author Óscar Gómez, Jose Ignacio Gómez, Óscar Pinto
* @date 01/10/2016 (modified 08/11/2016)
* @param player pointer
* @return STATUS (OK if the player was successfuly destroyed)
*/

STATUS player_destroy(Player* player){
	int i;
	if(!player) {
		return ERROR;
	}
	
	for(i=0; i<MAX_OBJECTS; i++){
		if(player->object[i]) free(player->object[i]); /*This objects are not freed in game.c*/
	}
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
	if (!player) {
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
* @brief it points the player object to NULL and returns
the object
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param player pointer
* @return Object* (the dropped object)
*/

Object* player_drop_object (Player* player){
	Object *obj = NULL;

	if (!player || !player->object[0]){
		return NULL;
	}

	obj = player->object[0];
	player->object[0] = NULL;

	return obj;
}


/*
* @brief if the bag isn't full, it places an object
in the bag
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 01/10/2016
* @param Player*, Object* (the picked object)
* @return BOOL(TRUE if the object was picked)
*/

BOOL player_pick_object (Player* player, Object* object){
	int i;

	if(player == NULL || object == NULL){
		return FALSE;
	}

	for (i = 0; i < MAX_OBJECTS; i++){
		if (player->object[i] == NULL){
			player->object[i] = object;
			return TRUE;
		}
	}

	return FALSE;
}


/*
* @brief It return the symbol of the Object that the player has
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 23/10/2016
* @param Player pointer
* @return char (The symbol, if an error occurs it returns CHAR_ERROR)
*/

char player_get_object_symbol (Player* player){
	if(player == NULL || player->object[0] == NULL){
		return CHAR_ERROR;
	}
	return object_get_symbol(player->object[0]);
}
