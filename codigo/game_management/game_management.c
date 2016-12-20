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
* @brief reads the game table from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 30/09/2016
* @param Game* and a char* (filename)
* @return OK if the table was successfuly read
*/



STATUS game_load_spaces(Game* game, char* filename) {
  char gdesc[MAX_GDESC+1]; /*Gdesc (drawing of the space)*/
  FILE* file = NULL; /*File to read*/
  char line[WORD_SIZE] = ""; /*Line read*/
  char name[WORD_SIZE] = ""; /*Name of the space read*/
  char* toks = NULL; /*String for tokenization*/
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID; /*Group of Ids for the space*/
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
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "\n");
      strcpy(gdesc, toks);
      
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
	      space_set_up(space, up);
        space_set_light(space, TRUE);
	      space_set_down(space, down);
        space_set_gdesc(space, gdesc);
	      space_set_adesc(space, "To be written");
      	if(game_add_space(game, space) == ERROR) status = ERROR;
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


/**
* @brief reads the objects from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 21/10/2016
* @param Game* and a char* (filename)
* @return OK if the objects were successfuly read
*/

STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL; /*File to read*/
  char line[WORD_SIZE] = ""; /*Line read*/
  char symbol = 'E'; /*Symbol of the objects*/
  char* toks = NULL; /*String for tokenization*/
  Id object_id = NO_ID, space_id = NO_ID; /*Ids for the object*/
  Object* object = NULL; /*Object pointer*/
  STATUS status = OK; /*Status set to OK*/
  int num_objects = 0; /*Number of objects read*/
  char desc[WORD_SIZE+1]= ""; /*Description of the object*/

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
      toks = strtok(NULL, " |");
      strcpy(desc, toks);

#ifdef DEBUG 
      printf("Leido: %ld|%ld|%c|%s\n", object_id, space_id, symbol, desc);
#endif

      object = object_create(object_id);
      if (object != NULL) {
        object_set_symbol(object, symbol);
        object_set_location(object, space_id);
        object_set_name(object, desc);
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


/**
* @brief reads the links from a file
* @author 
* @date 08/10/2016
* @param Game* and a char* (filename)
* @return OK if the links were successfuly read
*/

STATUS game_load_links(Game* game, char* filename){
  FILE* file = NULL; /*File to read*/
  char line[WORD_SIZE] = ""; /*Line read*/
  Id link_id = NO_ID; /*Id for the link*/
  Id con1_id = NO_ID, con2_id = NO_ID; /*Id for the conections*/
  char* toks = NULL; /*String for tokenization*/
  Link* link = NULL; /*Link pointer*/
  STATUS status = OK; /*Status set to OK*/
  char desc[WORD_SIZE+1]= ""; /*Name of the link*/

  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      link_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks);
      toks = strtok(NULL, "|");
      con1_id = atol(toks);
      toks = strtok(NULL, "|");
      con2_id = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld\n", link_id, desc, con1_id, con2_id);
#endif
      link = link_create(link_id);
      if (link != NULL) {
        link_set_name(link, desc);
        link_set_conection1(link, con1_id);
        link_set_conection2(link, con2_id);
        game_add_link(game, link);
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

/**
* @brief reads the player from a file
* @author Óscar Pinto Santamaría
* @date 16/10/2016
* @param Game* and a char* (filename)
* @return OK if the player were successfuly read
*/

STATUS game_load_player(Game* game, char* filename){
  FILE* file = NULL; /*File to read*/
  Id id;
  char name[WORD_SIZE +1];
  Id location; 
  char *toks=NULL;
  Player *player;
  char line[WORD_SIZE];
  STATUS status=OK;

  if(!game || !filename)
    return ERROR;

  file = fopen(filename, "r");
    if(file == NULL)
      return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      #ifdef DEBUG 
      printf("Leido: %ld|%s|%ld\n", id, name, location);
      #endif
      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_location(player, location);
        game_add_player(game, player);
      }
    }
  }

if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
return status;
}

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

  fprintf(f, "#s:%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%s|%s|%s\n", 
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

  STATUS ret1, ret2, ret3, ret4;

  if(!game || !path)
    return ERROR;

  ret1 = game_load_spaces(game, path);

  ret2 = game_load_objects(game, path);

  ret3 = game_load_links(game, path);

  ret4 = game_load_player(game, path);

  if(ret1 == ret2 && ret2 == ret3 && ret3 == ret4 && ret4 == OK)
    return OK;

  return ERROR;
}
