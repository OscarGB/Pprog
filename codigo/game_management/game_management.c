/**
 * @brief It implements the rutine that reads a file to prepare the game
 * @file game_reader.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 2.0
 * @date 22/09/2016
 * @revision_history 2.0 included reader for objects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_management.h"
#include "game.h"
#include "object.h"
#include "space.h"

#define VACIO "+------------+|           ||           ||           ||           ||           ||           |+------------+"


/**
* @brief prints a given space to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Space* space
* @return OK if the space was succesfully printed
*/

STATUS print_space_save(FILE *f, Space* space){
  Id id; 
  char name[WORD_SIZE + 1]; 
  Id north;
  Id east; 
  Id south; 
  Id west; 
  Id up; 
  Id down; 
  char buff[MAX_GDESC];
  /*char *toks=NULL; */
  BOOL light;
  char lux[100];
  char adesc[MAX_ADESC];

  if(!f || !space) return ERROR;
  id = space_get_id(space);
  strcpy(name,space_get_name(space));
  north = space_get_north(space);
  south = space_get_south(space);
  east = space_get_east(space);
  west = space_get_west(space);
  up = space_get_up(space);
  down = space_get_down(space);
  light= space_get_light(space);
  strcpy(buff,space_get_gdesc(space));
  strcpy(adesc,space_get_adesc(space));

  if(light==TRUE){
    strcpy(lux, "TRUE");
  }else{
    strcpy(lux, "FALSE");
  }

  /*toks = strtok(buff, "\n");
  strcat(gdesc, toks);
  toks = strtok(NULL, "\n");
  strcat(gdesc, toks);
  toks = strtok(NULL, "\n");
  strcat(gdesc, toks);*/

  fprintf(f, "#s:%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%s|%s|%s/\n", 
      id, name, north, east, south, west, up, down,
      lux, adesc, buff);

  return OK;
}

/**
* @brief prints a given link to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Link* link
* @return OK if the link was succesfully printed
*/

STATUS print_link_save(FILE *f, Link *link){

  Id id; 
  char name[WORD_SIZE + 1]; 
  Id conection1; 
  Id conection2; 
  State state; 
  char stt[100];

  if(!f || !link) return ERROR;

  id = link_get_id(link);
  strcpy(name, link_get_name(link));
  conection1 = link_get_conection1(link);
  conection2 = link_get_conection2(link);
  state = link_get_state(link);

  if(state==CLOSEDL){
    strcpy(stt, "CLOSEDL");
  }else{
    strcpy(stt, "OPENL");
  }

  fprintf(f, "#l:%ld|%ld|%ld|%s|%s|\n", 
      id, conection1, conection2, name, stt);
  return OK;
  }

  /**
* @brief prints a given object to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Object* object
* @return OK if the object was succesfully printed
*/

STATUS print_object_save(FILE *f, Object *object){

  Id id;
  char name[WORD_SIZE + 1]; 
  char symbol; 
  Id location;
  char desc[WORD_SIZE+1];
  char mdesc[WORD_SIZE+1];
  BOOL movable;
  BOOL moved;
  BOOL hidden;
  Id open;
  BOOL light;
  BOOL on_off;
  int duration;
  char mvbl[100], mvd[100], hddn[100], lux[100], on[100];


  if(!f || !object) return ERROR;

  id = object_get_id(object);
  strcpy(name,object_get_name(object));
  strcpy(desc, object_get_desc(object));
  strcpy(mdesc, object_get_mdesc(object));
  symbol = object_get_symbol(object);
  location = object_get_location(object);
  movable = object_get_movable(object);
  moved = object_get_moved(object);
  hidden = object_get_hidden(object);
  open = object_get_open(object);
  light = object_get_light(object);
  on_off = object_get_on_off(object);
  duration = object_get_duration(object);

  if(light==TRUE){
    strcpy(lux, "TRUE");
  }else{
    strcpy(lux, "FALSE");
  }

  if(movable==TRUE){
    strcpy(mvbl, "TRUE");
  }else{
    strcpy(mvbl, "FALSE");
  }

  if(moved==TRUE){
    strcpy(mvd, "TRUE");
  }else{
    strcpy(mvd, "FALSE");
  }

  if(hidden==TRUE){
    strcpy(hddn, "TRUE");
  }else{
    strcpy(hddn, "FALSE");
  }

  if(on_off==TRUE){
    strcpy(on, "TRUE");
  }else{
    strcpy(on, "FALSE");
  }
  
  fprintf(f, "#o:%ld|%ld|%s|%s|%s|%c|%s|%s|%s|%s|%s|%ld|%d|\n", 
      id, location, name, desc, mdesc, symbol, mvbl, mvd,
      hddn, lux, on, open, duration);

  return OK;
}

