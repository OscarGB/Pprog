#include <stdlib.h>
#include "set.h"
#include "types.h"

int main() {
	Set *set = NULL;
	int i;

	fprintf(stdout, "TESTING SET MODULE\n");

	/*Creating and testing a new set*/
	fprintf(stdout, "Creating new set...\n");
	set = set_create();
	if(!set) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: CREATING SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Testing set_is_empty()*/
	fprintf(stdout, "Testing set_is_empty() function:\n");
	if(set_is_empty(set) != TRUE) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: Set_is_empty() NOT WORKING\n");
		#endif
	}
	else fprintf(stdout, "OK\n");


	/*Testing set_add() function*/
	fprintf(stdout, "Adding Id to empty set:\n");
	if(set_add(set, 1) == ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: ADDING ID TO EMPTY SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	fprintf(stdout, "Adding Id to non-empty set:\n");
	if(set_add(set, 2) == ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: ADDING ID TO NON-EMPTY SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Testing set_get_num_ids()*/
	fprintf(stdout, "Testing set_get_num_ids() function:\n");
	if(set_get_num_ids(set) != 2) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: set_get_num_ids() NOT WORKING\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Testing set_is_id()*/
	fprintf(stdout, "Testing set_is_id() function:\n");
	if(set_is_id(set, 1) != TRUE) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: set_is_id() NOT WORKING\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	fprintf(stdout, "Adding repeated Id to the set:\n");
	if(set_add(set, 1) != ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: A REPEATED ID HAS BEEN ADDED\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Filling the set*/
	i = 3;
	while(set_is_full(set) != TRUE){
		set_add(set, i);
	}

	/*Testing set_is_full()*/
	fprintf(stdout, "Testing set_is_full()");
	if(set_get_num_ids(set) != MAX_IDS){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: set_is_full() NOT WORKING\n");
		#endif
	}

	/*Adding Id to full set*/
	fprintf(stdout, "Adding Id to filled set:\n");
	if(set_add(set, 1) != ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: AN ID HAS BEEN ADDED TO A FILLED SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Testing set_delete() function*/
	fprintf(stdout, "Deleting Id from a filled set:\n");
	if(set_delete(set, 1) == ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: DELETING AN ID\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	fprintf(stdout, "Deleting Id from a non-filled set:\n");
	if(set_delete(set, 2) == ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: DELETING AN ID\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	fprintf(stdout, "Deleting Id that is not inside the set:\n");
	if(set_delete(set, 1) != ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: DELETED AN ID THAT IS NOT INSIDE THE SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Destroying the current set and creating a new one in order to
	test the set_delete() function over an empty set*/
	set_detroy(set);
	set = set_create();

	fprintf(stdout, "Deleting Id from an empty set:\n");
	if(set_delete(set, 1) != ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: DELETED AN ID FROM AN EMPTY SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	/*Destroying the set and testing the destroyed set*/
	fprintf(stdout, "Destroying the set:\n");
	if(set_destroy(set) == ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: DESTROYING SET\n");
		#endif
	}
	else fprintf(stdout, "OK\n");

	fprintf(stdout, "Destroying an uncreated set:\n");
	if(set_destroy(set) != ERROR) {
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGGING: UNCREATED SET DESTROYED\n");
		#endif
	}
	else fprintf(stdout, "OK\n");


}