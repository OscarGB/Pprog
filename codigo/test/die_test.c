/**
 * @brief Main to test the Die module
 * @file die_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 17/11/2016
 */

#include "die_test_func.c"

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

	if(test != 0 && test != 13){
		end_test();
	}

	PRINT_RESULTS();

	return 0;
}
