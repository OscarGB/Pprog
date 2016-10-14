/* ===================================================================
File: die.c

Version: 1.0

Date: 07/10/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the die's commands

Revision history: none

=================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include "die.h"
#include "types.h"
#include <time.h>

struct _Die{
	Id id;
	int last;
};

/* --------------------------------------------------------------------
Function:die_roll()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It return a random value between inf and sup

Input: int inf (The inferior limit)
	   int sup (The superior limit)
Output: int (the random number)

------------------------------------------------------------------- */
int die_roll(Die* die, int inf, int sup){
	float random;

	if(inf < 0 || sup < 0 || sup < inf || !die){
		return -1; /*ERROR*/
	}
	srand(clock());
	random = rand();
	random /= RAND_MAX;
	random *= (sup-inf+1);
	random += inf;
	if(random > sup){
		random = sup;
	}
	die->last = random;
	return (int)random;
}

/* --------------------------------------------------------------------
Function: die_create();

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates a die without any information inside

Input: Id (The id of the dice)

Output: Die* (A pointer to the created die)

------------------------------------------------------------------- */
Die* die_create(Id id){
	Die *die = NULL;

	die = (Die *)malloc(sizeof(Die));

	if(!die){
		return NULL;
	}

	die->id = id;
	die->last = NOT_ROLLED;

	return die;
}


/* --------------------------------------------------------------------
Function: die_destroy()

Date:07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroy a dice, freeing all the memory blocks

Input: Die* (The die to destroy)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS die_destroy(Die* die){
	if(!die){
		return ERROR;
	}

	free(die);
	die = NULL;

	return OK;
}

/* --------------------------------------------------------------------
Function: die_print()

Date: 04/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It prints the data of a die

Input: Die* (The die to print)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS die_print(Die* die){
	if(!die){
		return ERROR;
	}

	fprintf(stdout, "-->Die (Id: %ld)\n", die_get_id(die));
	fprintf(stdout, "--->Last value: %d\n", die_get_last_roll(die));

	return OK;
}

/* --------------------------------------------------------------------
Function: die_get_last_roll

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It returns the value of the last roll

Input: Die* (The die we want to get the value)

Output: int (The value of the last roll)

------------------------------------------------------------------- */
int die_get_last_roll(Die* die){
	if(!die){
		return NOT_ROLLED;
	}
	return die->last;
}

/* --------------------------------------------------------------------
Function: die_get_id()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It returns the Id of the Die

Input: Die* (The die we want to get the Id)

Output: Id (The id of the die)

------------------------------------------------------------------- */
Id die_get_id(Die* die){
	if(!die){
		return NO_ID;
	}
	return die->id;
}
