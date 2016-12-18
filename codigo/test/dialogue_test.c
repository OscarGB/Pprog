/**
 * @brief Main to test the Dialogue module
 * @file dialogue_test.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 18/12/2016
 */

#include "dialogue.h"
#include "command.h"
#include "graphics.h"
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
	objects[2] = NULL;

	if(dialogue_standard(gra, dia, objects, string) == ERROR){
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
	objects[2] = NULL;

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
	objects[2] = NULL;

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
	objects[2] = NULL;

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
	objects[2] = NULL;

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
	objects[2] = NULL;

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


/*Dialogue_generic with NULL objects*/
BOOL test_dialogue14(){
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
BOOL test_dialogue15(){
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

	strcpy(inventory[0], "OBJ1\n");
	strcpy(inventory[1], "OBJ2\n");
	inventory[2] = NULL;

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
BOOL test_dialogue17(){
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
BOOL test_dialogue18(){
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
BOOL test_dialogue19(){
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
BOOL test_dialogue20(){
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
	PRINT_RESULTS();

	return 0;
}
