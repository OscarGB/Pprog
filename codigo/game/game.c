/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Óscar Gómez, Jose Ignacio Gómez
 * @version 1.0 
 * @date 23/09/2016
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

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

STATUS game_init(Game* game) {
  int i;
  
  game_destroy(game); /*Just in case the game has been initialized*/

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  
  game->player_location = NO_ID;
  game->object_location = NO_ID;
  
  return OK;
}

STATUS game_init_from_file(Game* game, char* filename) {

  if (game_init(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

STATUS game_destroy(Game* game) {
    int i = 0;

    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
      space_destroy(game->spaces[i]);
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

    game->player_location = id;
    return OK; /*Linea cambiada debido a warning durante compilación*/
}

STATUS game_set_object_location(Game* game, Id id) {
  
    /*int i = 0;*//*¿Sobra?*/

    if (id == NO_ID) {
        return ERROR;
    }

    game->object_location = id;

    return OK;
}

Id game_get_player_location(Game* game) {
    return game->player_location;
}

Id game_get_object_location(Game* game) {
    return game->object_location;
}

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
  case NO_CMD:
    break;
  default: /* We must never arrive here*/
    return ERROR;
  }

  return OK;
}

void game_print_data(Game* game) {
  int i = 0;
  
  printf("\n\n-------------\n\n");
  
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }
  
  printf("=> Object location: %d\n", (int) game->object_location);    
  printf("=> Player location: %d\n", (int) game->player_location);
  printf("prompt:> ");
}

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
  
  if (game->object_location == id_back) 
    obj='*';
  else 
    obj=' ';
  
  if (id_back != NO_ID) {
    printf("|         %2d|\n",(int) id_back);
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
    printf("      ^\n");
  }
  
  if (game->object_location == id_act)
    obj='*';
  else 
    obj=' ';
  
  if (id_act != NO_ID) {
    printf("+-----------+\n");
    printf("| 8D      %2d|\n",(int)id_act);
    printf("|     %c     |\n",obj);
    printf("+-----------+\n");
  }
  
  if (game->object_location == id_next)
    obj='*';
  else 
    obj=' ';
  
  if (id_next != NO_ID) {
    printf("      v\n");
    printf("+-----------+\n");
    printf("|         %2d|\n",(int)id_next);
    printf("|     %c     |\n",obj);
  }
  
  if (game->object_location != NO_ID)
    printf ("\nOject location:%d", (int)game->object_location);

  printf("\n[commands: next or n, back or b, or quit or q]");
  printf("\nprompt:> ");
}

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

STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
	game_add_space(game, space);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}
