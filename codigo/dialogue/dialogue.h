/**
 * @brief It defines the dialogue module
 * @file dialogue.h
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 15/12/2016
 * @revision_history none
 */


#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "command.h"


typedef struct _Dialogue Dialogue; /*!< Definition of struct Dialogue*/

/*
* @brief creates a new dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @return Dialogue* (created dialogue)
*/
Dialogue* dialogue_create();

/*
* @brief destroys a dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @param Dialogue*
* @return OK if it was destroyed
*/
STATUS dialogue_destroy(Dialogue* dialogue);

STATUS dialogue_standard_print()


#endif