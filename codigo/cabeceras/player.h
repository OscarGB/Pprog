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
#include "object.h"

typedef struct _Player Player;


/* --------------------------------------------------------------------
Function: player_create()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: creates a new player

Input: the id of the player

Output: OK if the player was successfuly created

------------------------------------------------------------------- */
BOOL player_crete(Id id);


/* --------------------------------------------------------------------
Function: player_destroy()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a player

Input: Player*

Output: OK if the player was successfuly destroyed

------------------------------------------------------------------- */
BOOL player_destroy(Player* player);


/* --------------------------------------------------------------------
Function: player_set_name()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: sets the player's name

Input: Player* and char* (player's name)

Output: OK if the name was successfuly set

------------------------------------------------------------------- */
STATUS player_set_name(Player* player, char* name);


/* --------------------------------------------------------------------
Function: player_set_location()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: sets the location of the player

Input: Player* and the location id

Output: OK if the location was successfuly created

------------------------------------------------------------------- */
STATUS player_set_location(Player* player, Id location);


/* --------------------------------------------------------------------
Function: player_get_name()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gets the name of the player

Input: Player*

Output: char* (player's name)

------------------------------------------------------------------- */
const char* player_get_name(Player *player);


/* --------------------------------------------------------------------
Function: player_get_location()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gets the location of the player

Input: Player*

Output: location id

------------------------------------------------------------------- */
const Id player_get_location(Player *player);


/* --------------------------------------------------------------------
Function: player_drop_object()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it points the player object to NULL and return
the object

Input: Player*

Output: Object* (the dropped object)

------------------------------------------------------------------- */
Object* player_drop_object(Player *player);


/* --------------------------------------------------------------------
Function: player_pick_object()

Date: 01/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: if the bag isn't full, it places an object
in the bag

Input: Player*, Object* (the picked object)

Output: TRUE if the object was picked

------------------------------------------------------------------- */
BOOL player_drop_object(Player *player, Object* object);

#endif