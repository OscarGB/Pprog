/**
 * @brief It implements the die's commands
 * @file die.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 2.0
 * @date 07/10/2016
 * @revision_history Changed creation for different die faces
 */


#include <stdlib.h>
#include <stdio.h>
#include "die.h"
#include "types.h"
#include <time.h>

struct _Die{
	Id id; /*!<Die's id*/
	int last; /*!<Last rolled value*/
	int max; /*!<Maximum value to roll*/
};/*!<Die structure*/

/**
* @brief It return a random value between inf and sup
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param die pointer, int inf, int sup
* @return int (the random number)
*/

int die_roll(Die* die){
	int inf, sup;
	float random; /*The rolled value*/

	if(!die){
		return -1; /*ERROR*/
	}

	inf = 1;
	sup = die->max;

	srand(clock()); /*seed*/
	random = rand(); /*random number between 0 and RAND_MAX*/
	random /= RAND_MAX; /*random number between 0 and 1*/
	random *= (sup-inf+1); /*random number between 0 and (sup -inf +1)*/
	random += inf; /*randome number between inf and (sup + 1)*/
	if(random > sup){ /*in case is (sup + 1)*/
		random = sup; /*We set it to sup*/
	}
	die->last = (int)random; /*Set last to the rolled value*/
	return (int)random;
}


/**
* @brief It creates a die without any information inside
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param id of the die to create
* @param int (the number of faces of the die)
* @return die pointer (of the created one)
*/

Die* die_create(Id id, int faces){
	Die *die = NULL; /*New pointer for die*/

	if(id == NO_ID || faces < 1){
		return NULL;
	}

	die = (Die *)malloc(sizeof(Die));

	if(!die){
		return NULL;
	}

	/*Default values*/
	die->id = id;
	die->last = NOT_ROLLED;
	die->max = faces;

	return die;
}


/**
* @brief It destroy a dice, freeing all the memory blocks
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die to destroy)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS die_destroy(Die* die){
	if(!die){
		return ERROR;
	}

	/*Free the memory*/
	free(die);
	die = NULL;

	return OK;
}


/**
* @brief It prints the data of a die
* @author José Ignacio Gómez, Óscar Gómez
* @date 04/10/2016
* @param Die* (The die to print)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS die_print(Die* die){
	if(!die){
		return ERROR;
	}

	/*Print the values of the die*/
	fprintf(stdout, "-->Die (Id: %ld)\n", die_get_id(die));
	fprintf(stdout, "--->Last value: %d\n", die_get_last_roll(die));
	fprintf(stdout, "--->Faces: %d\n", die_get_faces(die));

	return OK;
}


/**
* @brief It returns the value of the last roll
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die we want to get the value)
* @return int (The value of the last roll)
*/

int die_get_last_roll(Die* die){
	if(!die){
		return NOT_ROLLED;
	}
	/*We return the last rolled value*/
	return die->last;
}


/**
* @brief It returns the Id of the Die
* @author José Ignacio Gómez, Óscar Gómez
* @date 07/10/2016
* @param Die* (The die we want to get the Id)
* @return int (The id of the die)
*/

Id die_get_id(Die* die){
	if(!die){
		return NO_ID;
	}
	/*Get the Id fo the die*/
	return die->id;
}

/**
* @brief It returns the number of faces the die has
* @author Óscar Gómez
* @date 25/11/2016
* @param Die* (The die we want to get the Id)
* @return int (The faces of the die)
*/

int die_get_faces(Die* die){
	if(!die){
		return 0;
	}

	return die->max;
}