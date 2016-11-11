/**
 * @brief It implements the capability of store sets of things
 * @file set.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 07/10/2016
 * @revision_history none
 */

#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

#define NOT_FOUND -1

struct _Set {
	Id id[MAX_IDS]; /*<!The array of ids of the set*/
	int num_ids; /*<!The number of elements that the set has*/
};

/*Private functions*/


/*
* @brief checks in which position is a certain Id
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param Set* (the set to inspect)
	 Id (the Id to search)
* @return int (the position in the set)
*/

int set_where_is_id(Set* set, Id id) {
	int i; /*Variable used for loops and searching value*/

	for(i = 0; i < set->num_ids; i++){
		if(set->id[i] == id) return i;
	}

	return NOT_FOUND;
}

/*Public functions*/


/*
* @brief checks if the set is full
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param Set* (the set to inspect)
* @return BOOL (TRUE if the set is full)
*/

BOOL set_is_full(Set* set) {
	
	if(set->num_ids == MAX_IDS){
		return TRUE;
	}

	return FALSE;
}


/*
* @brief checks if the set is empty
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param Set* (the set to inspect)
* @return BOOL (TRUE if the set is empty)
*/


BOOL set_is_empty(Set* set) {
	if(set->num_ids == 0) return TRUE;
	else return FALSE;
}


/*
* @brief creates a new set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param none
* @return Set* (created set)
*/

Set* set_create() {
	int i; /*Variable used for loops*/

	Set* set = NULL;

	set = (Set*) malloc (sizeof(Set));
	if(!set) return NULL;

	/*Default values*/

	for(i = 0; i < MAX_IDS; i++) {
		set->id[i] = NO_ID;
	}

	set->num_ids = 0;

	return set;
}


/*
* @brief destroys a set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer (set to destroy)
* @return STATUS (OK if it was successfuly destroyed)
*/

STATUS set_destroy(Set* set) {
	if(!set) return ERROR;

	free(set);
	return OK;
}


/*
* @brief adds something to a given set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param Set* , Id (the id of the thing we want to add)
* @return STATUS (OK if it was successfuly added)
*/

STATUS set_add(Set* set, Id id) {

	if(set_where_is_id(set, id) != NOT_FOUND || !set || id == NO_ID || set_is_full(set) == TRUE){
		return ERROR;
	}

	set->id[set->num_ids] = id;
	set->num_ids++;

	return OK;
}


/*
* @brief deletes the id from the set if it's inside
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param Set* , Id (the id of the thing we want to delete)
* @return STATUS (OK if it was successfuly deleted)
*/

STATUS set_delete(Set* set, Id id) {
	int position;

	if(!set || set_is_empty(set) == TRUE || id == NO_ID){
		return ERROR;
	}

	position = set_where_is_id(set, id);
	if(position == NOT_FOUND) return ERROR;

	set->id[position] = set->id[set->num_ids-1];
	set->id[set->num_ids-1] = NO_ID;

	set->num_ids--;
	return OK;
}


/*
* @brief prints the set's array
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer
* @return STATUS (OK if it was successfuly printed)
*/

STATUS set_print(Set* set) {
	int i;

	if(!set) return ERROR;
	if(set_is_empty(set) == TRUE) return OK;

	fprintf(stdout, "[");
	fprintf(stdout, "%ld", set->id[0]);
	for(i = 1; i < set->num_ids; i++){
		fprintf(stdout, ", %ld", set->id[i]);
	}
	fprintf(stdout, "]\n");

	return OK;
}


/*
* @brief gives the number of stored ids
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer
* @return the number of stored ids
*/

int set_get_num_ids(Set* set) {
	if(!set) return NOT_FOUND;

	return set->num_ids;
}


/*
* @brief gives the number of stored ids
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param set pointer, id
* @return BOOL (returns TRUE if the id is inside the set)
*/

BOOL set_is_id(Set* set, Id id){
	if(set_where_is_id(set, id) == NOT_FOUND){
		return FALSE;
	}

	return TRUE;
}
