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
#include "game.h"
#include "player.h"
#include "object.h"
#include "game_reader.h"
#include "die.h"
#include "link.h"
#include "graphics.h"

#ifdef __WINDOWS_BUILD__ /*In case we are working on Windows*/
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct _Game{
  Player* player; /*!< Pointer to Player Structure */
  Object* object[MAX_IDS + 1]; /*!< Array of pointers to Object Structure */
  int num_objects; /*!< Number of objects of the Game */
  Space* spaces[MAX_SPACES]; /*!< Array of pointers to Space Structure */
  Die* die; /*!< Pointer to Die Structure */
  Link *links[MAX_LINKS]; /*!< Array of pointers to Link Structure */
  int num_links;
  char desc[WORD_SIZE+1]; /* !< For inspect command*/
};/*!< Game structure*/

/*
* brief List of callbacks for each command in the game 
*/

STATUS callback_UNKNOWN(Game* game);
STATUS callback_QUIT(Game* game);
STATUS callback_NEXT(Game* game);
STATUS callback_BACK(Game* game);
STATUS callback_JUMP(Game* game);
STATUS callback_UP(Game* game);
STATUS callback_BACK(Game* game);
STATUS callback_DROP(Game* game, char *symbol);
STATUS callback_PICK(Game* game, char *symbol);
STATUS callback_ROLL(Game* game);
STATUS callback_INSPECT(Game* game, char *symbol);
STATUS callback_GO(Game* game, char *symbol);
STATUS callback_TURNON(Game* game, char *symbol);
STATUS callback_TURNOFF(Game* game, char *symbol);


