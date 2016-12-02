/**
 * @brief Main to test the Graphics module
 * @file die_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 02/12/2016
 */

#include "graphics.h"
#include "test.h"
#include "types.h"
#include <unistd.h>


#define MAX_TESTS 1
#define DELAY 1

BOOL test_graphics1(){
	Graphics* gra = NULL;
	gra = graphics_create();
	if(!gra){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics2(){
	Graphics* gra = NULL;
	gra = graphics_create();
	if(graphics_destroy(gra) == ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Graphics:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Graphics: \n", test);
	}

	if(todas || test == 1) test_graphics1();
	if(todas || test == 2) test_graphics2();

	PRINT_RESULTS();

	return 0;
}