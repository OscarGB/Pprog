/* ===================================================================
File: game_reader.c

Version: 2.0

Date: 22/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: implementation of the rutine that reads a file to preapre the game

Revision history: 2.0 included reader for objects

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "object.h"
#include "space.h"


/* --------------------------------------------------------------------
Function: game_load_spaces()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads the game table from a file

Input: Game* and a char* (filename)

Output: OK if the table was successfuly read

------------------------------------------------------------------- */
STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL; /*File to read*/
  char line[WORD_SIZE] = ""; /*Line read*/
  char name[WORD_SIZE] = ""; /*Name of the space read*/
  char gdesc[MAX_GDESC]; /*Gdesc (drawing of the space)*/
  char* toks = NULL; /*String for tokenization*/
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID; /*Group of Ids for the space*/
  Space* space = NULL; /*Space pointer*/
  STATUS status = OK; /*Status set to OK*/
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  /*Reading of the file*/
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
      toks = strtok(NULL, "|");
      strcpy(gdesc, "|");
      strcat(gdesc, toks);
      strcat(gdesc, "|\n");
      toks = strtok(NULL, "|");
      strcat(gdesc, "|");
      strcat(gdesc, toks);
      strcat(gdesc, "|\n");
      toks = strtok(NULL, "|");
      strcat(gdesc, "|");
      strcat(gdesc, toks);
      strcat(gdesc, "|\n");
      strcat(gdesc, "\0");
      
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\nGdesc:\n%s\n", id, name, north, east, south, west, gdesc);
#endif

      space = space_create(id);
      if (space != NULL) {
      	space_set_name(space, name);
      	space_set_north(space, north);
      	space_set_east(space, east);
      	space_set_south(space, south);
      	space_set_west(space, west);
        space_set_gdesc(space, gdesc);
      	game_add_space(game, space);
      }
    }
  }
  
  /*We make this to prevent exiting without closing the file*/
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
  FILE* file = NULL; /*File to read*/
  char line[WORD_SIZE] = ""; /*Line read*/
  char symbol = 'E'; /*Symbol of the objects*/
  char* toks = NULL; /*String for tokenization*/
  Id object_id = NO_ID, space_id = NO_ID; /*Ids for the object*/
  Object* object = NULL; /*Object pointer*/
  STATUS status = OK; /*Status set to OK*/
  int num_objects = 0; /*Number of objects read*/

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
  
  /*We make this to prevent exiting without closing the file*/
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  
return status;
}