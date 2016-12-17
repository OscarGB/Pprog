/**
 * @brief Definition of the game rules
 * @file game_rules.h
 * @author Andrea Ruiz
 * @version 1.0
 * @date 16/12/2016
 */

#include "game.h"


typedef struct _Game_rules Game_rules;

/*typedef enum enum_Game_rules {
} E_Game_rules; */


STATUS change_light_space(Game *game);
STATUS change_link_status(Game * game);
STATUS change_object_location(Game * game);
