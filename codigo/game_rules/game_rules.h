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


#endif
