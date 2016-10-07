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
}

/*Private function*/
BOOL set_is_full(Set* set) {
	int i;
	
	if(set->num_ids = MAX_IDS){
		return TRUE;
	}

	return FALSE;
}

BOOL set_is_empty(Set* set) {
	if(set->num_ids == 0) return TRUE;
	else return FALSE;
}

int set_where_is_id(Set* set, Id id) {
	int i;

	for(i = 0; i < set->num_ids; i++){
		if(set->id[i] == id) return i;
	}

	return NOT_FOUND;
}


/*Public functions*/
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

STATUS set_destroy(Set* set) {
	if(!set) return ERROR;

	free(set);
	return OK;
}

STATUS set_add(Set* set, Id id) {

	if(!set || id == NO_ID || set_is_full(set) == TRUE){
		return ERROR;
	}

	set->id[set->num_ids] = id;
	set->num_ids++;

	return OK;
}

STATUS set_delete(Set* set, Id id) {
	int position;

	if(!set || set_is_empty(set) == TRUE || id == NO_ID){
		return ERROR;
	}

	position = set_where_is_id(set, id);
	if(position == NOT_FOUND) return ERROR;

	set->id[position] = set->id[num_ids-1];
	set->id[num_ids-1] = NO_ID;

	set->num_ids--;
}

STATUS set_print(Set* set) {
	int i;

	if(!set) return ERROR;
	if(set_is_empty(set) == TRUE) return OK;

	fprintf(stdout, "[");
	fprintf(stdout, "%d", set->id[0])
	for(i = 1; i < set->num_ids; i++){
		fprintf(stdout, ", %d", set->id[i]);
	}
	fprintf(stdout, "]\n");

	return OK;
}

int set_get_num_ids(Set* set) {
	if(!set) return NOT_FOUND;

	return set->num_ids;
}