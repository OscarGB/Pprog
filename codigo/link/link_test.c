/**
 * @brief Test module for Link
 * @file link_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 4/11/2016
 */

 #include <stdio.h>
 #include <string.h>
 #include "link.h"

 int main(){
 	Link *link = NULL; /*<!Link pointer for checks*/

 	fprintf(stdout, "TESTING LINK MODULE\n");
 	/*Test the link_create*/
 	fprintf(stdout, "Creating the die\n");
 	link = link_create(2);
 	if(!link){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE LINK\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");
 	link_print(link);

 	/*Test the link_get_id*/
 	fprintf(stdout, "Getting the link's Id\n");
 	if(link_get_id(link) != 2){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: LINK'S ID\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking default values on conections*/
 	fprintf(stdout, "Getting the link's conections Ids\n");
 	if(link_get_conection1(link) != NO_ID || link_get_conection2(link) != NO_ID){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DEFAULT LINK'S CONECTIONS ID\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking default value on name*/
 	fprintf(stdout, "Getting the link's name\n");
 	if(strcmp(link_get_name(link),"")){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DEFAULT LINK'S NAME\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking default value on State*/
 	fprintf(stdout, "Getting the link's Id\n");
 	if(link_get_state(link) != OPEN){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DEFAULT LINK'S STATE\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking of link_set_name*/
 	fprintf(stdout, "Setting the link's name\n");
 	if(link_set_name(link, "checking") == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S NAME\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking if the name was correctly set*/
 	fprintf(stdout, "Checking Link's name\n");
 	if(strcmp(link_get_name(link), "checking")){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S NAME IS NOT CORRECT\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking link_set_conection (both)*/
 	fprintf(stdout, "Setting Link's conections\n");
 	if(link_set_conection1(link, 1) == ERROR || link_set_conection2(link, 1) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S CONECTIONS\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking if the conections were correctly set*/
 	fprintf(stdout, "Setting Link's conections\n");
 	if(link_get_conection1(link) != 1 || link_get_conection2(link) != 1){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S CONECTIONS IS NOT CORRECT\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking link_set_state*/
 	fprintf(stdout, "Setting Link's State\n");
 	if(link_set_state(link, CLOSED) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S STATE\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking if the state was correctly set*/
 	fprintf(stdout, "Setting Link's State\n");
 	if(link_get_state(link) != CLOSED){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING LINK'S STATE IS NOT CORRECT\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");
 	link_print(link);

 	/*Destroying the link*/
 	fprintf(stdout, "Destroying the Link\n");
 	if(link_destroy(link) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING THE LINK\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");
 	link = NULL;

 	/*Destroying an uncreated link*/
 	fprintf(stdout, "Destroying an uncreated Link\n");
 	if(link_destroy(link) != ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: DESTROYING AN UNCREATED LINK\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Checking link_print for an uncreated link*/
 	fprintf(stdout, "Printing an uncreated Link\n");
 	if(link_print(link) != ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: PRINTING AN UNCREATED LINK\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	return 0;

 }