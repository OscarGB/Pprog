/**
 * @brief It implements the game interface for each command
 * @file game.c
 * @author Óscar Gómez, José Ignacio Gómez, Óscar Pinto, Andrea Ruiz
 * @version 1.0
 * @date 09/11/2016
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <alloca.h>
#include "game.h"
#include "player.h"
#include "object.h"
#include "game_management.h"
#include "die.h"
#include "link.h"
#include "graphics.h"

#ifdef __WINDOWS_BUILD__ /*In case we are working on Windows*/
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct _Game {
  Player* player; /*!< Pointer to Player Structure */
  Object* object[MAX_IDS + 1]; /*!< Array of pointers to Object Structure */
  int num_objects; /*!< Number of objects of the Game */
  Space* spaces[MAX_SPACES]; /*!< Array of pointers to Space Structure */
  Die* die; /*!< Pointer to Die Structure */
  Link *links[MAX_LINKS]; /*!< Array of pointers to Link Structure */
  int num_links; /*!<Number of links */
  char desc[WORD_SIZE+1]; /* !< For inspect command*/
  int turns; /* !<Number of turns passed */
};/*!< Game structure*/

/*
* brief List of callbacks for each command in the game 
*/

STATUS callback_UNKNOWN(Game* game, Dialogue* dia, Graphics* gra);
STATUS callback_QUIT(Game* game, Dialogue* dia, Graphics* gra);
STATUS callback_NEXT(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_BACK(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_JUMP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_UP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_BACK(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_DROP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_PICK(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_ROLL(Game* game, Command* cmd);
STATUS callback_INSPECT(Game* game, Command* cmd, Dialogue* dia, Graphics* gra);
STATUS callback_GO(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_TURNON(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_TURNOFF(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_OPEN(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects);
STATUS callback_SAVE(Game* game, Command* cmd, Dialogue* dia, Graphics* gra);
STATUS callback_LOAD(Game* game, Command* cmd, Dialogue* dia, Graphics* gra);


/*
* Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);

STATUS game_add_object(Game* game, Object* object);
STATUS game_set_object_location(Game* game, Id id_s, Id id_o);
Id     game_get_object_location(Game* game, char *symbol);

STATUS print_player_save(FILE *f, Player *player);
STATUS print_space_save(FILE *f, Space* space);
STATUS print_link_save(FILE *f, Link *link);
STATUS print_object_save(FILE *f, Object *object);


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
Game* game_init(Game* game) {
  int i; /* !< Variable used for loops*/

  game = (Game *) malloc (sizeof(Game));
  if(!game)
    return NULL;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  
  /*Creating player*/
  game->player = player_create(1);
  if(!game->player){
    game_destroy(game);
    return NULL;
  }

  for (i = 0; i < MAX_IDS; i++){
    game->object[i] = NULL;
  }

  game->num_objects = 0;
  game->num_links = 0;
  game->turns = 0;

  /*Creating die*/
  game->die = die_create(1, DIE_FACES);
  if(!game->die){ /*Error case*/
    player_destroy(game->player);
    game_destroy(game);
    return NULL;
  }

  for (i = 0; i < MAX_LINKS; i++){
    game->links[i] = NULL;
  }

  game->desc[0]='\0';

  return game;
}

/**
* @brief it creates a game table loading spaces from a file
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer and a filename
* @return OK if it was successfuly initialized
*/
STATUS game_init_from_file(Game* game, char* filename) {
  Id aux;
  /*Init the game*/
  /*if (game_init(game) == ERROR){
    return ERROR;
  }*/

  /*Load objects from file*/
  if (game_load_objects(game, filename) == ERROR) {
    return ERROR;
  }

  /*Load spaces from file*/
  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /*Load links from file*/
  if(game_load_links(game, filename) == ERROR) {
    return ERROR;
  }

  /*Set player in the initial position*/
  aux = game_get_space_id_at(game, 0);
  game_set_player_location(game, aux);
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
    int i = 0; /*Variable used for loops*/

    /*Destroy all the spaces*/
    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
      space_destroy(game->spaces[i]);
    }

    /*Destroy the player*/
    if(game->player != NULL){
      player_destroy(game->player);
    }

    /*Destroy all the objects*/
    if(game->object != NULL){
      for (i = 0; i < game->num_objects; i++){
        object_destroy(game->object[i]);
      }
    }

    /*Destroy the die*/
    if(game->die != NULL){
      die_destroy(game->die);
    }

    /*Destroy all the links*/
    for(i=0; i < MAX_LINKS; i++){
      link_destroy(game->links[i]);
    }

    free(game);
        
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
    int i = 0; /* !< Variable used for loops*/

    if (game == NULL || space == NULL) {
        return ERROR;
    }

    /*Check the first empty position*/
    while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
        i++;
    }

    /*Check if there are more spaces than positions*/
    if (i >= MAX_SPACES) {
        return ERROR;
    }

    /*Set the space to the proper position*/
    game->spaces[i] = space;

    return OK;
}

/**
* @brief Adds a link to the game
* @author Óscar Gómez
* @date 4/11/2016
* @param Game *game (The game to change)
* @param Link *link (The link to add)
* @return Status (OK if it was added, ERROR if wasn't)
*/
STATUS game_add_link(Game *game, Link* link){
  int i = 0; /* !<Variable used for loops*/

  if(game == NULL || link == NULL){
    return ERROR;
  }

  /*Check the first empty position*/
  while((i < (4 * MAX_SPACES)) && (game->links[i] != NULL)){
    i++;
  }

  /*Check if there are more links than positions*/
  if(i >= (4 * MAX_SPACES)){
    return ERROR;
  }

  /*Set the link to the proper position*/
  game->links[i] = link;
  game->num_links ++;

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
    if (object == NULL || game == NULL) {
        return ERROR;
    }
    

    /*Checks if there are too much objects*/
    if(game->num_objects >= MAX_IDS){
      return ERROR;
    }


    /*Sets the object*/
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
* @date 29/09/2016
* @param game pointer
* @param Id space id
* @return Space pointer with that id
*/
Space* game_get_space(Game* game, Id id){
    int i = 0; /* !< Variable used for loops*/

    if (id == NO_ID) {
      return NULL;
    }
    
    /*Checks all the positions for the space*/
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
      if (id == space_get_id(game->spaces[i])){
      	return game->spaces[i];
      }
    }
    
    /*If theres no space with the given Id*/
    return NULL;
}

/**
* @brief It gets the object from a given id
* @author Andrea Ruiz
* @date 17/12/2016
* @param game pointer
* @param Id space id
* @return Object pointer with that id
*/
Object * game_get_object(Game* game, Id id){
    int i = 0; /* !< Variable used for loops*/

    if (id == NO_ID) {
      return NULL;
    }
    
    /*Checks all the positions for the object*/
    for (i = 0; i < MAX_SPACES && game->object[i] != NULL; i++) {
      if (id == object_get_id(game->object[i])){
      	return game->object[i];
      }
    }
    
    /*If theres no object with the given Id*/
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
* @param the id of the object
* @return OK if it was set
*/
STATUS game_set_object_location(Game* game, Id id_s, Id id_o) {

    int i; /* !< Variable used for loops*/

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
* @brief Gets the location of the player
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return The id of the player location
*/
Id game_get_player_location(Game* game) {

    return player_get_location(game->player);
}

/**
* @brief Adds a player pointer to the gme Player field
* @author Óscar Pinto Santamaría
* @date 16/12/2016
* @param Game* game, Player* player
* @return OK or ERROR
*/

STATUS game_add_player(Game* game, Player* player){
	if(!game || !player)
		return ERROR;

	game->player = player;
	if(!game->player)
		return ERROR;

	return OK;
}


/**
* @brief Gets the location of an object
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param the symbol of the object
* @return The id of the object location
*/
Id game_get_object_location(Game* game, char *symbol) {
    int i; /* !< Variable used for loops*/

    if(strlen(symbol) == 1){
      for(i = 0; i < game->num_objects; i++){
        if(object_get_symbol(game->object[i]) == symbol[0]){
          return object_get_location(game->object[i]);
        }
      }
    }
    else if(strlen(symbol) > 1){
      for(i = 0; i < game->num_objects; i++){
        if(strcmp(object_get_name(game->object[i]), symbol) == 0){
          return object_get_location(game->object[i]);
        }
      }
    }
    /*If theres no object with that symbol*/
    return NO_ID;
}

/**
* @brief gets the name of the objects in player's location
* @author José Ignacio Gómez
* @date 18/12/2016
* @param game pointer
* @return string with the name of the objects
*/
char** game_get_objects_name(Game* game, char** objects){
  int i, j = 0;

  for (i = 0; i < game->num_objects; i++){
    if (object_get_location(game->object[i]) == game_get_player_location(game)){
      objects[j] = object_get_name(game->object[i]);
      j++;
    }
  }
  objects[j] = NULL;

  return (char**) objects;
}



/**
* @brief it calls different callbacks depending on the written command
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Command cmd
* @return OK if it was updated
*/

STATUS game_update(Game* game, Command *cmd, Dialogue* dia, Graphics* gra) {
  char *objects[MAX_IDS];

  game->turns++;
  switch (command_get_cmd(cmd)) { /*Switch for the command value*/
  case UNKNOWN:
    return callback_UNKNOWN(game, dia, gra);
  case QUIT:
    return callback_QUIT(game, dia, gra);
  case PICK:
    return callback_PICK(game, cmd, dia, gra, objects);
  case DROP:
    return callback_DROP(game, cmd, dia, gra, objects);
  case ROLL:
    return callback_ROLL(game, cmd);
  case INSPECT:
    return callback_INSPECT(game, cmd, dia, gra);
  case GO:
    return callback_GO(game, cmd, dia, gra, objects);
  case TURNON:
    return callback_TURNON(game, cmd, dia, gra, objects); 
  case TURNOFF:
    return callback_TURNOFF(game, cmd, dia, gra, objects);
  case OPEN:
    return callback_OPEN(game, cmd, dia, gra, objects);
  case SAVE:
    game->turns--;
    return callback_SAVE(game, cmd, dia, gra);
  case LOAD:
  	return callback_LOAD(game, cmd, dia, gra);
  case NO_CMD:
    break;
  default: /*We must never arrive here*/
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
  int i = 0; /* !< Variable used for loops*/
  
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
* @author José Ignacio Gómez, Óscar Gómez, Andrea Ruiz
* @date 29/09/2016
* @param game pointer
* @return void
*/
void game_print_screen(Game* game, Graphics* gra){
  Id id_act = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID; /* !< Ids for locations*/
  Id id_swest = NO_ID, id_nwest = NO_ID, id_neast = NO_ID, id_seast = NO_ID;
  Id id_l_back = NO_ID, id_l_next = NO_ID, id_l_east = NO_ID, id_l_west = NO_ID; /*!< Ids of the links*/
  Id id_l_swest = NO_ID, id_l_nwest = NO_ID, id_l_neast = NO_ID, id_l_seast = NO_ID;
  Space* space_act = NULL; /* !< Pointers to spaces needed to print the game*/
  Space* space_north = NULL;
  Space* space_south = NULL;
  Space* space_east = NULL;
  Space* space_west = NULL;
  Space* space_nwest = NULL;
  Space* space_swest = NULL;
  Space* space_neast = NULL;
  Space* space_seast = NULL;
  char print[(SPACE_SIZE_X * SPACE_SIZE_Y) + 1];
  int i; /* !< loops, last rolled value*/

  print[0] = '\0';

  if(!gra || !game){
    return;
  }

  graphics_clear(gra, 0);
  
  id_act = game_get_player_location(game);

  if (id_act == NO_ID){
    return;
  }
  
  space_act = game_get_space(game, id_act);
  id_l_back = space_get_north(space_act);
  id_l_next = space_get_south(space_act);
  id_l_east = space_get_east(space_act);
  id_l_west = space_get_west(space_act);

  /*Search for the id of the back space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_back){
      if(link_get_conection1(game->links[i]) == id_act){
        id_north = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_north = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_north = NO_ID;
    }
  }

  /*Search for the id of the next space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_next){
      if(link_get_conection1(game->links[i]) == id_act){
        id_south
     = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_south
     = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_south
   = NO_ID;
    }
  }

  /*Search for the id of the east space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_east){
      if(link_get_conection1(game->links[i]) == id_act){
        id_east = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_east = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_east = NO_ID;
    }
  }

  /*Search for the id of the west space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_west){
      if(link_get_conection1(game->links[i]) == id_act){
        id_west = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_west = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_west = NO_ID;
    }
  }

  space_west = game_get_space(game, id_west);
  space_east = game_get_space(game, id_east);
  space_north = game_get_space(game, id_north);
  space_south = game_get_space(game, id_south
);

  /*Search for the north west space*/
  id_l_nwest = space_get_north(space_west);
  if(id_l_nwest == NO_ID){
    id_l_nwest = space_get_west(space_north);
  } 
  if(id_l_nwest != NO_ID){
    for(i=0; i<(4*MAX_SPACES); i++){
      if(link_get_id(game->links[i]) == id_l_nwest){
        if(link_get_conection1(game->links[i]) == id_west || link_get_conection1(game->links[i]) == id_north){
          id_nwest = link_get_conection2(game->links[i]);
          break;
        }
        else{
          id_nwest = link_get_conection1(game->links[i]);
          break;
        }
      }
      else{
        id_nwest = NO_ID;
      }
    }
  }

  /*Search for the north east space*/
  id_l_neast = space_get_north(space_east);
  if(id_l_neast == NO_ID){
    id_l_neast = space_get_east(space_north);
  } 
  if(id_l_neast != NO_ID){
    for(i=0; i<(4*MAX_SPACES); i++){
      if(link_get_id(game->links[i]) == id_l_neast){
        if(link_get_conection1(game->links[i]) == id_east || link_get_conection1(game->links[i]) == id_north){
          id_neast = link_get_conection2(game->links[i]);
          break;
        }
        else{
          id_neast = link_get_conection1(game->links[i]);
          break;
        }
      }
      else{
        id_neast = NO_ID;
      }
    } 
  }

  /*Search for the south east space*/
  id_l_seast = space_get_south(space_east);
  if(id_l_seast == NO_ID){
    id_l_seast = space_get_east(space_south);
  } 
  if(id_l_seast != NO_ID){
    for(i=0; i<(4*MAX_SPACES); i++){
      if(link_get_id(game->links[i]) == id_l_seast){
        if(link_get_conection1(game->links[i]) == id_east || link_get_conection1(game->links[i]) == id_south){
          id_seast = link_get_conection2(game->links[i]);
          break;
        }
        else{
          id_seast = link_get_conection1(game->links[i]);
          break;
        }
      }
      else{
        id_seast = NO_ID;
      }
    } 
  }

  /*Search for the south west space*/
  id_l_swest = space_get_south(space_west);
  if(id_l_swest == NO_ID){
    id_l_swest = space_get_west(space_south);
  } 
  if(id_l_swest != NO_ID){
    for(i=0; i<(4*MAX_SPACES); i++){
      if(link_get_id(game->links[i]) == id_l_swest){
        if(link_get_conection1(game->links[i]) == id_west || link_get_conection1(game->links[i]) == id_south){
          id_swest = link_get_conection2(game->links[i]);
          break;
        }
        else{
          id_swest = link_get_conection1(game->links[i]);
          break;
        }
      }
      else{
        id_swest = NO_ID;
      }
    }
  }


  space_nwest = game_get_space(game, id_nwest);
  space_neast = game_get_space(game, id_neast);
  space_seast = game_get_space(game, id_seast);
  space_swest = game_get_space(game, id_swest);
  
  if (id_north != NO_ID) {
    if(space_get_light(space_north) == TRUE){
      print_in_zone(gra, PLAYGROUND, N, space_get_gdesc(space_north));
    }
    else{
      print_in_zone(gra, PLAYGROUND, N, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, N, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_act != NO_ID) {
    if(space_get_light(space_act) == TRUE){
      strcpy(print, space_get_gdesc(space_act));
      print[27] = ':';
      print[28] = ')';
      print_in_zone(gra, PLAYGROUND, C, print);
    }
    else{
      print_in_zone(gra, PLAYGROUND, C, "+------------+|            ||            ||     :)     ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, C, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }
  
  if (id_south != NO_ID) {
    if(space_get_light(space_south) == TRUE){
      print_in_zone(gra, PLAYGROUND, S, space_get_gdesc(space_south));
    }
    else{
      print_in_zone(gra, PLAYGROUND, S, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, S, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_east != NO_ID) {
    if(space_get_light(space_east) == TRUE){
      print_in_zone(gra, PLAYGROUND, E, space_get_gdesc(space_east));
    }
    else{
      print_in_zone(gra, PLAYGROUND, E, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, E, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_west != NO_ID) {
    if(space_get_light(space_west) == TRUE){
      print_in_zone(gra, PLAYGROUND, W, space_get_gdesc(space_west));
    }
    else{
      print_in_zone(gra, PLAYGROUND, W, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, W, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }
  
  if (id_nwest != NO_ID) {
    if(space_get_light(space_nwest) == TRUE){
      print_in_zone(gra, PLAYGROUND, NW, space_get_gdesc(space_nwest));
    }
    else{
      print_in_zone(gra, PLAYGROUND, NW, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, NW, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_neast != NO_ID) {
    if(space_get_light(space_neast) == TRUE){
      print_in_zone(gra, PLAYGROUND, NE, space_get_gdesc(space_neast));
    }
    else{
      print_in_zone(gra, PLAYGROUND, NE, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, NE, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_swest != NO_ID) {
    if(space_get_light(space_swest) == TRUE){
      print_in_zone(gra, PLAYGROUND, SW, space_get_gdesc(space_swest));
    }
    else{
      print_in_zone(gra, PLAYGROUND, SW, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, SW, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }

  if (id_seast != NO_ID) {
    if(space_get_light(space_seast) == TRUE){
      print_in_zone(gra, PLAYGROUND, SE, space_get_gdesc(space_seast));
    }
    else{
      print_in_zone(gra, PLAYGROUND, SE, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, SE, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }


  graphics_refresh(gra);

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
* @brief callback for an unknown parameter
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_UNKNOWN(Game* game, Dialogue* dia, Graphics* gra) {

  dialogue_generic(dia, OK, NULL, gra);
  return OK;
}


/**
* @brief callback for quitting the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_QUIT(Game* game, Dialogue* dia, Graphics* gra) {
  if(!game || !dia || !gra) return ERROR;

  dialogue_generic(dia, OK, NULL, gra);
  return OK;
}


/**
* @brief callback for "next" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_NEXT(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects) {
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, south_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  STATUS result;
  
  if(!game || !dia || !gra || !cmd) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      link_id = space_get_south(game->spaces[i]);
      for(j = 0; j < (4 * MAX_SPACES); j++){
        if(link_get_id(game->links[j]) == link_id){
          if(link_get_conection1(game->links[j]) == current_id){
            south_id = link_get_conection2(game->links[j]);
            break;
          }
          else{
            south_id = link_get_conection1(game->links[j]);
            break;
          }
        }
        else{
          south_id = NO_ID;
        }
      }
      if (south_id != NO_ID) {

        result = game_set_player_location(game, south_id);
        return result;
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}


/**
* @brief callback for "back" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_BACK(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects) {
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, north_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  STATUS result;
  
  if(!game || !dia || !gra || !cmd) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      link_id = space_get_north(game->spaces[i]);
      for(j = 0; j < (4 * MAX_SPACES); j++){
        if(link_get_id(game->links[j]) == link_id){
          if(link_get_conection1(game->links[j]) == current_id){
            north_id = link_get_conection2(game->links[j]);
            break;
          }
          else{
            north_id = link_get_conection1(game->links[j]);
            break;
          }
        }
        else{
          north_id = NO_ID;
        }
      }
      if (north_id != NO_ID) {
        result = game_set_player_location(game, north_id);
        return result;
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}

/**
* @brief callback for "up" instruction
* @author Andrea Ruiz
* @date 2/12/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_UP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){

  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, up_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Space id*/
  STATUS result;
  
  if(!game || !dia || !gra || !cmd) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      link_id = space_get_up(game->spaces[i]);
      for(j = 0; j < (4 * MAX_SPACES); j++){
        if(link_get_id(game->links[j]) == link_id){
          if(link_get_conection1(game->links[j]) == current_id){
            up_id = link_get_conection2(game->links[j]);
            break;
          }
          else{
            up_id = link_get_conection1(game->links[j]);
            break;
          }
        }
        else{
          up_id = NO_ID;
        }
      }
      if (up_id != NO_ID) {
        result = game_set_player_location(game, up_id);
        return result;
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;

}

/**
* @brief callback for "down" instruction
* @author Andrea Ruiz
* @date 2/12/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_DOWN(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, down_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Space id*/
  STATUS result;
  
  if(!game || !dia || !gra || !cmd) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      link_id = space_get_down(game->spaces[i]);
      for(j = 0; j < (4 * MAX_SPACES); j++){
        if(link_get_id(game->links[j]) == link_id){
          if(link_get_conection1(game->links[j]) == current_id){
            down_id = link_get_conection2(game->links[j]);
            break;
          }
          else{
            down_id = link_get_conection1(game->links[j]);
            break;
          }
        }
        else{
          down_id = NO_ID;
        }
      }
      if (down_id != NO_ID) {
        result = game_set_player_location(game, down_id);
        return result;
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}

/**
* @brief callback for "jump" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_JUMP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, east_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  STATUS result;
  
  if(!game || !dia || !gra || !cmd) return ERROR;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return ERROR;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      link_id = space_get_east(game->spaces[i]);
      for(j = 0; j < (4 * MAX_SPACES); j++){
        if(link_get_id(game->links[j]) == link_id){
          if(link_get_conection1(game->links[j]) == current_id){
            east_id = link_get_conection2(game->links[j]);
            break;
          }
          else{
            east_id = link_get_conection1(game->links[j]);
            break;
          }
        }
        else{
          east_id = NO_ID;
        }
      }
      if (east_id != NO_ID) {
        result = game_set_player_location(game, east_id);
        return result;
      }
      else{
        return ERROR;
      }
    }
  }
  return ERROR;
}


/**
* @brief callback for "drop" instruction
* @author José Ignacio Gómez, Óscar Gómez, Andrea Ruiz
* @date 29/09/2016
* @param game pointer
* @param char symbol to drop
* @return OK if it went ok
*/
STATUS callback_DROP(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  Object* object = NULL; /* !< Object that will be dropped*/
  Id object_id = NO_ID;
  Id current_id; /* !< Id of the current space*/
  int i;
  STATUS result;
  char *symbol = NULL; /*!< Variable used for storing the command*/
  symbol = command_get_symbol(cmd); 

  if(!game || !dia || !gra || !cmd) return ERROR;

  if(strlen(symbol) == 1){
    for(i=0; i< game->num_objects; i++){ /*!< Seeing if the symbol is associated to an object */
    	if(object_get_symbol(game->object[i]) == symbol[0]){
    		object_id = object_get_id(game->object[i]);
      	object = game->object[i];
    		break;
    	}
    }
  }
  else if(strlen(symbol) > 1){
    for(i=0; i< game->num_objects; i++){ /*!< Seeing if the symbol is associated to an object */
      if(strcmp(object_get_name(game->object[i]), symbol) == 0){
        object_id = object_get_id(game->object[i]);
        object = game->object[i];
        break;
      }
    }
  }

  if(object_id == NO_ID || !object){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  if(player_drop_object(game->player, object_id) == FALSE){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  if(strlen(symbol) == 1){
    if(object_get_symbol(object) != symbol[0]){
      player_pick_object(game->player, object_id);
      objects = game_get_objects_name(game, objects);
      dialogue_generic(dia, ERROR, objects, gra);
      return ERROR;
    }
  }
  else if(strlen(symbol) > 1){
    if(strcmp(object_get_name(object), symbol) != 0){
      player_pick_object(game->player, object_id);
      objects = game_get_objects_name(game, objects);
      dialogue_generic(dia, ERROR, objects, gra);
      return ERROR;
    }
  }

  current_id = game_get_player_location(game);

  result = game_set_object_location(game, current_id, object_get_id(object));
  objects = game_get_objects_name(game, objects);
  dialogue_generic(dia, result, objects, gra);

  return result;
}


/**
* @brief callback for "pick" instruction
* @author José Ignacio Gómez, Óscar Gómez, Andrea Ruiz
* @date 29/09/2016
* @param game pointer
* @param the symbol to pick
* @return OK if it went ok
*/
STATUS callback_PICK(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/
  char *symbol = NULL; /*!< Variable used for storing the command*/

  if(!game || !dia || !gra || !cmd) return ERROR;

  symbol = command_get_symbol(cmd);

  if(strcmp(symbol, "\0") == 0){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_pick_object(game->player, object_get_id(object)) != FALSE){
          object_set_location(object, PLAYER_OBJ);
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, OK, objects, gra); 
          return OK;
        }
      }  
    }

  }
  else if(strlen(symbol) > 1){
    for(i = 0; i < game->num_objects; i++){

      if(strcmp(object_get_name(game->object[i]), symbol) == 0){
        object = game->object[i];

        if(player_pick_object(game->player, object_get_id(object)) != FALSE){
          object_set_location(object, PLAYER_OBJ); 
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, OK, objects, gra);
          return OK;
        }
      }  
    }
  }

  objects = game_get_objects_name(game, objects);
  dialogue_generic(dia, ERROR, objects, gra);
  return ERROR;
}


/**
* @brief callback for "roll" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_ROLL(Game* game, Command* cmd){
    int res; /* !< Result of the rolled die*/

    res = die_roll(game->die);
    if(res < 1 || res > 6) return ERROR;

    return OK;
}

/**
* @brief callback for "inspect" instruction
* @author Óscar Pinto, Andrea Ruiz
* @date 04/11/2016
* @param game pointer
* @param symbol to inspect
* @return OK if it went ok
*/
STATUS callback_INSPECT(Game* game, Command* cmd, Dialogue* dia, Graphics* gra){

    int i, j;/* !< Variable used for loops*/
    Object *obj; /* !<Variable used for storing the player's object*/
    Id player_location = NO_ID; /* !< Locations of the player and object*/
    Space *space; /*!<Variable used for storing auxiliary spaces*/
    char *symbol = NULL; /*!< Variable used for storing the command*/
    Inventory* inventory = NULL;
    Id* ids = NULL;
    char **invobjs;

    invobjs = (char **) malloc(sizeof(char *) * (1 + game->num_objects));
    for(i = 0; i >= game->num_objects; i++){
      invobjs[i] = (char*) malloc(sizeof(char)*MAX_ADESC);
      invobjs[i][0] = '\0';
    }

    symbol = command_get_symbol(cmd);

    obj = NULL;
    
    if(!game || !cmd || !dia || !gra){
      dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
      return ERROR;
    }
    if(strcmp(symbol, "E") == 0){
      dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
      return ERROR;
    }

    player_location = game_get_player_location(game);
    if(player_location == NO_ID){
      dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
      return ERROR;
    }

    if(strlen(symbol) == 1){

      if(symbol[0] == 's' || symbol[0] == 'S'){ /*!< Inspecting space */
          	for(i=0; i < MAX_SPACES; i++){
          		if(player_location == space_get_id(game->spaces[i])){
                if(space_get_light(game->spaces[i]) != FALSE){
          		    strcpy(invobjs[0], space_get_adesc(game->spaces[i]));
          		    dialogue_inspect(dia, OK, invobjs, gra, SPACE);
                  return OK;	
                }
                else{
                  dialogue_inspect(dia, ERROR, invobjs, gra, SPACE);
                  return OK;
                }
          		}
          	}
            dialogue_inspect(dia, ERROR, invobjs, gra, SPACE);
            return ERROR;
      }
      else{ /*!< Inspecting an object */
  	     
         for(i=0; i< game->num_objects; i++){ /*!< If player has the object or they're in the same field */
  		      if(object_get_location(game->object[i]) == player_location || object_get_location(game->object[i]) == PLAYER_OBJ){
  			       if(object_get_symbol(game->object[i]) == symbol[0])
  				        obj = game->object[i];
  		      }
          }

          if(!obj){
            dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
            return ERROR;
          }

    		  space = game_get_space(game, player_location); /*Get the space where the object is*/

		      if(space_get_light(space) == FALSE){
		        dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
            return ERROR;
          }
          strcpy(game->desc, space_get_adesc(space));
          strcpy(invobjs[0], game->desc);
          dialogue_inspect(dia, OK, invobjs, gra, OBJECT);
          return OK;
      }
    }
    else if(strlen(symbol) > 1){
      if(strcmp(symbol, "space") == 0 || strcmp(symbol, "Space") == 0){ /*!< Inspecting space */
          for(i=0; i<MAX_SPACES && game->spaces[i]; i++){
            if(player_location==space_get_id(game->spaces[i])){
                if(space_get_light(game->spaces[i]) == TRUE){
                  strcpy(game->desc, space_get_adesc(game->spaces[i]));
                  strcpy(invobjs[0], game->desc);
                  dialogue_inspect(dia, OK, invobjs, gra, SPACE);
                  return OK;  
                }  
            }
          }
          dialogue_inspect(dia, ERROR, invobjs, gra, SPACE);
          return ERROR;
      }
      else if(strcmp(symbol, "inventory") == 0 || strcmp(symbol, "Inventory") == 0){ /*!< Inspecting inventory*/
        inventory = player_get_inventory(game->player);
        if(!inventory){ 
          dialogue_inspect(dia, ERROR, invobjs, gra, INVENTORY);
          return ERROR;
        }
        ids = inventory_get_ids(player_get_inventory(game->player));
        if(!ids){
          dialogue_inspect(dia, ERROR, invobjs, gra, INVENTORY);
          return ERROR;
        }
        for(i = 0; i < MAX_IDS; i++){
          if(ids[i] == NO_ID){
            break;
          }
          for(j = 0; j < game->num_objects; i++){
            if(object_get_id(game->object[j]) == ids[i]){
              invobjs[i] = object_get_name(game->object[i]);
              break;
            }
          }
        }
        dialogue_inspect(dia, OK, invobjs, gra, INVENTORY);
        return OK;
      }
      else{ /*!< Inspecting an object */
         for(i=0; i< game->num_objects; i++){ /*!< If player has the object or they're in the same field */
            if(object_get_location(game->object[i]) == player_location || object_get_location(game->object[i]) == PLAYER_OBJ){
               if(strcmp(object_get_name(game->object[i]), symbol) == 0)
                  obj = game->object[i];
            }
          }

          if(!obj) {
            dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
            return ERROR;
          }
	
		      space = game_get_space(game, player_location); /*Get the space where the object is*/

    		  if(space_get_light(space) == FALSE){
            dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
            return ERROR;
          }
          strcpy(game->desc, space_get_adesc(space));
          strcpy(invobjs[0], game->desc);
          dialogue_inspect(dia, OK, invobjs, gra, OBJECT);
          return OK;
      }
    }

  dialogue_inspect(dia, ERROR, invobjs, gra, OBJECT);
  return ERROR;
} 

/**
* @brief callback for "go" instruction
* @author Andrea Ruiz
* @date 08/11/2016
* @param game pointer
* @param symbol to inspect (direction)
* @return OK if it went ok
*/

STATUS callback_GO(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){

  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, west_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  char *symbol = NULL; /*!< Variable used for storing the command*/
  STATUS result;

  if(!game || !dia || !gra || !cmd){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  symbol = command_get_symbol(cmd);


  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  if(strlen(symbol) == 1){
    if(symbol[0] == 'n'){ /* Go north */ 
	   result = callback_BACK(game, cmd, dia, gra, objects);
     objects = game_get_objects_name(game, objects);
     dialogue_generic(dia, result, objects, gra);

     return result;
    }

    if(symbol[0] == 's'){ /* Go south */ 
	   result = callback_NEXT(game, cmd, dia, gra, objects);
     objects = game_get_objects_name(game, objects);
     dialogue_generic(dia, result, objects, gra);

     return result;
    }

  if(symbol[0] == 'u'){ /* Go up */
   result = callback_UP(game, cmd, dia, gra, objects);
   objects = game_get_objects_name(game, objects);
   dialogue_generic(dia, result, objects, gra);

     return result; 
  }

  if(symbol[0] == 'd'){ /* Go down */
   result = callback_DOWN(game, cmd, dia, gra, objects);
   objects = game_get_objects_name(game, objects);
   dialogue_generic(dia, result, objects, gra);

     return result;
  }

  if(symbol[0] == 'e'){ /* Go east */ 
   result = callback_JUMP(game, cmd, dia, gra, objects);
   objects = game_get_objects_name(game, objects);
   dialogue_generic(dia, result, objects, gra);

   return result;
  }

  if(symbol[0] == 'w'){ /* Go west */

    	for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    		current_id = space_get_id(game->spaces[i]);
    	    	if (current_id == space_id) {
          			link_id = space_get_west(game->spaces[i]);
    	        	for(j = 0; j < (4 * MAX_SPACES); j++){
            			if(link_get_id(game->links[j]) == link_id){
    	        			if(link_get_conection1(game->links[j]) == current_id){
                					west_id = link_get_conection2(game->links[j]);
                					break;
              				}
              				else{
                					west_id = link_get_conection1(game->links[j]);
                					break;
              				}
            			}
            			else{
    				        west_id = NO_ID;
            			}
          			}	
    	      		if (west_id != NO_ID) {

    			        result = game_set_player_location(game, west_id);
                  objects = game_get_objects_name(game, objects);
                  dialogue_generic(dia, result, objects, gra);

                  return result;
          			}
    			      else{
                  objects = game_get_objects_name(game, objects);
                  dialogue_generic(dia, ERROR, objects, gra);
    			        return ERROR;
          			}
            	}
      	} 	

      }

    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

  else if(strlen(symbol) > 1){
      if(strcmp(symbol, "north") == 0){ /* Go north */ 
       result = callback_BACK(game, cmd, dia, gra, objects);
       objects = game_get_objects_name(game, objects);
       dialogue_generic(dia, result, objects, gra);

       return result;
      }

      if(strcmp(symbol, "south") == 0){ /* Go south */ 
       result = callback_NEXT(game, cmd, dia, gra, objects);
       objects = game_get_objects_name(game, objects);
       dialogue_generic(dia, result, objects, gra);

       return result;
      }

	  if(strcmp(symbol, "up") == 0){ /* Go up */ 
       result = callback_UP(game, cmd, dia, gra, objects);
       objects = game_get_objects_name(game, objects);
       dialogue_generic(dia, result, objects, gra);

       return result;
      }

	  if(strcmp(symbol, "down") == 0){ /* Go down */ 
       result = callback_DOWN(game, cmd, dia, gra, objects);
       objects = game_get_objects_name(game, objects);
       dialogue_generic(dia, result, objects, gra);

       return result;
      }

    if(strcmp(symbol, "east") == 0){ /* Go east */ 
     result = callback_JUMP(game, cmd, dia, gra, objects);
     objects = game_get_objects_name(game, objects);
     dialogue_generic(dia, result, objects, gra);

     return result;
    }

    if(strcmp(symbol, "west") == 0){ /* Go west */

        for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
          current_id = space_get_id(game->spaces[i]);
              if (current_id == space_id) {
                  link_id = space_get_west(game->spaces[i]);
                  for(j = 0; j < (4 * MAX_SPACES); j++){
                    if(link_get_id(game->links[j]) == link_id){
                      if(link_get_conection1(game->links[j]) == current_id){
                            west_id = link_get_conection2(game->links[j]);
                            break;
                        }
                        else{
                            west_id = link_get_conection1(game->links[j]);
                            break;
                        }
                    }
                    else{
                      west_id = NO_ID;
                    }
                  } 
                  if (west_id != NO_ID) {
                    result = game_set_player_location(game, west_id);
                    objects = game_get_objects_name(game, objects);
                    dialogue_generic(dia, result, objects, gra);

                    return result;
                  }
                  else{
                    objects = game_get_objects_name(game, objects);
                    dialogue_generic(dia, ERROR, objects, gra);
                    return ERROR;
                  }
                }
          } 

    }
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }

objects = game_get_objects_name(game, objects);
dialogue_generic(dia, ERROR, objects, gra);
return ERROR;
}

STATUS callback_TURNON(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/
  char *symbol = NULL; /*!< Variable used for storing the command*/

  if(!game || !dia || !gra || !cmd) return ERROR;

  symbol = command_get_symbol(cmd);

  if(strcmp(symbol, "\0") == 0){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }


  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          if(object_turnoff(object) == OK){
            objects = game_get_objects_name(game, objects);
            dialogue_generic(dia, OK, objects, gra);
            return OK;
          }
          else{
            strcpy(game->desc, "I think it cannot be lighted.");
            objects = game_get_objects_name(game, objects);
            dialogue_generic(dia, ERROR, objects, gra);
            return ERROR;
          }
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, ERROR, objects, gra);
          return ERROR;
        }
      }  
    }

  }
  else if(strlen(symbol) > 1){
    for(i = 0; i < game->num_objects; i++){

      if(strcmp(object_get_name(game->object[i]), symbol) == 0){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          if(object_turnoff(object) == OK){
            objects = game_get_objects_name(game, objects);
            dialogue_generic(dia, OK, objects, gra);
            return OK;
          }
          else{
            strcpy(game->desc, "I think it cannot be lighted.");
            objects = game_get_objects_name(game, objects);
            dialogue_generic(dia, ERROR, objects, gra);
            return ERROR;
          }
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, ERROR, objects, gra);
          return ERROR;
        }
      }  
    }
  }

  objects = game_get_objects_name(game, objects);
  dialogue_generic(dia, ERROR, objects, gra);
  return ERROR;
}


STATUS callback_TURNOFF(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/
  char *symbol = NULL; /*!< Variable used for storing the command*/
  STATUS result;

  if(!game || !dia || !gra || !cmd) return ERROR;

  symbol = command_get_symbol(cmd);

  if(strcmp(symbol, "\0") == 0){
    objects = game_get_objects_name(game, objects);objects = game_get_objects_name(game, objects);

    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    objects = game_get_objects_name(game, objects);objects = game_get_objects_name(game, objects);

    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }


  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          result = object_turnoff(object);
          objects = game_get_objects_name(game, objects);objects = game_get_objects_name(game, objects);

          dialogue_generic(dia, result, objects, gra);

          return result;
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          objects = game_get_objects_name(game, objects);objects = game_get_objects_name(game, objects);

          dialogue_generic(dia, ERROR, objects, gra);
          return ERROR;
        }
      }  
    }

  }
  else if(strlen(symbol) > 1){
    for(i = 0; i < game->num_objects; i++){

      if(strcmp(object_get_name(game->object[i]), symbol) == 0){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          result = object_turnoff(object);
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, result, objects, gra);

          return result;
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, ERROR, objects, gra);
          return ERROR;
        }
      }  
    }
  }

  objects = game_get_objects_name(game, objects);
  dialogue_generic(dia, ERROR, objects, gra);
  return ERROR;
}

STATUS callback_OPEN(Game* game, Command* cmd, Dialogue* dia, Graphics* gra, char** objects){
  char* link_name = NULL;
  char* object_name = NULL;
  char* token = NULL;
  Object* object = NULL;
  Link* link = NULL;
  Id link_id = NO_ID;
  int i;
  STATUS result;
  char *string = NULL;
  string = command_get_symbol(cmd);

  if(!game || !dia || !gra || !cmd) return ERROR;

  /*string will be like "door with key", because "open"
  has been already read*/
  link_name = strtok(string, " ");
  token = strtok(NULL, " ");
  if(strcmp(token, "with") != 0){
    strcpy(game->desc, "Maybe trying *open <door> with <key>*?");
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, ERROR, objects, gra);
    return ERROR;
  }
  object_name = strtok(NULL, " ");

  /*Finding the object by its name*/
  for(i = 0; i < game->num_objects; i++){

      if(strcmp(object_get_name(game->object[i]), object_name) == 0){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == FALSE){
          strcpy(game->desc, "Is this object in your bag?");
          objects = game_get_objects_name(game, objects);
          dialogue_generic(dia, ERROR, objects, gra);
          return ERROR;
        
        }
      }  
  }

  /*Finding the link_id by its name*/
  for(i = 0; i < game->num_links; i++){

      if(strcmp(link_get_name(game->links[i]), link_name) == 0){
        link = game->links[i];
        link_id = link_get_id(link);
        break;
      }

  }

  /*Can the object open the link?*/
  if(object_can_open(object, link_id) == TRUE){
    result = link_open(link);
    objects = game_get_objects_name(game, objects);
    dialogue_generic(dia, result, objects, gra);

    return result;
  }
  else{
    strcpy(game->desc, "It won't be opened");
  }

  objects = game_get_objects_name(game, objects);
  dialogue_generic(dia, ERROR, objects, gra);
  return ERROR;
}

STATUS callback_SAVE(Game* game, Command* cmd, Dialogue* dia, Graphics* gra){
  char path[256] = "codigo/Saves/";
  char *symbol = NULL;

	if(!game || !dia || !gra || !cmd) return ERROR;

  	if(!game || !cmd)
  			return ERROR;

  	symbol = command_get_symbol(cmd);
  	strcat(path, symbol); 
  	strcat(path, ".ao");
	
	return game_save(game, path);
}

STATUS callback_LOAD(Game* game, Command* cmd, Dialogue* dia, Graphics* gra){

	int i=0;
	DIR *dir;
	struct dirent *ent;
	char savegames[256];
	char *symbol = NULL;
	char path[256] = "codigo/Saves/";
	STATUS status = ERROR;
	Game *game2, *aux;

  game2 = NULL;

	if(!game || !dia || !gra || !cmd)
		return ERROR;

	/*This if only shows available files for load*/
	symbol = command_get_symbol(cmd);
	if(!strcmp(symbol, "show")){
		if ((dir = opendir ("codigo/Saves")) != NULL) {
		  while ((ent = readdir (dir)) != NULL && i<4) {
		    strcat(savegames, ent->d_name);
		    strcat(savegames, "\n");
		    i++;
		  }
		  strcpy(game->desc, savegames);
		  closedir (dir);
		  return OK;
		} else
		  	return ERROR;
	}

	/*This loads a file to the game*/
	/*THIS SHOULD BE USE IN INIT FROM FILE game_load(game, symbol);*/

	strcat(path, symbol);

	aux = game;
	game2 = game_init(game2);
	if(!game2)
		return ERROR;

	status = game_init_from_file(game2, path);
	game = game2;
	game_destroy(aux);

	return status;
}




/**
* @brief Returns the game die
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return Die pointer
*/
Die * game_get_die(Game * game){
	if(!game) return NULL;
	
	return game->die;
}

/**
* @brief Returns the link in a concrete position
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return Link pointer
*/
Link * game_get_link_n(Game * game, int n){
	if(!game || n >= game->num_links || n < 0)
		return NULL;
	
	return game->links[n];
}

/**
* @brief Returns the number of links
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of links)
*/
int game_get_num_links(Game * game){
	if(!game)
		return -1;
	return game->num_links;
}

/**
* @brief Returns the objects in the game (all of them)
* @author Andrea Ruiz
* @date 16/12/2016
* @param Object ** object
* @return pointer to the array of objects
*/	
Object ** game_get_objects(Game * game){
	if(!game)
		return NULL;
	return game->object;
}

/**
* @brief Returns the number of objects
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of objects)
*/
int game_get_num_objects(Game * game){
	if(!game)
		return -1;

	return game->num_objects;
}

/**
* @brief Returns the number of turns
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return int (number of objects)
*/

int game_get_turns(Game * game){
	if(!game)
		return -1;

	return game->turns;
}

/**
* @brief Returns the player pointer
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return player pointer
*/

Player * game_get_player(Game * game){
	if(!game)
		return NULL;

	return game->player;
}

/**
* @brief It gets the space from a given position
* @author Andrea Ruiz
* @date 17/12/2016
* @param game pointer
* @param Id space id
* @return Space pointer in that position
*/
Space* game_get_space_at(Game* game, int pos){
    if(!game || pos <0 || pos> MAX_SPACES)
		return NULL;

    return game->spaces[pos];
}

/**
* @brief It gets the space from a given position
* @author Andrea Ruiz
* @date 17/12/2016
* @param game pointer
* @param Id space id
* @return Space pointer in that position
*/
Object* game_get_object_at(Game* game, int pos){
    if(!game || pos <0 || pos> MAX_SPACES)
		return NULL;

    return game->object[pos];
}
