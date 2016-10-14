/* ===================================================================
File: set.h

Version: 1.0

Date: 07/10/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the capability of store sets
of things

Revision history: none

=================================================================== */

#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

#define NOT_FOUND -1

struct _Set {
	Id id[MAX_IDS];
	int num_ids;
};

/*Private functions*/

int set_where_is_id(Set* set, Id id) {
	int i;

	for(i = 0; i < set->num_ids; i++){
		if(set->id[i] == id) return i;
	}

	return NOT_FOUND;
}

/*Public functions*/

/* --------------------------------------------------------------------
Function: set_is_full()

Date: 14/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: checks if the set is full

Input: Set*

Output: TRUE if the set is full

------------------------------------------------------------------- */
BOOL set_is_full(Set* set) {
	
	if(set->num_ids == MAX_IDS){
		return TRUE;
	}

	return FALSE;
}


/* --------------------------------------------------------------------
Function: set_is_empty()

Date: 14/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: checks if the set is empty

Input: Set*

Output: TRUE if the set is full

------------------------------------------------------------------- */
BOOL set_is_empty(Set* set) {
	if(set->num_ids == 0) return TRUE;
	else return FALSE;
}


/* --------------------------------------------------------------------
Function: set_create()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: creates a new set

Input: 

Output: Set* (created set)

------------------------------------------------------------------- */
Set* set_create() {
	int i;

	Set* set = NULL;

	set = (Set*) malloc (sizeof(Set));
	if(!set) return NULL;

	for(i = 0; i < MAX_IDS; i++) {
		set->id[i] = NO_ID;
	}

	set->num_ids = 0;

	return set;
}


/* --------------------------------------------------------------------
Function: set_destroy()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a set

Input: Set* 

Output: OK if it was successfuly destroyed

------------------------------------------------------------------- */
STATUS set_destroy(Set* set) {
	if(!set) return ERROR;

	free(set);
	return OK;
}


/* --------------------------------------------------------------------
Function: set_add()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: adds something to a given set

Input: Set* , Id (the id of the thing we want to add)

Output: OK if it was successfuly added

------------------------------------------------------------------- */
STATUS set_add(Set* set, Id id) {

	if(set_where_is_id(set, id) != NOT_FOUND || !set || id == NO_ID || set_is_full(set) == TRUE){
		return ERROR;
	}

	set->id[set->num_ids] = id;
	set->num_ids++;

	return OK;
}


/* --------------------------------------------------------------------
Function: set_delete()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: deletes the id from the set if it's inside

Input: Set* , Id (the id of the thing we want to delete)

Output: OK if it was successfuly deleted

------------------------------------------------------------------- */
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


/* --------------------------------------------------------------------
Function: set_print()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints the set's array

Input: Set*

Output: OK if it was successfuly printed

------------------------------------------------------------------- */
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


/* --------------------------------------------------------------------
Function: set_get_num_ids()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gives the number of stored ids

Input: Set*

Output: the number of stored ids

------------------------------------------------------------------- */
int set_get_num_ids(Set* set) {
	if(!set) return NOT_FOUND;

	return set->num_ids;
}

/* --------------------------------------------------------------------
Function: set_is_id()

Date: 14/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: returns TRUE if the id is inside the set

Input: Set*, Id

Output: TRUE if the Id is inside the set

------------------------------------------------------------------- */
BOOL set_is_id(Set* set, Id id){
	if(set_where_is_id(set, id) == NOT_FOUND){
		return FALSE;
	}

	return TRUE;
}