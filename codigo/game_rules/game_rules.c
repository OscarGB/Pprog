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
#include "game_rules.h"
#include "game.h"


STATUS change_light_space(Game *game){
	Id current_id;
	Die * die;
	Space *current_space;
	BOOL space_light;
	int roll;

	if(!game)
		return ERROR;

	current_id = game_get_player_location(game);
	if(current_id == NO_ID)
		return ERROR;

	current_space = game_get_space(game, current_id);
	if(current_space == NULL)
		return ERROR
	
	space_light = space_get_light(current_space);

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_get_last_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	if(roll < (die_get_faces(die) / 2) && space_light == TRUE){
		space_set_light(current_space, FALSE);
		if(space_get_light(current_space) != FALSE)
			return ERROR;
	} else if(roll > (die_get_faces(die) / 2) && space_light == FALSE){
		space_set_light(current_space, TRUE);
		if(space_get_light(current_space) != TRUE)
			return ERROR;
	}

	return OK

}


STATUS change_link_status(Game * game){
	Id current_id;
	Space *current_space;
	Link * link;
	State link_state;
	Die * die;
	int aleat;
	int nlinks;
	int roll;

	if(!gamer)
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

	roll = die_get_last_roll(game_get_die(game));
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	if(roll < (die_get_faces(die) / 2) && state == OPENL){
		link_set_state(link, CLOSEDL);
		if(link_get_state(link) != CLOSEDL)
			return ERROR;
	} else if (roll > (die_get_faces(die) / 2) && state == CLOSEDL){
		link_set_state(link, OPENL);
		if(link_get_state(link) != OPENL)
			return ERROR;

	return OK;
}

STATUS change_object_location(Game * game){
	Id current_id;
	Die * die;
	Space *current_space;
	Object ** objects;
	Object * object;
	int roll;

	if(!game)
		return ERROR;

	current_id = game_get_player_location(game);
	if(current_id == NO_ID)
		return ERROR;

	current_space = game_get_space(game, current_id);
	if(current_space == NULL)
		return ERROR
	
	space_light = space_get_light(current_space);

	die = game_get_die(game);
	if(!die)
		return ERROR;

	roll = die_get_last_roll(die);
	if(roll <= 0 || roll > die_get_faces(die))
		return ERROR;

	objects = game_get_objects(game);

	
}