/*
* Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Space* game_get_space(Game* game, Id id);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);
Id     game_get_player_location(Game* game);

STATUS game_add_object(Game* game, Object* object);
STATUS game_set_object_location(Game* game, Id id_s, Id id_o);
Id     game_get_object_location(Game* game, char *symbol);

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
* @brief it calls different callbacks depending on the written command
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @param Command cmd
* @return OK if it was updated
*/
STATUS game_update(Game* game, Command *cmd) {

  switch (command_get_cmd(cmd)) { /*Switch for the command value*/
  case UNKNOWN:
    return callback_UNKNOWN(game);
  case QUIT:
    return callback_QUIT(game);
  case PICK:
    return callback_PICK(game, command_get_symbol(cmd));
  case DROP:
    return callback_DROP(game, command_get_symbol(cmd));
  case ROLL:
    return callback_ROLL(game);
  case INSPECT:
    return callback_INSPECT(game, command_get_symbol(cmd));
  case GO:
    return callback_GO(game, command_get_symbol(cmd));
  case TURNON:
    return callback_TURNON(game, command_get_symbol(cmd)); 
  case TURNOFF:
    return callback_TURNOFF(game, command_get_symbol(cmd));
  case OPEN:
    return callback_TURNON(game, command_get_symbol(cmd));
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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_east = NO_ID, id_west = NO_ID; /* !< Ids for locations*/
  Id id_l_back = NO_ID, id_l_next = NO_ID, id_l_east = NO_ID, id_l_west = NO_ID; /*!< Ids of the links*/
  Space* space_act = NULL; /* !< Pointers to spaces needed to print the game*/
  Space* space_back = NULL;
  Space* space_next = NULL;
  Space* space_east = NULL;
  Space* space_west = NULL;
  int i; /* !< loops, last rolled value*/

  if(!gra || !game){
    return;
  }

  graphics_clear(gra);
  
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
        id_back = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_back = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_back = NO_ID;
    }
  }

  /*Search for the id of the next space*/
  for(i=0; i<(4*MAX_SPACES); i++){
    if(link_get_id(game->links[i]) == id_l_next){
      if(link_get_conection1(game->links[i]) == id_act){
        id_next = link_get_conection2(game->links[i]);
        break;
      }
      else{
        id_next = link_get_conection1(game->links[i]);
        break;
      }
    }
    else{
      id_next = NO_ID;
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
  space_back = game_get_space(game, id_back);
  space_next = game_get_space(game, id_next);  
  
  if(system(CLEAR))
     return; 

  if (id_back != NO_ID) {
    if(space_get_light(space_back) == TRUE){
      print_in_zone(gra, PLAYGROUND, N, space_get_gdesc(space_back));
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
      print_in_zone(gra, PLAYGROUND, C, space_get_gdesc(space_act));
    }
    else{
      print_in_zone(gra, PLAYGROUND, C, "+------------+|            ||            ||            ||            ||            |+------------+");
    }
  }
  else{
    print_in_zone(gra, PLAYGROUND, C, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  }
  
  if (id_next != NO_ID) {
    if(space_get_light(space_next) == TRUE){
      print_in_zone(gra, PLAYGROUND, S, space_get_gdesc(space_next));
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
  


  graphics_refresh(gra);

  /*printf("Object locations:");
  for(i = 0; i < game->num_objects; i++){
    if(object_get_location(game->object[i]) != PLAYER_OBJ){
      printf(" %c:%d", object_get_symbol(game->object[i]), (int)object_get_location(game->object[i]));
    }
  }    
  printf("\n");

  printf("Player objects: ");
  for(i=0; i< game->num_objects; i++){
  if(object_get_location(game->object[i]) == PLAYER_OBJ)
    printf("%c ", object_get_symbol(game->object[i]));
  }

  printf("\n");

    

  last = die_get_last_roll(game->die);
  if(last != -1){
    printf("Last die value: %d\n", last);
  }

  if(strlen(game->desc) != 0){
  printf("Description: %s\n", game->desc);
  }
  game->desc[0] = '\0';


  printf("\n[commands: quit or q, drop or d, pick or p, roll or r, inspect or i, go or g]");
  printf("\nprompt:> ");*/
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
STATUS callback_UNKNOWN(Game* game) {
  return OK;
}


/**
* @brief callback for quitting the game
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_QUIT(Game* game) {
  return OK;
}


/**
* @brief callback for "next" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_NEXT(Game* game) {
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, south_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  
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
        return game_set_player_location(game, south_id);
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
STATUS callback_BACK(Game* game) {
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, north_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  
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
        return game_set_player_location(game, north_id);
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
STATUS callback_UP(Game* game){

  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, up_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Space id*/
  
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
        return game_set_player_location(game, up_id);
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
STATUS callback_DOWN(Game* game){
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, down_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Space id*/
  
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
        return game_set_player_location(game, down_id);
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
STATUS callback_JUMP(Game* game){
  int i = 0, j = 0; /* !< Variables used for loops*/
  Id current_id = NO_ID, east_id = NO_ID; /* !< Current space id and sout id*/
  Id link_id = NO_ID; /* !< Link id*/
  Id space_id = NO_ID; /* !< Id of the next space*/
  
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
        return game_set_player_location(game, east_id);
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
STATUS callback_DROP(Game* game, char *symbol){
  Object* object = NULL; /* !< Object that will be dropped*/
  Id object_id = NO_ID;
  Id current_id; /* !< Id of the current space*/
  int i;

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

  if(object_id == NO_ID || !object) return ERROR;

  if(player_drop_object(game->player, object_id) == FALSE)
	return ERROR;

  if(strlen(symbol) == 1){
    if(object_get_symbol(object) != symbol[0]){
      player_pick_object(game->player, object_id);
      return ERROR;
    }
  }
  else if(strlen(symbol) > 1){
    if(strcmp(object_get_name(object), symbol) != 0){
      player_pick_object(game->player, object_id);
      return ERROR;
    }
  }

  current_id = game_get_player_location(game);

  return game_set_object_location(game, current_id, object_get_id(object));
}


/**
* @brief callback for "pick" instruction
* @author José Ignacio Gómez, Óscar Gómez, Andrea Ruiz
* @date 29/09/2016
* @param game pointer
* @param the symbol to pick
* @return OK if it went ok
*/
STATUS callback_PICK(Game* game, char *symbol){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/

  if(strcmp(symbol, "\0") == 0){
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    return ERROR;
  }

  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_pick_object(game->player, object_get_id(object)) != FALSE){
          object_set_location(object, PLAYER_OBJ); 
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
          return OK;
        }
      }  
    }
  }

  return ERROR;
}


/**
* @brief callback for "roll" instruction
* @author José Ignacio Gómez, Óscar Gómez
* @date 29/09/2016
* @param game pointer
* @return OK if it went ok
*/
STATUS callback_ROLL(Game* game){
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
STATUS callback_INSPECT(Game* game, char *symbol){

    int i;/* !< Variable used for loops*/
    Object *obj; /* !<Variable used for storing the player's object*/
    Id player_location = NO_ID; /* !< Locations of the player and object*/
    Space *space; /*!<Variable used for storing auxiliary spaces*/

    obj = NULL;
    
    if(!game) return ERROR;
    if(strcmp(symbol, "E") == 0) return ERROR;

    player_location = game_get_player_location(game);
    if(player_location == NO_ID) return ERROR;

    if(strlen(symbol) == 1){
      if(symbol[0] == 's' || symbol[0] == 'S'){ /*!< Inspecting space */
          	for(i=0; i<MAX_SPACES && game->spaces[i]; i++){
          		if(player_location==space_get_id(game->spaces[i])){
                if(space_get_light(game->spaces[i]) == TRUE){
          		    strcpy(game->desc, space_get_adesc(game->spaces[i]));
          		    return OK;	
                }
          		}
          	}
            return ERROR;
      }else{ /*!< Inspecting an object */
  	     for(i=0; i< game->num_objects; i++){ /*!< If player has the object or they're in the same field */
  		      if(object_get_location(game->object[i]) == player_location || object_get_location(game->object[i]) == PLAYER_OBJ){
  			       if(object_get_symbol(game->object[i]) == symbol[0])
  				        obj = game->object[i];
  		      }
          }

          if(!obj) return ERROR;

		  space = game_get_space(game, object_get_location(obj)); /*Get the space where the object is*/

		  if(space_get_light(space) == FALSE){
		  	strcpy(game->desc, "You can't find the object in the pitch black darkness");
		  }
          strcpy(game->desc, object_get_description(obj));
          return OK;
        }
    }

    else if(strlen(symbol) > 1){
      if(strcmp(symbol, "space") == 0 || strcmp(symbol, "Space") == 0){ /*!< Inspecting space */
          for(i=0; i<MAX_SPACES && game->spaces[i]; i++){
            if(player_location==space_get_id(game->spaces[i])){
                if(space_get_light(game->spaces[i]) == TRUE){
                  strcpy(game->desc, space_get_adesc(game->spaces[i]));
                  return OK;  
                }  
            }
          }
          return ERROR;
      }else{ /*!< Inspecting an object */
         for(i=0; i< game->num_objects; i++){ /*!< If player has the object or they're in the same field */
            if(object_get_location(game->object[i]) == player_location || object_get_location(game->object[i]) == PLAYER_OBJ){
               if(strcmp(object_get_name(game->object[i]), symbol) == 0)
                  obj = game->object[i];
            }
          }

          if(!obj) return ERROR;
	
		  space = game_get_space(game, object_get_location(obj)); /*Get the space where the object is*/

		  if(space_get_light(space) == FALSE){
		  	strcpy(game->desc, "You can't find the object in the pitch black darkness");
		  }
		  strcpy(game->desc, object_get_description(obj));
          return OK;
        }
    }

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

STATUS callback_GO(Game* game, char *symbol){

    int i = 0, j = 0; /* !< Variables used for loops*/
    Id current_id = NO_ID, west_id = NO_ID; /* !< Current space id and sout id*/
    Id link_id = NO_ID; /* !< Link id*/
    Id space_id = NO_ID; /* !< Id of the next space*/


    if(!game) return ERROR;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
	   return ERROR;
    }

    if(strlen(symbol) == 1){
      if(symbol[0] == 'n'){ /* Go north */ 
  	   return callback_BACK(game);
      }

      if(symbol[0] == 's'){ /* Go south */ 
  	   return callback_NEXT(game);
      }

	  if(symbol[0] == 'u'){ /* Go up */
	   return callback_UP(game); 
	  }

	  if(symbol[0] == 'd'){ /* Go down */
	   return callback_DOWN(game);
	  }

      if(symbol[0] == 'e'){ /* Go east */ 
  	   return callback_JUMP(game);
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

        			        return game_set_player_location(game, west_id);
              			}
        			      else{
        			        return ERROR;
              			}
                	}
          	}	

      }

    return OK;
  }

  else if(strlen(symbol) > 1){
      if(strcmp(symbol, "north") == 0){ /* Go north */ 
       return callback_BACK(game);
      }

      if(strcmp(symbol, "south") == 0){ /* Go south */ 
       return callback_NEXT(game);
      }

	  if(strcmp(symbol, "up") == 0){ /* Go up */ 
       return callback_UP(game);
      }

	  if(strcmp(symbol, "down") == 0){ /* Go down */ 
       return callback_DOWN(game);
      }

      if(strcmp(symbol, "east") == 0){ /* Go east */ 
       return callback_JUMP(game);
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
                      return game_set_player_location(game, west_id);
                    }
                    else{
                      return ERROR;
                    }
                  }
            } 

      }

    return OK;
  }


