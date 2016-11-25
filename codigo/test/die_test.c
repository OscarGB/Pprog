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
#define FACES 6


BOOL test_die1(){
	Die *die = NULL;
	die = die_create(NO_ID, FACES);
	if(die == NULL){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die2(){
 	Die* die = NULL;
	die = die_create(ID, FACES);
	if(!die){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	die_destroy(die);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_die3(){
	Die* die = NULL;
	die = die_create(ID, FACES);
	if(die_get_id(die) == ID){
		die_destroy(die);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	die_destroy(die);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die4(){
	if(die_get_id(NULL) == NO_ID){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die5(){
	Die* die = NULL;
	int roll;
	die = die_create(ID, FACES);
	roll = die_roll(die);
	if(roll < 1 || roll > 6){
		die_destroy(die);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	die_destroy(die);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_die6(){
	Die* die = NULL;
	int roll;
	die = die_create(ID, FACES);
	roll = die_roll(die);
	if(die_get_last_roll(die) == roll){
		die_destroy(die);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	die_destroy(die);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die7(){
	if(die_roll(NULL) == -1){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die8(){
	Die* die = NULL;
	die = die_create(ID, -2);
	if(die == NULL){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	die_destroy(die);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die9(){
	Die* die = NULL;
	die = die_create(ID, FACES);
	if(die_get_faces(die) == FACES){
		die_destroy(die);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	die_destroy(die);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die10(){
	if(die_get_faces(NULL) == 0){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die11(){
	if(die_get_last_roll(NULL) == -1){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die12(){
	if(die_print(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die13(){
	Die* die = NULL;
	die = die_create(ID, FACES);
	if(die_destroy(die) == OK){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_die14(){
	if(die_destroy(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
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

	if(todas || test == 1) test_die1();
	if(todas || test == 2) test_die2();
	if(todas || test == 3) test_die3();
	if(todas || test == 4) test_die4();
	if(todas || test == 5) test_die5();
	if(todas || test == 6) test_die6();
	if(todas || test == 7) test_die7();
	if(todas || test == 8) test_die8();
	if(todas || test == 9) test_die9();
	if(todas || test == 10) test_die10();
	if(todas || test == 11) test_die11();
	if(todas || test == 12) test_die12();
	if(todas || test == 13) test_die13();
	if(todas || test == 14) test_die14();

	PRINT_RESULTS();

	return 0;
}
