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
#include "graphics.h"

#define MAX_DIALOGUE 180


typedef struct _Dialogue Dialogue; /*!< Definition of struct Dialogue*/

typedef enum{
	SPACE = 0,
	INVENTORY,
	OBJECT
}DIALOGUE_INSPECT;

/*
* @brief creates a new dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @param Command* 
* @return Dialogue* (created dialogue)
*/
Dialogue* dialogue_create(Command* current);

/*
* @brief destroys a dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @param Dialogue*
* @return OK if it was destroyed
*/
void dialogue_destroy(Dialogue* dialogue);

/*
* @brief Print the standard dialogue (objects in the space)
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Graphics*
* @param Dialogue*
* @param STATUS
* @param char** objects
* @param char string
* @return OK if it worked
*/
STATUS dialogue_standard(Graphics* gra, Dialogue* dialogue, char** objects, char *string);

/*
* @brief generic dialogue engine
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Dialogue*
* @param STATUS
* @param char** objects
* @param Graphics*
* @param char string
* @return OK if it worked
*/
STATUS dialogue_generic(Dialogue* dialogue, STATUS check, char** objects, Graphics* gra);

/*
* @brief dialogue engine for inspect
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Dialogue*
* @param STATUS
* @param char** inventory
* @param Graphics*
* @param DIALOGUE_INSPECT type
* @param char string
* @return OK if it worked
*/
STATUS dialogue_inspect(Dialogue* dialogue, STATUS check, char** inventory, Graphics* gra, DIALOGUE_INSPECT type);

/*
* @brief prints on screen the dialogue
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Graphics*
* @param char string
* @return OK if it was printed successfuly
*/
STATUS dialogue_print(Graphics* gra, char *string);

#endif