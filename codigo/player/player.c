/* ===================================================================
File: player.c

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the functionality of the players 

Revision history: none

=================================================================== */-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

struct _Player {
	Id id;
	char name[WORD_SIZE +1];
	Id location;
	Object *object[MAX_OBJECTS]; /*We've set MAX_OBJECTS
								as 1, in order to prepare 
								the bag creation*/
}

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

BOOL player_destroy(Player* player){
	if(!player) {
		return ERROR;
	}

	free(player);
	player = NULL;

	return OK;
}

STATUS player_set_name(Player* player, char* name) {
	if (!player || !name) {
		return ERROR;
	}

	if (!strcpy(player->name, name)) {
		return ERROR;
	}

	return OK;
}

STATUS player_set_location(Player* player, Id location) {
	if (!player || location == NO_ID){
		return ERROR;
	}

	player->location = location;

	return OK;
}

const char* player_get_name(Player* player) {
	if (!player) {
		return NULL;
	}

	return player->name;
}

const Id player_get_location (Player* player) {
	if (!player){
		return NULL;
	}

	return player->location;
}
