
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "object.h"

/* --------------------------------------------------------------------
Function: game_load_spaces()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads the game table from a file

Input: Game* and a char* (filename)

Output: OK if the table was successfuly read

------------------------------------------------------------------- */
STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  int i;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[3][7];
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  int flag;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    flag = 0; /*If flag == 1, a gdesc has been read*/
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
      toks = strtok(NULL, "|");
      if(!toks){
        strcpy(gdesc[0], toks);
        flag = 1;
      }
      toks = strtok(NULL, "|");
      if(!toks){
        strcpy(gdesc[1], toks);
      }
      toks = strtok(NULL, "|");
      if(!toks){
        strcpy(gdesc[2], toks):
      }
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
        if(flag == 1){  
            space_set_gdesc(space, gdesc);
        }
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


/* --------------------------------------------------------------------
Function: game_load_objects()

Date: 21/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads the objects from a file

Input: Game* and a char* (filename)

Output: OK if the objects were successfuly read

------------------------------------------------------------------- */
STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char symbol = 'E';
  char* toks = NULL;
  Id object_id = NO_ID, space_id = NO_ID;
  Object* object = NULL;
  STATUS status = OK;
  int num_objects = 0;

  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file) && num_objects < 4) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);
      toks = strtok(NULL, "|");
      symbol = toks[0];
      
#ifdef DEBUG 
      printf("Leido: %ld|%ld|%c\n", object_id, space_id, symbol);
#endif
      object = object_create(object_id);
      if (object != NULL) {
        object_set_symbol(object, symbol);
        object_set_location(object, space_id);
        game_add_object(game, object);
      }

      num_objects++;
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  
return status;
}