#include "link_test_func.c"

int main(int argc, char* argv[]){
	int test;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Link:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Link: \n", test);
	}


	if(todas || test == 1) TEST_PRINT(test_link1());
	if(todas || test == 2) TEST_PRINT(test_link2());
	if(todas || test == 3) TEST_PRINT(test_link3());
	if(todas || test == 4) TEST_PRINT(test_link4());
	if(todas || test == 5) TEST_PRINT(test_link5());
	if(todas || test == 6) TEST_PRINT(test_link6());
	if(todas || test == 7) TEST_PRINT(test_link7());
	if(todas || test == 8) TEST_PRINT(test_link8());
	if(todas || test == 9) TEST_PRINT(test_link9());
	if(todas || test == 10) TEST_PRINT(test_link10());
	if(todas || test == 11) TEST_PRINT(test_link11());
	if(todas || test == 12) TEST_PRINT(test_link12());
	if(todas || test == 13) TEST_PRINT(test_link13());
	if(todas || test == 14) TEST_PRINT(test_link14());
	if(todas || test == 15) TEST_PRINT(test_link15());
	if(todas || test == 16) TEST_PRINT(test_link16());
	if(todas || test == 17) TEST_PRINT(test_link17());
	if(todas || test == 18) TEST_PRINT(test_link18());
	if(todas || test == 19) TEST_PRINT(test_link19());
	if(todas || test == 20) TEST_PRINT(test_link20());
	if(todas || test == 21) TEST_PRINT(test_link21());
	if(todas || test == 22) TEST_PRINT(test_link22());
	if(todas || test == 23) TEST_PRINT(test_link23());
	if(todas || test == 24) TEST_PRINT(test_link24());
	if(todas || test == 25) TEST_PRINT(test_link25());
	if(todas || test == 26) TEST_PRINT(test_link26());
	if(todas || test == 27) TEST_PRINT(test_link27());
	if(todas || test == 28) TEST_PRINT(test_link28());
	if(todas || test == 29) TEST_PRINT(test_link29());
	if(todas || test == 30) TEST_PRINT(test_link30());

	PRINT_RESULTS();

	return 0;
}
