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
};


/* --------------------------------------------------------------------
Function: player_create()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: creates a new player

Input: the id of the player

Output: OK if the player was successfuly created

------------------------------------------------------------------- */
BOOL player_create(Id id){

	Player *newPlayer = NULL;

	if(id == NO_ID)
		return NULL;

	newPlayer = (Player *) malloc (sizeof(Player));

	if(!newplayer) {
		return NULL;
	}

	newPlayer->id = id;

	newPlayer->name[0] = '\0';

	newPlayer->location = NO_ID;

	newPlayer->object = NULL;

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
BOOL player_destroy(Player* player){
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

BOOL player_pick_object (Player* player, Object* object){
	int i;

	for (i = 0; i < MAX_OBJECTS; i++){
		if (player->object[i] == NULL){
			player->object[i] = object;
			return TRUE;
		}
	}

	return FALSE;
}