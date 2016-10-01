/* ===================================================================
File: game.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the game interface for each command 

Revision history: none

=================================================================== */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"
#include "object.h"

#ifdef __WINDOWS_BUILD__
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

/**
   List of callbacks for each command in the game 
*/

void callback_UNKNOWN(Game* game);
void callback_QUIT(Game* game);
void callback_NEXT(Game* game);
void callback_BACK(Game* game);
void callback_DROP(Game* game);
void callback_PICK(Game* game);


/**
   Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Space* game_get_space(Game* game, Id id);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);
Id     game_get_player_location(Game* game);

STATUS game_set_object_location(Game* game, Id id);
Id     game_get_object_location(Game* game);

/**
   Game interface implementation
 */

/* --------------------------------------------------------------------
Function: game_init()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it creates an empty game table with no player/object location
if the game pointer has been already initialized, we have decided to destroy 
the previous game

Input: Game* (game pointer)

Output: OK if the game has been successfuly initialized, ERROR if not

------------------------------------------------------------------- */
STATUS game_init(Game* game) {
  int i;
  
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  
  game->player = NULL;
  game->object = NULL;
  
  return OK;
}

/* --------------------------------------------------------------------
Function: game_init_from_file()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it creates a game table loading spaces from a file

Input: Game* (game pointer) and char* filename (the name of the 
read file)

Output: OK if the game has been successfuly initialized

------------------------------------------------------------------- */
STATUS game_init_from_file(Game* game, char* filename) {

  if (game_init(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/* --------------------------------------------------------------------
Function: game_destroy()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it destroys a given game

Input: Game*

Output: OK if the game was successfuly destroyed

------------------------------------------------------------------- */
STATUS game_destroy(Game* game) {
    int i = 0;

    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
      space_destroy(game->spaces[i]);
    }

    if(game->player != NULL){
      player_destroy(game->player);
    }

    if(game->object != NULL){
      object_destroy(game->object);
    }
        
    return OK;
}

STATUS game_add_space(Game* game, Space* space) {
    int i = 0;

    if (space == NULL) {
        return ERROR;
    }

    while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
        i++;
    }

    if (i >= MAX_SPACES) {
        return ERROR;
    }

    game->spaces[i] = space;

    return OK;
}

Id game_get_space_id_at(Game* game, int position) {

    if (position < 0 || position >= MAX_SPACES) {
        return NO_ID;
    }

    return space_get_id(game->spaces[position]);
}

Space* game_get_space(Game* game, Id id){
    int i = 0;

    if (id == NO_ID) {
      return NULL;
    }
    
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
      if (id == space_get_id(game->spaces[i])){
      	return game->spaces[i];
      }
    }
    
    return NULL;
}

STATUS game_set_player_location(Game* game, Id id) {
    
    if (id == NO_ID) {
        return ERROR;
    }

    return player_set_location(game->player, id);
}

STATUS game_set_object_location(Game* game, Id id) {

    if (id == NO_ID) {
        return ERROR;
    }

    return object_set_location(game->object, id);
}

Id game_get_player_location(Game* game) {
    return player_get_location(game->player);
}

Id game_get_object_location(Game* game) {
    return object_get_location(game->object);
}

/* --------------------------------------------------------------------
Function: game_update

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it calls different callbacks depending on the written command

Input: Game* and a command (cmd)

Output: OK if everything went OK

------------------------------------------------------------------- */
STATUS game_update(Game* game, T_Command cmd) {

  switch (cmd) {
  case UNKNOWN:
    callback_UNKNOWN(game);
    break;
  case QUIT:
    callback_QUIT(game);
    break;
  case NEXT:
    callback_NEXT(game);
    break;
  case BACK:
    callback_BACK(game);
    break;
  case PICK:
    callback_PICK(game);
    break;
  case DROP:
    callback_DROP(game);
    break;
  case NO_CMD:
    break;
  default: /* We must never arrive here*/
    return ERROR;
  }

  return OK;
}

/* --------------------------------------------------------------------
Function: game_print_data()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints on screen the actual game state

Input: Game*

Output: void

------------------------------------------------------------------- */
void game_print_data(Game* game) {
  int i = 0;
  
  printf("\n\n-------------\n\n");
  
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }
  
  printf("=> Object location: %d\n", (int) game_get_object_location(game));    
  printf("=> Player location: %d\n", (int) game_get_player_location(game));
  printf("prompt:> ");
}

/* --------------------------------------------------------------------
Function: game_print_screen()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints on screen the data of the game (player/object situation)

Input: Game*

Output: void

------------------------------------------------------------------- */
void game_print_screen(Game* game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Space* space_act = NULL;
  char obj='\0';
  
  id_act = game_get_player_location(game);
  
  if (id_act == NO_ID){
    return;
  }
  
  space_act = game_get_space(game, id_act);
  id_back = space_get_north(space_act);
  id_next = space_get_south(space_act);
  
  if(system(CLEAR))
  	 return; 
  
  if (game_get_object_location(game) == id_back) 
    obj='*';
  else 
    obj=' ';
  
  if (id_back != NO_ID) {
    printf("|         %2d|\n",(int) id_back);
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
    printf("      ^\n");
  }
  
  if (game_get_object_location(game) == id_act)
    obj='*';
  else 
    obj=' ';
  
  if (id_act != NO_ID) {
    printf("+-----------+\n");
    printf("| 8D      %2d|\n",(int)id_act);
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
  }
  
  if (game_get_object_location(game) == id_next)
    obj='*';
  else 
    obj=' ';
  
  if (id_next != NO_ID) {
    printf("      v\n");
    printf("+-----------+\n");
    printf("|         %2d|\n",(int)id_next);
    printf("|     %c     |\n",obj);
  }
  
  if (game_get_object_location(game) != NO_ID)
    printf ("\nOject location:%d", (int)game_get_object_location(game));

  printf("\n[commands: next or n, back or b, or quit or q]");
  printf("\nprompt:> ");
}

/* --------------------------------------------------------------------
Function: game_is_over()

Date: 29/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: ends the game

Input: Game*

Output: -

------------------------------------------------------------------- */
BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action 
*/

void callback_UNKNOWN(Game* game) {
}

void callback_QUIT(Game* game) {
}

void callback_NEXT(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void callback_BACK(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  
  if (NO_ID == space_id) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void callback_DROP(Game* game){
  Object* object;
  Id current_id;

  object = player_drop_object(game->player)
  if(!object){
    return;
  }
  current_id = game_get_player_location(game);

  game->object = object;

  game_set_object_location(game, current_id);
  return;
}

void callback_PICK(Game* game){
  Object* object
  Id player_id, object_id;

  player_id = game_get_player_location(game);
  object_id = game_get_object_location(game);

  if(player_id != object_id || player_id == NO_ID || object_id==NO_ID){
    return;
  }

  object = game->object; 
  object_set_location(object, NO_ID) 
  if(player_pick_object(game->player, object) != FALSE){
    game->object = NULL;
  }

  return;
}