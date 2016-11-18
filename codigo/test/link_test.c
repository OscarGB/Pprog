/**
 * @brief Main to test the Link module
 * @file link_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 17/11/2016
 */

#include "test.h"
#include "link.h"
#include "types.h"

#define MAX_TESTS 31
#define ID 3
#define ID1 5
#define ID2 8
#define NAME "Testing"


BOOL test_link1(){
	Link* link = NULL;
	link = link_create(NO_ID);
	if(!link){
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link2(){
	Link* link = NULL;
	link = link_create(ID);
	if(!link){
		return FALSE;
	}
	link_destroy(link);
	return TRUE;
}

BOOL test_link3(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_id(link) == ID){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link4(){
	Link* link = NULL;
	link = link_create(ID);
	if(strcmp(link_get_name(link), "") == 0){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link5(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_state(link) == OPEN){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link6(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_conection1(link) == NO_ID){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link7(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_conection2(link) == NO_ID){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link8(){
	if(link_get_id(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link9(){
	if(link_get_name(NULL) == NULL){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link10(){
	if(link_get_state(NULL) == OPEN){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link11(){
	if(link_get_conection1(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link12(){
	if(link_get_conection2(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link13(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_name(link, NAME) == OK){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link14(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_name(link, NAME);
	if(strcmp(link_get_name(link), NAME) == 0){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link15(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection1(link, ID1) == OK){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link16(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection2(link, ID2) == OK){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link17(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_conection1(link, ID1);
	if(link_get_conection1(link) == ID1){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link18(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_conection2(link, ID2);
	if(link_get_conection2(link) == ID2){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link19(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_state(link, CLOSED) == OK){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link20(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_state(link, CLOSED);
	if(link_get_state(link) == CLOSED){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link21(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_name(link, NULL) == ERROR){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link22(){
	if(link_set_name(NULL, NAME) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link23(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection1(link, NO_ID) == ERROR){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link24(){
	if(link_set_conection1(NULL, ID1) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link25(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection2(link, NO_ID) == ERROR){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link26(){
	if(link_set_conection2(NULL, ID2) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link27(){
	if(link_set_state(NULL, CLOSED) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link28(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_state(link, 12) == ERROR){
		link_destroy(link);
		return TRUE;
	}
	link_destroy(link);
	return FALSE;
}

BOOL test_link29(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_destroy(link) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link30(){
	if(link_destroy(NULL) == ERROR){
		return TRUE;
	}
	return TRUE;
}

BOOL test_link31(){
	if(link_print(NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}

int main(int argc, char* argv[]){
	int test = 0;
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
	if(todas || test == 31) TEST_PRINT(test_link31());


	PRINT_RESULTS();

	return 0;
}