/**
* @brief prints a given player to a file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param FILE* file, Player* player
* @return OK if the player was succesfully printed
*/

STATUS print_player_save(FILE *f, Player *player){
  Id id;
  char name[WORD_SIZE +1];
  Id location; 

  if(!f || !player) return ERROR;

  id = player_get_id(player);
  strcpy(name, player_get_name(player));
  location = player_get_location(player);

  fprintf(f, "#p:%ld|%ld|%s|\n", id, location, name); 

  return OK;
}

/**
* @brief saves a game in the given file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game, char* savepath
* @return OK or ERROR
*/

STATUS game_save(Game* game, char* savepath){
  FILE *f=NULL;
  int i;

  if(!game || !savepath) return ERROR;

  f=fopen(savepath, "w+");
  if(!f)
    return ERROR;

  print_player_save(f, game_get_player(game));

  for(i=0; i<MAX_SPACES && game_get_space_at(game, i) != NULL; i++){ /*loops for printing all not null links, spaces and objects to file*/
    print_space_save(f, game_get_space_at(game,i));
  }

  for(i=0; i<MAX_LINKS && game_get_link_n(game, i)!=NULL; i++){
    print_link_save(f, game_get_link_n(game, i));
  }

  for(i=0; i<=MAX_IDS && game_get_object_at(game, i) != NULL; i++){
    print_object_save(f, game_get_object_at(game, i));
  }

  fclose(f);
  return OK;
}

/**
* @brief loads a game from the given file
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game, char* savepath
* @return OK or ERROR
*/

STATUS game_load(Game* game, char* path){

	FILE *file;
	STATUS ret1 = OK, ret2 = OK, ret3 = OK, ret4 = OK, status = OK;
	char line[WORD_SIZE+1];


	if(!game || !path)
	    return ERROR;

	file = fopen(path, "r+");
	if (file == NULL) {
	    return ERROR;
	}

	while (fgets(line, WORD_SIZE, file)) {
		if(!strncmp("#s:", line, 3)){
			ret1 = game_load_space(game, line+3);

		} else if(!strncmp("#o:", line, 3)){
			ret2 = game_load_object(game, line+3);

		}else if(!strncmp("#l:", line, 3)){
			ret3 = game_load_link(game, line+3);

		}else if(!strncmp("#p:", line, 3)){
			ret4 = game_load_player(game, line+3);
		}else
			break;
	}

    if (ferror(file)) {
    	status = ERROR;
  	}

  fclose(file);

  if(ret1 == OK && ret2 == OK && ret3 == OK && ret4 == OK){
  	return status;
  }
  return ERROR;
}

