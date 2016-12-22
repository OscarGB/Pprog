/**
 * @brief Main to test the Dialogue module
 * @file dialogue_test.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 18/12/2016
 */

#include "dialogue.h"
#include "command.h"
#include "graphic_engine.h"
#include <string.h>
#include "test.h"
#include "types.h"
#include <unistd.h>

#define MAX_TESTS 28

/*Creates a dialogue*/
BOOL test_dialogue1(){
	Dialogue* dia = NULL;
	Command* cmd = NULL;

	cmd = command_create();
	if(!cmd){
		TEST_PRINT(FALSE);
		return FALSE;
	}

	dia = dialogue_create(cmd);
	if(!dia){
		command_destroy(cmd);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Creates a dialogue with NULL command*/
BOOL test_dialogue2(){
	if(dialogue_create(NULL) != NULL){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

/*Destroys a NULL dialogue*/
BOOL test_dialogue3(){
	dialogue_destroy(NULL);
	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_print*/
BOOL test_dialogue4(){
	Graphics* gra = NULL;

	gra = graphics_create();

	if(dialogue_print(gra, "Testing dialogue") == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

/*Dialogue_print with null string*/
BOOL test_dialogue5(){
	Graphics* gra = NULL;

	gra = graphics_create();

	if(dialogue_print(gra, NULL) != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard*/
BOOL test_dialogue6(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;
	char string[MAX_DIALOGUE];

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	strcpy(string, "");

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_standard(gra, dia, objects, string) == ERROR){
		for(i = 0; i < 2; i++){
			free(objects[i]);
		}	

		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL graphics*/
BOOL test_dialogue7(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	char string[MAX_DIALOGUE];
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_standard(gra, dia, objects, string) != ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL dialogue*/
BOOL test_dialogue8(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	char string[MAX_DIALOGUE];
	int i;

	cmd = command_create();

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_standard(gra, dia, objects, string) != ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL objects*/
BOOL test_dialogue9(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	char string[MAX_DIALOGUE];

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_standard(gra, dia, objects, string) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic*/
BOOL test_dialogue10(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Dialogue_generic with ERROR status*/
BOOL test_dialogue11(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_generic(dia, ERROR, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Dialogue_generic with NULL dialogue*/
BOOL test_dialogue12(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	int i;

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_generic(dia, ERROR, objects, gra) != ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Dialogue_generic with NULL graphics*/
BOOL test_dialogue13(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2][0] = '\0';

	if(dialogue_generic(dia, ERROR, objects, gra) != ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Testing dialogue_inspect SPACE*/
BOOL test_dialogue14(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	inventory = (char**) malloc (3 * sizeof(char*));
	if(!inventory){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		inventory[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, SPACE) == ERROR){
		for(i = 0; i < 3; i++){
			free(inventory[i]);
		}
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(inventory[i]);
	}
	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect INVENTORY*/
BOOL test_dialogue15(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	inventory = (char**) malloc (1000 * sizeof(char*));
	if(!inventory){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		inventory[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(inventory[0], "OBJ1\n\0");
	strcpy(inventory[1], "OBJ2\n\0");
	inventory[2][0] = '\0';

	if(dialogue_inspect(dia, OK, inventory, gra, INVENTORY) == ERROR){
		for(i = 0; i < 3; i++){
			free(inventory[i]);
		}
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(inventory[i]);
	}
	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect OBJECT*/
BOOL test_dialogue16(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	inventory = (char**) malloc (3 * sizeof(char*));
	if(!inventory){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		inventory[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, OBJECT) == ERROR){
		for(i = 0; i < 3; i++){
			free(inventory[i]);
		}
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(inventory[i]);
	}
	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect with NULL dialogue*/
BOOL test_dialogue17(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	int i;

	gra = graphics_create();

	inventory = (char**) malloc (3 * sizeof(char*));
	if(!inventory){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		inventory[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, OBJECT) != ERROR){
		for(i = 0; i < 3; i++){
			free(inventory[i]);
		}
		free(inventory);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(inventory[i]);
	}
	free(inventory);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect with NULL graphics*/
BOOL test_dialogue18(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();

	dia = dialogue_create(cmd);

	inventory = (char**) malloc (3 * sizeof(char*));
	if(!inventory){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		inventory[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, OBJECT) != ERROR){
		for(i = 0; i < 3; i++){
			free(inventory[i]);
		}
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(inventory[i]);
	}
	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect with NULL inventory*/
BOOL test_dialogue19(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_inspect(dia, OK, inventory, gra, OBJECT) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show*/
BOOL test_dialogue20(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load_show(gra, dia, str, OK) == ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL dialogue*/
BOOL test_dialogue21(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;

	gra = graphics_create();

	if(dialogue_load_show(gra, dia, str, OK) != ERROR){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL graphics*/
BOOL test_dialogue22(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);


	if(dialogue_load_show(gra, dia, str, OK) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL string*/
BOOL test_dialogue23(){
	Dialogue* dia = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load_show(gra, dia, NULL, OK) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with ERROR STATUS*/
BOOL test_dialogue24(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load_show(gra, dia, str, ERROR) == ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load*/
BOOL test_dialogue25(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load(gra, dia, str, ERROR) == ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL dialogue*/
BOOL test_dialogue26(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;

	gra = graphics_create();

	if(dialogue_load(gra, dia, str, OK) != ERROR){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL graphics*/
BOOL test_dialogue27(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);


	if(dialogue_load(gra, dia, str, OK) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with NULL string*/
BOOL test_dialogue28(){
	Dialogue* dia = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load(gra, dia, NULL, OK) != ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_load_show with ERROR STATUS*/
BOOL test_dialogue29(){
	Dialogue* dia = NULL;
	char str[200] = "Testing string";
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_load(gra, dia, str, ERROR) == ERROR){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_start_game*/
BOOL test_dialogue30(){
	Graphics* gra = NULL;

	gra = graphics_create();

	if(dialogue_start_game(gra) == ERROR){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_start_game with NULL graphics*/
BOOL test_dialogue31(){

	if(dialogue_start_game(NULL) != ERROR){

		TEST_PRINT(FALSE);
		return FALSE;
	}


	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with NO_CMD*/
BOOL test_dialogue32(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, NO_ID);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with UNKNOWN*/
BOOL test_dialogue33(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, UNKNOWN);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with QUIT*/
BOOL test_dialogue34(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, QUIT);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with WIN*/
BOOL test_dialogue35(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, WIN);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with PICK*/
BOOL test_dialogue36(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, PICK);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with DROP*/
BOOL test_dialogue37(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, DROP);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with GO*/
BOOL test_dialogue38(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, GO);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with TURNON*/
BOOL test_dialogue39(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, TURNON);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with TURNOFF*/
BOOL test_dialogue40(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, TURNOFF);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with OPEN*/
BOOL test_dialogue41(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, OPEN);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_generic with HELP*/
BOOL test_dialogue42(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;
	int i;

	cmd = command_create();
	command_set_cmd(cmd, HELP);

	dia = dialogue_create(cmd);

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 2; i++){
		objects[i] = (char*)malloc(100 * sizeof(char));
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		for(i = 0; i < 3; i++){
			free(objects[i]);
		}
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	for(i = 0; i < 3; i++){
		free(objects[i]);
	}
	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}


int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Dialogue:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Dialogue: \n", test);
	}

	if(todas || test == 1) test_dialogue1();
	if(todas || test == 2) test_dialogue2();
	if(todas || test == 3) test_dialogue3();
	if(todas || test == 4) test_dialogue4();
	if(todas || test == 5) test_dialogue5();
	if(todas || test == 6) test_dialogue6();
	if(todas || test == 7) test_dialogue7();
	if(todas || test == 8) test_dialogue8();
	if(todas || test == 9) test_dialogue9();
	if(todas || test == 10) test_dialogue10();
	if(todas || test == 11) test_dialogue11();
	if(todas || test == 12) test_dialogue12();
	if(todas || test == 13) test_dialogue13();
	if(todas || test == 14) test_dialogue14();
	if(todas || test == 15) test_dialogue15();
	if(todas || test == 16) test_dialogue16();
	if(todas || test == 17) test_dialogue17();
	if(todas || test == 18) test_dialogue18();
	if(todas || test == 19) test_dialogue19();
	if(todas || test == 20) test_dialogue20();
	if(todas || test == 21) test_dialogue21();
	if(todas || test == 22) test_dialogue22();
	if(todas || test == 23) test_dialogue23();
	if(todas || test == 24) test_dialogue24();
	if(todas || test == 25) test_dialogue25();
	if(todas || test == 26) test_dialogue26();
	if(todas || test == 27) test_dialogue27();
	if(todas || test == 28) test_dialogue28();
	if(todas || test == 29) test_dialogue29();
	if(todas || test == 30) test_dialogue30();
	if(todas || test == 31) test_dialogue31();
	if(todas || test == 32) test_dialogue32();
	if(todas || test == 33) test_dialogue33();
	if(todas || test == 34) test_dialogue34();
	if(todas || test == 35) test_dialogue35();
	if(todas || test == 36) test_dialogue36();
	if(todas || test == 37) test_dialogue37();
	if(todas || test == 38) test_dialogue38();
	if(todas || test == 39) test_dialogue39();
	if(todas || test == 40) test_dialogue40();
	if(todas || test == 41) test_dialogue41();
	if(todas || test == 42) test_dialogue42();

	PRINT_RESULTS();

	return 0;
}
