/**
 * @brief It defines the die's commands
 * @file die.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 07/10/2016
 * @revision_history none
 */

#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include "types.h"

#define NOT_ROLLED -1

typedef struct _Die Die; /*<! Definition of the Die structure */


/*
* @brief It return a random value between inf and sup
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param die pointer, int inf, int sup
* @return int (the random number)
*/

int die_roll(Die* die, int inf, int sup);


/*
* @brief It creates a die without any information inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param id of the die to create
* @return die pointer (of the created one)
*/

Die* die_create(Id id);


/*
* @brief It destroy a dice, freeing all the memory blocks
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die to destroy)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS die_destroy(Die* die);


/*
* @brief It prints the data of a die
* @author José Ignacio Gómez, Óscar Gómez
* @date 04/10/2016
* @param Die* (The die to print)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS die_print(Die* die);


/*
* @brief It returns the value of the last roll
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die we want to get the value)
* @return int (The value of the last roll)
*/

int die_get_last_roll(Die* die);

/*
* @brief It returns the Id of the Die
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die we want to get the Id)
* @return int (The id of the die)
*/

Id die_get_id(Die* die);

#endif
