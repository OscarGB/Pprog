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
void callback_JUMP(Game* game);
void callback_DROP(Game* game);
void callback_PICK(Game* game, char symbol);


/**
   Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Space* game_get_space(Game* game, Id id);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);
Id     game_get_player_location(Game* game);

STATUS game_set_object_location(Game* game, Id id_s, Id id_o);
Id     game_get_object_location(Game* game, char symbol);

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
  
  game->player = player_create(1);
  if(!game->player){
    game_destroy(game);
    return ERROR;
  }

  game->object = NULL;

  game->die = die_create(1);
  if(!game->die){
    player_destroy(game->player);
    game_destroy(game);
    return ERROR;
  }
  /*
  for( i = 0; i < MAX_IDS; i++){
    game->object = object_create(i);
  }
  
  if(!game->object){
    game_destroy(game);
    return ERROR;
  }

  for( i = 0; i < MAX_IDS; i++){
    object_set_symbol(game->object, (char) (i + 48));
  }
*/
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

  if (game_load_objects(game, filename) == ERROR)
    return ERROR;
  /*game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));
  */
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
      for (i = 0; i < game->num_objects; i++){
        object_destroy(game->object[i]);
      }
      free(game->object);
    }

    if(game->die != NULL){
      die_destroy(game->die);
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
    
    if (id == NO_ID || !game) {
        return ERROR;
    }

    return player_set_location(game->player, id);
}

STATUS game_set_object_location(Game* game, Id id_s, Id id_o) {

    int i;

    if (id_s == NO_ID || id_o == NO_ID || !game) {
        return ERROR;
    }

    for( i = 0; i < game->num_objects; i++){
      if(object_get_id(game->object[i]) == id_o){
        return object_set_location(game->object[i], id_s);
      }
    }
    return ERROR;
}

Id game_get_player_location(Game* game) {
    return player_get_location(game->player);
}

Id game_get_object_location(Game* game, char symbol) {
    int i;
    for(i = 0; i < game->num_objects; i++){
      if(object_get_symbol(game->object[i]) == symbol){
        return object_get_location(game->object[i]);
      }
    }
    return NO_ID;
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
  case JUMP:
    callback_JUMP(game);
    break;
  case PICK:
    callback_PICK(game);
    break;
  case DROP:
    callback_DROP(game);
    break;
  case ROLL:
    callback_ROLL(game);
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
  
  printf("=> Object locations:");
  for(i = 0; i < game->num_objects; i++){
    printf(" %d", (int)object_get_location(game->object[i]));
  }    
  printf("\n");
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
  Space* space_back = NULL;
  Space* space_next = NULL;
  char obj[WORD_SIZE];
  char aux[WORD_SIZE];
  int i;

  obj[0] = '\0'; /*Set to empty*/
  
  id_act = game_get_player_location(game);
  
  if (id_act == NO_ID){
    return;
  }
  
  space_act = game_get_space(game, id_act);
  id_back = space_get_north(space_act);
  id_next = space_get_south(space_act);
  space_back = game_get_space(game, id_back);
  space_next = game_get_space(game, id_next);
  
  if(system(CLEAR))
  	 return; 
  
  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_back){
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
    }
  }

  if (id_back != NO_ID) {
    if(space_get_east(space_back) != NO_ID){
      printf("|         %2d|>\n",(int) id_back);
    }
    else{
      printf("|         %2d|\n",(int) id_back);
    }    
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
    printf("      ^\n");
  }
  
  obj[0] = '\0'; /*Set to empty*/

  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_act) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
    }
  }
  
  if (id_act != NO_ID) {
    printf("+-----------+\n");
    if(space_get_east(space_act) != NO_ID){
      printf("| 8D      %2d|>\n",(int) id_act);
    }
    else{
      printf("| 8D      %2d|\n",(int) id_act);
    }
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
  }

  obj[0] = '\0'; /*Set to empty*/
  
   for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_next) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /*add the symbol*/
    }
  }
  
  if (id_next != NO_ID) {
    printf("      v\n");
    printf("+-----------+\n");
    if(space_get_east(space_next) != NO_ID){
      printf("|         %2d|>\n",(int) id_next);
    }
    else{
      printf("|         %2d|\n",(int) id_next);
    } 
    printf("|     %c     |\n",obj);
  }
  
  printf("=> Object locations:");
  for(i = 0; i < game->num_objects; i++){
    printf(" %d", (int)object_get_location(game->object[i]));
  }    
  printf("\n");

  printf("\n[commands: next or n, back or b, jump or j, quit or q, drop or d, pick or p, roll or r]");
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

    return res;
}