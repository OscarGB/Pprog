/**
 * @brief Implementation of the game rules
 * @file game_rules.c
 * @author Andrea Ruiz
 * @version 1.0
 * @date 16/12/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game_rules.h"


/**
* @brief Throws an internal die to pick a random function
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS pick_aleat_function(Game * game, Graphics * g){
	Die * die;
	int roll;

	if(!game || !g)
		return ERROR;

	die = die_create(2710, 50);
	if(!die)
		return ERROR;

	roll = die_roll(die);
	free(die);

			return change_link_state(game, g);

	switch(roll){
		case 1:
			return change_light_space(game, g);
		case 2:
			return change_link_state(game, g);
		case 3:
			return change_object_location(game, g);
		case 4:
			return turn_object_light_off(game, g);
		case 5:
			return useless_player_deserves_death(game, g);
		case 6:
			return kill_player(game, g);
		default:
			return OK;
	}

	return ERROR;

}

/**
* @brief Changes (or not) the light of an space
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_light_space(Game *game, Graphics * g){
	Id current_id = NO_ID;
	Die * die = NULL;
	Space *current_space = NULL;
	BOOL space_light;
	int roll;

	if(!game || !g)
		return ERROR;

	current_id = game_get_player_location(game);
	if(current_id == NO_ID)
		return ERROR;

	current_space = game_get_space(game, current_id);
	if(current_space == NULL)
		return ERROR;
	
	space_light = space_get_light(current_space);

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	dialogue_print(g, "We are going to play with light :)");
	sleep(2);

	if(roll < (die_get_faces(die) / 2) && space_light == TRUE){
		space_set_light(current_space, FALSE);
		if(space_get_light(current_space) == FALSE){
			dialogue_print(g, "Ops, it's so dark now\nTry using a lantern or similar ^^");
			sleep(2);
			return OK;
		}else
			return ERROR;

	} else if(roll > (die_get_faces(die) / 2) && space_light == FALSE){
		space_set_light(current_space, TRUE);
		if(space_get_light(current_space) == TRUE){
			dialogue_print(g, "You are not a big player,\nso now you can try with more light...");
			sleep(2);
			return OK;
		}else
			return ERROR;
	}

	dialogue_print(g, "Nothing has happened\nYou are so lucky");
	sleep(2);

	return OK;

}

/**
* @brief Changes (or not) the state of a link
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_link_state(Game * game, Graphics * g){
	Link * link = NULL;
	Die * die = NULL;
	int aleat;
	int nlinks;
	int roll;
	State state;

	if(!game || !g)
		return ERROR;

	srand(time(NULL)+clock());
	
	nlinks = game_get_num_links(game);

	aleat = rand() % nlinks;
	if(aleat < 0 || aleat >= nlinks)
		return ERROR;


	link = game_get_link_n(game, aleat);
	if(!link)
		return ERROR;

	state = link_get_state(link);

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	dialogue_print(g, "It's time to play with links :)");
	sleep(2);

	if(roll < (die_get_faces(die) / 2) && state == OPENL){
		link_set_state(link, CLOSEDL);
		if(link_get_state(link) == CLOSEDL){
			dialogue_print(g, "A random link has been closed\nGood luck trying to escape ;)");
			sleep(2);
			return OK;
		}else
			return ERROR;
	} else if (roll > (die_get_faces(die) / 2) && state == CLOSEDL){
		link_set_state(link, OPENL);
		if(link_get_state(link) == OPENL){
			dialogue_print(g, "A random link has been opened\nIt's your oportunity!\nRUN!");
			sleep(2);
			return OK;
		}else
			return ERROR;
	}

	dialogue_print(g, "Nothing has happened\nYou're so lucky (or not) ;)");
	sleep(2);

	return OK;
}

/**
* @brief Changes (or not) the location of an object
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_object_location(Game * game, Graphics * g){
	Id current_id;
	Die * die = NULL;
	Space *current_space = NULL;
	Object ** objects = NULL;
	Object * object = NULL;
	int roll, i;

	if(!game || !g)
		return ERROR;

	current_id = game_get_player_location(game);
	if(current_id == NO_ID)
		return ERROR;

	current_space = game_get_space(game, current_id);
	if(current_space == NULL)
		return ERROR;

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	objects = game_get_objects(game);
	if(!objects)
		return ERROR;

	for(i=0; i<game_get_num_objects(game); i++){
		if(object_get_location(objects[i]) == current_id && object_get_movable(objects[i]) == TRUE){
			object = objects[i];
			break;
		}
	}
	
	if(!object) /* There are no movable objects in space */
		return OK;
	if(roll < die_get_faces(die)/2){
		if(current_id >1){
			object_set_location(object, current_id -1);
			dialogue_print(g, "Can you hear that?\nHA!\nAn object has been taken to another space");
			sleep(2);
			return OK;
		}
	}
	
	dialogue_print(g, "You are so lucky\nHave you considered using your luck\nin something better?");

	return OK;
	
}

/**
* @brief Kills a player (game over)
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS kill_player(Game * game, Graphics * g){
	Die * die = NULL;
	int roll;

	if(!game || !g)
		return ERROR;

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	if(roll == 1){
		game_set_endgame(game, TRUE);
		dialogue_print(g, "Sorry, the rules have decided to\nkill you");
		sleep(2);
		dialogue_print(g, "You can try loading a previous game ;)\nOr starting a new one");
		sleep(2);
		dialogue_print(g, "Bye :)");
		sleep(2);
		game_is_over(game);
		return OK;
	}

	dialogue_print(g, "Death is coming for you\nYou should hurry up");
	sleep(2);	

	return OK;

}

/**
* @brief Kills a player if it has played too many turns
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS useless_player_deserves_death(Game * game, Graphics * g){
	int turns;
	if(!game || !g)
		return ERROR;

	turns = game_get_turns(game);
	

	if(turns >= DEATH_DESERVED){
		game_set_endgame(game, TRUE);
		dialogue_print(g, "The map is not that big\nYou have played way too much");
		sleep(2);
		dialogue_print(g, "You don't deserve our game");
		sleep(2);
		dialogue_print(g, "GAME OVER");
		sleep(2);
		game_is_over(game);
		return OK;
	}

	dialogue_print(g, "Death is coming for you\nBe careful, may the odds be ever in your favor");
	sleep(2);

	return OK; 
}

/**
* @brief Turns off (or not) an object
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS turn_object_light_off(Game * game, Graphics * g){
	Player * player = NULL;
	Inventory * bag = NULL;
	Object * object[MAX_IDS+1];
	long * ids, i;

	if(!game || !g)
		return ERROR;

	player = game_get_player(game);
	if(!player)
		return ERROR;

	bag = player_get_inventory(player);
	if(!bag)	
		return ERROR;

	ids = inventory_get_ids(bag);

	
	for(i=0; i<MAX_IDS; i++){
		object[i] = game_get_object(game, ids[i]);
		if(object_get_on_off(object[i]) == TRUE){
			object_turnoff(object[i]);
			if(object_get_on_off(object[i]) == FALSE){
				dialogue_print(g, "Ops, it's so dark now.\nWhat could have happened? ¬¬");
				sleep(2);
				return OK;
			}
		}

	}

	dialogue_print(g, "You don't have any object turned on\nWhat a pity :(,\nIt was going to be turned off\n'magically'...");
	sleep(2);

	return OK;
}
	


