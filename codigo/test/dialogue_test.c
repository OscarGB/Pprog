/**
 * @brief Main to test the Dialogue module
 * @file dialogue_test.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 18/12/2016
 */

#include "dialogue.h"
#include "command.h"
#include "test.h"
#include "types.h"
#include <unistd.h>

/*Creates a dialogue*/
BOOL test_dialogue1(){
	Dialogue* dia = NULL;
	Command* cmd = NULL;

	cmd = command_create();
	if(!cmd){
		TEST_PRINT(FALSE);
		return FALSE;
	}

	dia = dialogue_create();
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
BOOL test_dialogue(){
	if(dialogue_destroy(NULL) == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

/*Test for dialogue_print*/
BOOL test_dialogue(){
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
BOOL test_dialogue(){
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
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_standard(gra, dia, objects, "Testing: \n") == ERROR){
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL graphics*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_standard(gra, dia, objects, "Testing: \n") != ERROR){
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL dialogue*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_standard(gra, dia, objects, "Testing: \n") != ERROR){
		free(objects);
		command_destroy(cmd);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_standard with NULL objects*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_standard(gra, dia, objects, "Testing: \n") != ERROR){
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
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, OK, objects, gra) == ERROR){
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Dialogue_generic with ERROR status*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, ERROR, objects, gra) == ERROR){
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Dialogue_generic with NULL dialogue*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;

	gra = graphics_create();

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, ERROR, objects, gra) != ERROR){
		free(objects);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Dialogue_generic with NULL graphics*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	objects = (char**) malloc (3 * sizeof(char*));
	if(!objects){
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	strcpy(objects[0], "OBJ1\n");
	strcpy(objects[1], "OBJ2\n");
	objects[2] = NULL;

	if(dialogue_generic(dia, ERROR, objects, gra) != ERROR){
		free(objects);
		command_destroy(cmd);
		dialogue_destroy(dia);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(objects);
	command_destroy(cmd);
	dialogue_destroy(dia);

	TEST_PRINT(TRUE);
	return TRUE;
}


/*Dialogue_generic with NULL objects*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** objects = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

	cmd = command_create();

	dia = dialogue_create(cmd);

	gra = graphics_create();

	if(dialogue_generic(dia, ERROR, objects, gra) != ERROR){
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

/*Testing dialogue_inspect SPACE*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, SPACE) == ERROR){
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect INVENTORY*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(inventory[0], "OBJ1\n");
	strcpy(inventory[1], "OBJ2\n");
	inventory[2] = NULL;

	if(dialogue_inspect(dia, OK, inventory, gra, INVENTORY) == ERROR){
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}

/*Testing dialogue_inspect OBJECT*/
BOOL test_dialogue(){
	Dialogue* dia = NULL;
	char** inventory = NULL;
	Graphics* gra = NULL;
	Command* cmd = NULL;

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

	strcpy(inventory[0], "DESCRIPTION\n");

	if(dialogue_inspect(dia, OK, inventory, gra, OBJECT) == ERROR){
		free(inventory);
		command_destroy(cmd);
		dialogue_destroy(dia);
		graphics_destroy(gra);

		TEST_PRINT(FALSE);
		return FALSE;
	}

	free(inventory);
	command_destroy(cmd);
	dialogue_destroy(dia);
	graphics_destroy(gra);

	TEST_PRINT(TRUE);
	return TRUE;
}
