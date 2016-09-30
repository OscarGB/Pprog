/* ===================================================================
File: game_reader.h

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the reading game module 

Revision history: none

=================================================================== */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "space.h"
#include "game.h"
#include "types.h"


/* --------------------------------------------------------------------
Function: game_load_spaces()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: reads the game table from a file

Input: Game* and a char* (filename)

Output: OK if the table was successfuly read

------------------------------------------------------------------- */
STATUS game_load_spaces(Game* game, char* filename);

#endif