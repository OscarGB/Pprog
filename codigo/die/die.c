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

/* --------------------------------------------------------------------
Function:die_throw

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It return a random value between inf and sup

Input: int inf (The inferior limit)
	   int sup (The superior limit)
Output: int (the random number)

------------------------------------------------------------------- */
int die_throw(int inf, int sup){
	float random;

	if(inf < 0 || sup < 0 || sup < inf){
		fprintf(stderr, "Error en la entrada de argumentos a aleat_num");
		return -1; /*ERROR*/
	}

	random = rand();
	random /= RAND_MAX;
	random *= (sup-inf+1);
	random += inf;
	if(random > sup){
		random = sup;
	}
	return (int)random;
}