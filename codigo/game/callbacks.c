/* ===================================================================
File: callbacks.c

Version: 1.0

Date: 27/10/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: Implementation of the callbacks used in game.c

Revision history: none

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"
#include "object.h"
#include "game_reader.h"

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

void callback_JUMP(Game* game){
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
      current_id = space_get_east(game->spaces[i]);
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

  object = player_drop_object(game->player);
  if(!object){
    return;
  }
  current_id = game_get_player_location(game);

  game->object[game->num_objects] = object;
  game->num_objects++;

  game_set_object_location(game, current_id, object_get_id(object));
  return;
}

void callback_PICK(Game* game, char symbol){
  Object* object;
  Id player_id, object_id;
  int i;

  if(symbol == E){
    return;
  }

  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    return;
  }

  for(i = 0; i < game->num_objects; i++){

    if(object_get_symbol(game->object[i]) == symbol){
      object = game->object[i];

      if(player_pick_object(game->player, object) != FALSE){
        object_set_location(object, NO_ID); 
        game->object[i] = game->object[game->num_objects-1]; /*Reorder the table*/
        game->object[game->num_objects -1] = NULL; /*Preventing errors*/
        game->num_objects--; 
      }
    }  
  }

  return;
}

void callback_ROLL(Game* game){
    int res;

    res = die_roll(game->die, 1, 6);
    if(res < 1 || res > 6) return;

    return;
}