/**
 * @brief Definition of the game rules
 * @file game_rules.h
 * @author Andrea Ruiz
 * @version 1.0
 * @date 16/12/2016
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"


typedef struct _Game_rules Game_rules;

/**
* @brief Throws an internal die to pick a random function
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS pick_aleat_function(Game * game);

/**
* @brief Changes (or not) the light of an space
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_light_space(Game *game);

/**
* @brief Changes (or not) the state of a link
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_link_state(Game * game);

/**
* @brief Changes (or not) the location of an object
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS change_object_location(Game * game);

/**
* @brief Kills a player (game over)
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS kill_player(Game * game);

/**
* @brief Kills a player if it has played too many turns
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS useless_player_deserves_death(Game * game);

/**
* @brief Turns off (or not) an object
* @author Andrea Ruiz
* @date 16/12/2016
* @param Game *game
* @return STATUS (OK if everything went well), ERROR if not
*/

STATUS turn_object_light_off(Game * game);

#endif
