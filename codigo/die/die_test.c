#include <stdio.h>
#include "die.h"
#include "types.h"

int main(){
	Die *die = NULL; /*Die pointer*/
	int roll; /*Variable used to check the rolled values*/

	fprintf(stdout, "TESTING DIE MODULE\n");
	/*Test the die_create*/
	fprintf(stdout, "Creating the die\n");
	die = die_create(1);
	if(!die){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");
	/*Print the default values*/
	die_print(die);

	/*Test destroying the die*/
	fprintf(stdout, "Destroying the die\n");
	if(die_destroy(die) == ERROR){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING THE DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");
	die=NULL;

	/*Testing if we can destroy an uncreated die*/
	fprintf(stdout, "Destroying an uncreated die\n");
	if(die_destroy(die) != ERROR){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING AN UNCREATED DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");

	/*Testing if we ca nroll and uncreated die*/
	fprintf(stdout, "Rolling and uncreated die\n");
	if(die_roll(die, 1, 6) != -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: ROLLING AN UNCREATED DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");

	fprintf(stdout, "Creating the die\n");
	die = die_create(1);
	if(!die){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");
	die_print(die);

	/*Testing if an unrolled die returns last value -1*/
	fprintf(stdout, "Getting last roll\n");
	if(die_get_last_roll(die) != -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: WRONG INITIALIZED DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");

	fprintf(stdout, "Rolling the die\n");
	roll = die_roll(die, 1, 6);
	if(roll == -1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: ROLLING THE DIE\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");
	die_print(die);

	/*Testing if the value is correct*/
	fprintf(stdout, "Getting last roll\n");
	if(die_get_last_roll(die) != roll){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: RETURNING WRONG LAST ROLL\n");
		#endif
		return 1;
	}
	fprintf(stdout, "OK\n");	

	fprintf(stdout, "Getting die id\n");
	if(die_get_id(die) != 1){
		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: RETURNING WRONG ID\n");
		#endif
		return 1;	
	}
	fprintf(stdout, "OK\n");
	fprintf(stdout, "TESTING FINISHED\n");
	
	/*Destroying the die*/
	die_destroy(die);
	return 0;
}