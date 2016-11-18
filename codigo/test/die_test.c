/**
 * @brief Main to test the Die module
 * @file die_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 17/11/2016
 */

#include "test.h"
#include "die.h"
#include "types.h"
 
#define MAX_TESTS 14
#define ID 3


BOOL test_die1(){
	Die *die = NULL;
	die = die_create(NO_ID);
	if(die == NULL){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die2(){
 	Die* die = NULL;
	die = die_create(ID);
	if(!die){
		return FALSE;
	}
	die_destroy(die);
	return TRUE;
}

BOOL test_die3(){
	Die* die = NULL;
	die = die_create(ID);
	if(die_get_id(die) == ID){
		die_destroy(die);
		return TRUE;
	}
	die_destroy(die);
	return FALSE;
}

BOOL test_die4(){
	if(die_get_id(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die5(){
	Die* die = NULL;
	int roll;
	die = die_create(ID);
	roll = die_roll(die, 1, 6);
	if(roll < 1 || roll > 6){
		die_destroy(die);
		return FALSE;
	}
	die_destroy(die);
	return TRUE;
}

BOOL test_die6(){
	Die* die = NULL;
	int roll;
	die = die_create(ID);
	roll = die_roll(die, 1, 6);
	if(die_get_last_roll(die) == roll){
		die_destroy(die);
		return TRUE;
	}
	die_destroy(die);
	return FALSE;
}

BOOL test_die7(){
	if(die_roll(NULL, 1, 6) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die8(){
	Die* die = NULL;
	die = die_create(ID);
	if(die_roll(die, -1, 1) == -1){
		die_destroy(die);
		return TRUE;
	}
	die_destroy(die);
	return FALSE;
}

BOOL test_die9(){
	Die* die = NULL;
	die = die_create(ID);
	if(die_roll(die, 1, -1) == -1){
		die_destroy(die);
		return TRUE;
	}
	die_destroy(die);
	return FALSE;
}

BOOL test_die10(){
	Die* die = NULL;
	die = die_create(ID);
	if(die_roll(die, 6, 1) == -1){
		die_destroy(die);
		return TRUE;
	}
	die_destroy(die);
	return FALSE;
}

BOOL test_die11(){
	if(die_get_last_roll(NULL) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die12(){
	if(die_print(NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die13(){
	Die* die = NULL;
	die = die_create(ID);
	if(die_destroy(die) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die14(){
	if(die_destroy(NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}


int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Die:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Die: \n", test);
	}

	if(todas || test == 1) TEST_PRINT(test_die1());
	if(todas || test == 2) TEST_PRINT(test_die2());
	if(todas || test == 3) TEST_PRINT(test_die3());
	if(todas || test == 4) TEST_PRINT(test_die4());
	if(todas || test == 5) TEST_PRINT(test_die5());
	if(todas || test == 6) TEST_PRINT(test_die6());
	if(todas || test == 7) TEST_PRINT(test_die7());
	if(todas || test == 8) TEST_PRINT(test_die8());
	if(todas || test == 9) TEST_PRINT(test_die9());
	if(todas || test == 10) TEST_PRINT(test_die10());
	if(todas || test == 11) TEST_PRINT(test_die11());
	if(todas || test == 12) TEST_PRINT(test_die12());
	if(todas || test == 13) TEST_PRINT(test_die13());
	if(todas || test == 14) TEST_PRINT(test_die14());

	PRINT_RESULTS();

	return 0;
}
