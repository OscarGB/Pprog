/**
 * @brief It implements the game interface for each command
 * @file game.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 23/09/2016
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"
#include "object.h"
#include "game_reader.h"
#include "die.h"

#ifdef __WINDOWS_BUILD__
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

/**
* @brief List of callbacks for each command in the game 
*/

STATUS callback_UNKNOWN(Game* game);
STATUS callback_QUIT(Game* game);
STATUS callback_NEXT(Game* game);
STATUS callback_BACK(Game* game);
STATUS callback_JUMP(Game* game);
STATUS callback_DROP(Game* game);
STATUS callback_PICK(Game* game, char symbol);
STATUS callback_ROLL(Game* game);


/**
* @brief Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Space* game_get_space(Game* game, Id id);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);
Id     game_get_player_location(Game* game);

STATUS game_add_object(Game* game, Object* object);
STATUS game_set_object_location(Game* game, Id id_s, Id id_o);
Id     game_get_object_location(Game* game, char symbol);

/**
 * @brief Game interface implementation
 */

/**
* @brief it creates an empty game table with no player/object location
* if the game pointer has been already initialized, we have decided to destroy 
* the previous game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it was successfuly initialized
*/
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

  game->num_objects = 0;

  game->die = die_create(1);
  if(!game->die){
    player_destroy(game->player);
    game_destroy(game);
    return ERROR;
  }
  
  if(!game->object){
    game_destroy(game);
    return ERROR;
  }

  return OK;
}

/**
* @brief it creates a game table loading spaces from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer and a filename
* @return OK if it was successfuly initialized
*/
STATUS game_init_from_file(Game* game, char* filename) {

  if (game_init(game) == ERROR)
    return ERROR;


  if (game_load_objects(game, filename) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;
  game_set_player_location(game, game_get_space_id_at(game, 0));
  /*game_set_object_location(game, game_get_space_id_at(game, 0));*/
  
  return OK;
}

/**
* @brief it destroys a given game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer 
* @return OK if the game was successfuly destroyed
*/
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
    }

    if(game->die != NULL){
      die_destroy(game->die);
    }
        
    return OK;
}


/**
* @brief it adds an space to the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param space pointer (added space)
* @return OK if it was added
*/
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

/**
* @brief Adds an object to the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 27/10/2016
* @param game pointer
* @param object pointer (added)
* @return OK if it was added
*/
STATUS game_add_object(Game* game, Object* object) {

    if (object == NULL) {
        return ERROR;
    }

    if(game->num_objects >= MAX_IDS){
      return ERROR;
    }

    game->object[game->num_objects] = object;
    game->num_objects++;

    return OK;
}


/**
* @brief It gets the id of a given position
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param int position
* @return The id of the space
*/
Id game_get_space_id_at(Game* game, int position) {

    if (position < 0 || position >= MAX_SPACES) {
        return NO_ID;
    }

    return space_get_id(game->spaces[position]);
}


/**
* @brief It gets the space from a given id
* @author José Ignacio Gómez, Óscar Gómez
* @date 
* @param 
* @return 
*/
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


/**
* @brief Sets the player location at a given id
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param the id of the location
* @return OK if it was set
*/
STATUS game_set_player_location(Game* game, Id id) {
    
    if (id == NO_ID || !game) {
        return ERROR;
    }

    return player_set_location(game->player, id);
}


/**
* @brief Sets the object location at a given id
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param the id of the location
* @return OK if it was set
*/
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


/**
* @brief Gets the location of the playes
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return The id of the player location
*/
Id game_get_player_location(Game* game) {
    return player_get_location(game->player);
}


/**
* @brief Gets the location of an object
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param the symbol of the object
* @return The id of the object location
*/
Id game_get_object_location(Game* game, char symbol) {
    int i;
    for(i = 0; i < game->num_objects; i++){
      if(object_get_symbol(game->object[i]) == symbol){
        return object_get_location(game->object[i]);
      }
    }
    return NO_ID;
}



/**
* @brief it calls different callbacks depending on the written command
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Command cmd
* @return OK if it was updated
*/
STATUS game_update(Game* game, Command *cmd) {

  switch (command_get_cmd(cmd)) {
  case UNKNOWN:
    return callback_UNKNOWN(game);
  case QUIT:
    return callback_QUIT(game);
  case NEXT:
    return callback_NEXT(game);
  case BACK:
    return callback_BACK(game);
  case JUMP:
    return callback_JUMP(game);
  case PICK:
    return callback_PICK(game, command_get_symbol(cmd));
  case DROP:
    return callback_DROP(game);
  case ROLL:
    return callback_ROLL(game);
  case NO_CMD:
    break;
  default: /* !< We must never arrive here*/
    return ERROR;
  }
  return OK;
}



