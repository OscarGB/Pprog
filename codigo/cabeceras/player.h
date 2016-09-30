/* ===================================================================
File: player.h

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the functionality of the players 

Revision history: none

=================================================================== */-

#ifndef PLAYER_H
#define PLAYER_H
#define MAX_OBJECTS 1 /*Used to know the bag size*/

#include "types.h"

typedef struct _Player Player;

BOOL player_crete(Id id);

BOOL player_destroy(Player* player);

STATUS player_set_name(Player* player, char* name);

STATUS player_set_location(Player* player, Id location);

const char* player_get_name(Player *player);

const Id player_get_location(Player *player);



#endif