STATUS game_load_object(Game* game, char* line) {

  char *toks = NULL;
  STATUS status = ERROR;
  Object *object;
  Id id;
  char name[WORD_SIZE + 1]; 
  char symbol; 
  Id location;
  char desc[WORD_SIZE+1];
  char mdesc[WORD_SIZE+1];
  BOOL movable = FALSE;
  BOOL moved = FALSE;
  BOOL hidden = FALSE;
  Id open;
  BOOL light = FALSE;
  BOOL on_off = FALSE;
  int duration;


      toks = strtok(line, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks);
      toks = strtok(NULL, "|");
      strcpy(mdesc, toks);
      toks = strtok(NULL, "|");
      symbol = toks[0];
      toks = strtok(NULL, "|");
      if (!strcmp(toks, "TRUE"))
      	movable = TRUE;
      toks = strtok(NULL, "|");
      if (!strcmp(toks, "TRUE"))
      	moved = TRUE;
      toks = strtok(NULL, "|");
      if (!strcmp(toks, "TRUE"))
      	hidden = TRUE;
      toks = strtok(NULL, "|");
      if (!strcmp(toks, "TRUE"))
      	light = TRUE;
      toks = strtok(NULL, "|");
      if (!strcmp(toks, "TRUE"))
      	on_off = TRUE;
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      duration = atoi(toks);
      

      object = object_create(id);
      if (object != NULL) {
      	object_set_location(object, location);
      	object_set_name(object, name);
      	object_set_desc(object, desc);
      	object_set_mdesc(object, mdesc);
      	object_set_symbol(object, symbol);
      	object_set_movable(object, movable);
      	object_set_moved(object, moved);
      	object_set_hidden(object, hidden);
      	object_set_light(object, light);
      	object_set_on_off(object, on_off);
        object_set_open(object, open);
        /*object_set_duration(object, duration);*/
        status = game_add_object(game, object);
      }
  
return status;
}

STATUS game_load_player(Game* game, char* line) {

  char *toks = NULL;
  STATUS status = ERROR;
  Player* player;
  Id id;
  char name[WORD_SIZE +1];
  Id location; 

      toks = strtok(line, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);

      player = player_create(id);
      if (player != NULL) {
      	player_set_location(player, location);
      	player_set_name(player, name);
      	status = game_add_player(game, player);
      }
  
return status;
}

STATUS game_load_link(Game* game, char* line) {

  char *toks = NULL;
  STATUS status = ERROR;
  Link* link;
  Id id; 
  char name[WORD_SIZE + 1]; 
  Id conection1; 
  Id conection2; 
  State state; 

      toks = strtok(line, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      conection1 = atol(toks);
      toks = strtok(NULL, "|");
      conection2 = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
 	  toks = strtok(NULL, "|");
      if (!strcmp(toks, "OPENL"))
      	state = OPENL;

      link = link_create(id);
      if (link != NULL) {
      	link_set_name(link, name);
      	link_set_conection1(link, conection1);
      	link_set_conection2(link, conection2);
      	link_set_state(link, state);
      	status = game_add_link(game, link);
      }
return status;
}

STATUS game_load_space(Game* game, char* line) {

  char *toks = NULL;
  STATUS status = ERROR;
  Space *space;
  Id id; 
  char name[WORD_SIZE + 1]; 
  Id north;
  Id east; 
  Id south; 
  Id west; 
  Id up; 
  Id down; 
  char gdesc[MAX_GDESC];
  /*char *toks=NULL; */
  BOOL light = FALSE;
  char adesc[MAX_ADESC];

      toks = strtok(line, "|");
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
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      if(!strcmp(toks, "TRUE"))
      	light = TRUE;
      toks = strtok(NULL, "|");
      strcpy(adesc, toks);
      toks = strtok(NULL, "/");
      strcpy(gdesc, toks);

      space = space_create(id);
      if (space != NULL) {
      	space_set_name(space, name);
      	space_set_north(space, north);
      	space_set_east(space, east);
      	space_set_south(space, south);
      	space_set_west(space, west);
      	space_set_up(space, up);
      	space_set_down(space, down);
      	space_set_light(space, light);
      	space_set_adesc(space, adesc);
      	space_set_gdesc(space, gdesc);
      	status = game_add_space(game, space);
      }
return status;
}

