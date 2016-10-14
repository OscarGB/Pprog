#include <stdio.h>
#include "die.h"
#include "types.h"

int main(){
	Die *die = NULL;
	int roll;

	fprintf(stdout, "TESTING DIE MODULE\n");

	fprintf(stdout, "Creating the die\n");
	die = die_create(1);
	if(!die){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE DIE\n");
		#endif
		return 1;
	}
	die_print(die);

	fprintf(stdout, "Destroying the die\n");
	if(die_destroy(die) == ERROR){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING THE DIE\n");
		#endif
		return 1;
	}
	die=NULL;

	fprintf(stdout, "Destroying an uncreated die\n");
	if(die_destroy(die) != ERROR){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING AN UNCREATED DIE\n");
		#endif
		return 1;
	}

	fprintf(stdout, "Rolling and uncreated die\n");
	if(die_roll(die, 1, 6) != -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: ROLLING AN UNCREATED DIE\n");
		#endif
		return 1;
	}

	fprintf(stdout, "Creating the die\n");
	die = die_create(1);
	if(!die){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE DIE\n");
		#endif
		return 1;
	}
	die_print(die);

	fprintf(stdout, "Getting last roll\n");
	if(die_get_last_roll(die) != -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: WRONG INITIALIZED DIE\n");
		#endif
		return 1;
	}

	fprintf(stdout, "Rolling the die\n");
	roll = die_roll(die, 1, 6);
	if(roll == -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: ROLLING THE DIE\n");
		#endif
		return 1;
	}
	die_print(die);

	fprintf(stdout, "Getting last roll\n");
	if(die_get_last_roll(die) != roll){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: RETURNING WRONG LAST ROLL\n");
		#endif
		return 1;
	}	

	fprintf(stdout, "Getting die id\n");
	if(die_get_id(die) != 1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: RETURNING WRONG ID\n");
		#endif
		return 1;	
	}

	die_destroy(die);
	return 0;
}