/**
* @brief Prints on screen the actual game state
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return void
*/
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



/**
* @brief prints on screen the data of the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return void
*/
void game_print_screen(Game* game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Space* space_act = NULL;
  Space* space_back = NULL;
  Space* space_next = NULL;
  char obj[WORD_SIZE];
  char aux[WORD_SIZE];
  int i, last;
  char symbol;
  int obj_size; /* !< Control of the number of objects to print*/

  obj[0] = '\0'; /* !< Set to empty*/
  
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
  obj_size = 0;

  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_back){
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /* !< add the symbol*/
      obj_size++; 
    }
  }
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
  }

  if (id_back != NO_ID) {
    if(space_get_east(space_back) != NO_ID){
      printf("|         %2d|>\n",(int) id_back);
    }
    else{
      printf("|         %2d|\n",(int) id_back);
    }    
    printf("%s", space_get_gdesc(space_back));
    printf("|           |\n");
    printf("| %-6s    |\n",obj);
    printf("+-----------+\n");
    printf("      ^\n");
  }
  
  obj[0] = '\0'; /* !< Set to empty*/
  obj_size = 0;

  for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_act) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /* !< add the symbol*/
      obj_size++;
    }
  }
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
  }

  if (id_act != NO_ID) {
    printf("+-----------+\n");
    if(space_get_east(space_act) != NO_ID){
      printf("| 8D      %2d|>\n",(int) id_act);
    }
    else{
      printf("| 8D      %2d|\n",(int) id_act);
    }
    printf("%s", space_get_gdesc(space_act));
    printf("|           |\n");
    printf("| %-6s    |\n",obj);
    printf("+-----------+\n");
  }

  obj[0] = '\0'; /* !< Set to empty*/
  obj_size = 0;

   for(i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == id_next) {
      aux[0] = object_get_symbol(game->object[i]);
      aux[1] = '\0';
      strcat(obj,aux); /* !< add the symbol*/
      obj_size++;
    }
  }
  if(obj_size > 3){
    obj[3] = '.';
    obj[4] = '.';
    obj[5] = '.';
    obj[6] = '\0';
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
    printf("%s", space_get_gdesc(space_next));
    printf("|           |\n");
    printf("|  %-6s   |\n",obj);
  }
  
  printf("Object locations:");
  for(i = 0; i < game->num_objects; i++){
    printf(" %c:%d", object_get_symbol(game->object[i]), (int)object_get_location(game->object[i]));
  }    
  printf("\n");

  symbol = player_get_object_symbol(game->player);
  printf("Player objects:");
  if(symbol != CHAR_ERROR){
    printf("%c", symbol);
  }
  printf("\n");

  last = die_get_last_roll(game->die);
  if(last != -1){
    printf("Last die value: %d\n", last);
  }

  printf("\n[commands: next or n, back or b, jump or j, quit or q, drop or d, pick or p, roll or r]");
  printf("\nprompt:> ");
}



/**
* @brief ends the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return FALSE
*/
BOOL game_is_over(Game* game) {
  return FALSE;
}


/*
* @brief Private callbacks
*/

/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_UNKNOWN(Game* game) {
  return OK;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_QUIT(Game* game) {
  return OK;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_NEXT(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
        return game_set_player_location(game, current_id);
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_BACK(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  
  if (NO_ID == space_id) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
        return game_set_player_location(game, current_id);
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_JUMP(Game* game){
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID) {
        return game_set_player_location(game, current_id);
      }
      else{
        return ERROR;
      }      
    }
  }
  return ERROR;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_DROP(Game* game){
  Object* object;
  Id current_id;

  object = player_drop_object(game->player);
  if(!object){
    return ERROR;
  }
  current_id = game_get_player_location(game);

  game->object[game->num_objects] = object;
  game->num_objects++;

  return game_set_object_location(game, current_id, object_get_id(object));
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param the symbol to pick
* @return OK if it went ok
*/
STATUS callback_PICK(Game* game, char symbol){
  Object* object;
  Id player_id, object_id;
  int i;

  if(symbol == E){
    return ERROR;
  }

  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    return ERROR;
  }

  for(i = 0; i < game->num_objects; i++){

    if(object_get_symbol(game->object[i]) == symbol){
      object = game->object[i];

      if(player_pick_object(game->player, object) != FALSE){
        object_set_location(object, NO_ID); 
        game->object[i] = game->object[game->num_objects-1]; /*Reorder the table*/
        game->object[game->num_objects -1] = NULL; /*Preventing errors*/
        game->num_objects--; 
        return OK;
      }
    }  
  }

  return ERROR;;
}


/**
* @brief callbac
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_ROLL(Game* game){
    int res;

    res = die_roll(game->die, 1, 6);
    if(res < 1 || res > 6) return ERROR;

    return OK;
}