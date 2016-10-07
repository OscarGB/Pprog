/* ===================================================================
File: die.h

Version: 1.0

Date: 07/10/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the die's commands

Revision history: none

=================================================================== */
#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include "types.h"

typedef struct _Die Die;

/* --------------------------------------------------------------------
Function:die_roll()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It return a random value between inf and sup

Input: int inf (The inferior limit)
	   int sup (The superior limit)
	   Die* (The die to roll)
Output: int (the random number)

------------------------------------------------------------------- */
int die_roll(Die* die, int inf, int sup);


/* --------------------------------------------------------------------
Function: die_create();

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates a die without any information inside

Input: Id (The id of the dice)

Output: Die* (A pointer to the created die)

------------------------------------------------------------------- */
Die* die_create(Id id);


/* --------------------------------------------------------------------
Function: die_destroy()

Date:07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroy a dice, freeing all the memory blocks

Input: Die* (The die to destroy)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS die_destroy(Die* die);

/* --------------------------------------------------------------------
Function: die_print()

Date: 04/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It prints the data of a die

Input: Die* (The die to print)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS die_print(Die* die);

/* --------------------------------------------------------------------
Function: die_get_last_roll

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It returns the value of the last roll

Input: Die* (The die we want to get the value)

Output: int (The value of the last roll)

------------------------------------------------------------------- */
int die_get_last_roll(Die* die);

/* --------------------------------------------------------------------
Function: die_get_id()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It returns the Id of the Die

Input: Die* (The die we want to get the Id)

Output: Id (The id of the die)

------------------------------------------------------------------- */
Id die_get_id(Die* die);

#endif