/* ===================================================================
File: player.c

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the functionality of the players 

Revision history: none

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"

struct _Player {
	Id id;
	char name[WORD_SIZE +1];
	Id location;
	Object *object[MAX_OBJECTS]; /*We've set MAX_OBJECTS
								as 1, in order to prepare 
								the bag creation*/
								/*We left it this way because in the I3 we will use
								the inventory*/
};


/* --------------------------------------------------------------------
Function: player_create()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: creates a new player

Input: the id of the player

Output: Player* (created player)

------------------------------------------------------------------- */
Player* player_create(Id id){

	Player *newPlayer = NULL;

	if(id == NO_ID)
		return NULL;

	newPlayer = (Player *) malloc (sizeof(Player));

	if(!newPlayer) {
		return NULL;
	}

	newPlayer->id = id;

	newPlayer->name[0] = '\0';

	newPlayer->location = NO_ID;

	newPlayer->object[0] = NULL;

	return newPlayer;
}

/* --------------------------------------------------------------------
Function: player_destroy()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a player

Input: Player*

Output: OK if the player was successfuly destroyed

------------------------------------------------------------------- */
STATUS player_destroy(Player* player){
	if(!player) {
		return ERROR;
	}

	free(player);
	player = NULL;

	return OK;
}


/* --------------------------------------------------------------------
Function: player_set_name()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: sets the player's name

Input: Player* and char* (player's name)

Output: OK if the name was successfuly set

------------------------------------------------------------------- */
STATUS player_set_name(Player* player, char* name) {
	if (!player || !name) {
		return ERROR;
	}

	if (!strcpy(player->name, name)) {
		return ERROR;
	}

	return OK;
}


/* --------------------------------------------------------------------
Function: player_set_location()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: sets the location of the player

Input: Player* and the location id

Output: OK if the location was successfuly created

------------------------------------------------------------------- */
STATUS player_set_location(Player* player, Id location) {
	if (!player || location == NO_ID){
		return ERROR;
	}

	player->location = location;

	return OK;
}


/* --------------------------------------------------------------------
Function: player_get_name()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gets the name of the player

Input: Player*

Output: char* (player's name)

------------------------------------------------------------------- */
const char* player_get_name(Player* player) {
	if (!player) {
		return NULL;
	}

	return player->name;
}


/* --------------------------------------------------------------------
Function: player_get_location()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gets the location of the player

Input: Player*

Output: location id

------------------------------------------------------------------- */
const Id player_get_location (Player* player) {
	if (!player){
		return NO_ID;
	}

	return player->location;
}


/* --------------------------------------------------------------------
Function: player_drop_object()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it points the player object to NULL and return
the object

Input: Player*

Output: Object* (the dropped object)

------------------------------------------------------------------- */
Object* player_drop_object (Player* player){
	Object *obj = NULL;

	if (!player || !player->object[0]){
		return NULL;
	}

	obj = player->object[0];
	player->object[0] = NULL;

	return obj;
}

/* --------------------------------------------------------------------
Function: player_pick_object()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: if the bag isn't full, it places an object
in the bag

Input: Player*, Object* (the picked object)

Output: TRUE if the object was picked

------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------
Function: player_get_object_symbol()

Date: 23/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It return the symbol of the Object that the player has

Input: Player* (The player to inspect)

Output: char (The symbol, if an error ocurs it return CHAR_ERROR)

------------------------------------------------------------------- */
char player_get_object_symbol (Player* player){
	if(player == NULL || player->object[0] == NULL){
		return CHAR_ERROR;
	}
	return object_get_symbol(player->object[0]);
}