return ERROR;
}

STATUS callback_TURNON(Game* game, char *symbol){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/

  if(strcmp(symbol, "\0") == 0){
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    return ERROR;
  }


  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          if(object_turnoff(object) == OK){
            return OK;
          }
          else{
            strcpy(game->desc, "I think it cannot be lighted.");
            return ERROR;
          }
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
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
            return OK;
          }
          else{
            strcpy(game->desc, "I think it cannot be lighted.");
            return ERROR;
          }
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          return ERROR;
        }
      }  
    }
  }

  return ERROR;
}


STATUS callback_TURNOFF(Game* game, char *symbol){
  Object* object; /* !< Object that will be picked*/
  Id player_id, object_id; /* !< Ids of the player and object*/
  int i; /* !< Variable used for loops*/

  if(strcmp(symbol, "\0") == 0){
    return ERROR;
  }


  player_id = game_get_player_location(game);

  object_id = game_get_object_location(game, symbol);

  if(player_id != object_id || player_id == NO_ID || object_id == NO_ID){
    return ERROR;
  }


  if(strlen(symbol) == 1){
    for(i = 0; i < game->num_objects; i++){

      if(object_get_symbol(game->object[i]) == symbol[0]){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == TRUE){
          return object_turnoff(object);
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
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
          return object_turnoff(object);
        }
        else{
          strcpy(game->desc, "Is this object in your bag?");
          return ERROR;
        }
      }  
    }
  }

  return ERROR;
}

STATUS callback_OPEN(Game* game, char *string){
  char* link_name = NULL;
  char* object_name = NULL;
  char* token = NULL;
  Object* object = NULL;
  Link* link = NULL;
  Id link_id = NO_ID;
  int i;

  /*string will be like "door with key", because "open"
  has been already read*/
  link_name = strtok(string, " ");
  token = strtok(NULL, " ");
  if(strcmp(token, "with") != 0){
    strcpy(game->desc, "Maybe trying *open <door> with <key>*?");
    return ERROR;
  }
  object_name = strtok(NULL, " ");

  /*Finding the object by its name*/
  for(i = 0; i < game->num_objects; i++){

      if(strcmp(object_get_name(game->object[i]), object_name) == 0){
        object = game->object[i];

        if(player_has_object(game->player, object_get_id(object)) == FALSE){
          strcpy(game->desc, "Is this object in your bag?");
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
    return link_open(link);
  }
  else{
    strcpy(game->desc, "It won't be opened");
  }

  return ERROR;
}
