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
#define NAME "ZELDA"


BOOL test_link1(){
	Link* link = NULL;
	link = link_create(NO_ID);
	if(!link){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link2(){
	Link* link = NULL;
	link = link_create(ID);
	if(!link){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	link_destroy(link);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_link3(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_id(link) == ID){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link4(){
	Link* link = NULL;
	link = link_create(ID);
	if(strcmp(link_get_name(link), "") == 0){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link5(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_state(link) == OPENL){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link6(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_conection1(link) == NO_ID){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link7(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_get_conection2(link) == NO_ID){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link8(){
	if(link_get_id(NULL) == NO_ID){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link9(){
	if(link_get_name(NULL) == NULL){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link10(){
	if(link_get_state(NULL) == OPENL){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link11(){
	if(link_get_conection1(NULL) == NO_ID){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link12(){
	if(link_get_conection2(NULL) == NO_ID){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link13(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_name(link, NAME) == OK){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link14(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_name(link, NAME);
	if(strcmp(link_get_name(link), NAME) == 0){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link15(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection1(link, ID1) == OK){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link16(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection2(link, ID2) == OK){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link17(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_conection1(link, ID1);
	if(link_get_conection1(link) == ID1){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link18(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_conection2(link, ID2);
	if(link_get_conection2(link) == ID2){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link19(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_state(link, CLOSEDL) == OK){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link20(){
	Link* link = NULL;
	link = link_create(ID);
	link_set_state(link, CLOSEDL);
	if(link_get_state(link) == CLOSEDL){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link21(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_name(link, NULL) == ERROR){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link22(){
	if(link_set_name(NULL, NAME) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link23(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection1(link, NO_ID) == ERROR){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link24(){
	if(link_set_conection1(NULL, ID1) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link25(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_conection2(link, NO_ID) == ERROR){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link26(){
	if(link_set_conection2(NULL, ID2) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link27(){
	if(link_set_state(NULL, CLOSEDL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link28(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_set_state(link, 12) == ERROR){
		link_destroy(link);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	link_destroy(link);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link29(){
	Link* link = NULL;
	link = link_create(ID);
	if(link_destroy(link) == OK){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link30(){
	if(link_destroy(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link31(){
	if(link_print(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_link32(){
	if(link_open(NULL) != ERROR){
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


	if(todas || test == 1) test_link1();
	if(todas || test == 2) test_link2();
	if(todas || test == 3) test_link3();
	if(todas || test == 4) test_link4();
	if(todas || test == 5) test_link5();
	if(todas || test == 6) test_link6();
	if(todas || test == 7) test_link7();
	if(todas || test == 8) test_link8();
	if(todas || test == 9) test_link9();
	if(todas || test == 10) test_link10();
	if(todas || test == 11) test_link11();
	if(todas || test == 12) test_link12();
	if(todas || test == 13) test_link13();
	if(todas || test == 14) test_link14();
	if(todas || test == 15) test_link15();
	if(todas || test == 16) test_link16();
	if(todas || test == 17) test_link17();
	if(todas || test == 18) test_link18();
	if(todas || test == 19) test_link19();
	if(todas || test == 20) test_link20();
	if(todas || test == 21) test_link21();
	if(todas || test == 22) test_link22();
	if(todas || test == 23) test_link23();
	if(todas || test == 24) test_link24();
	if(todas || test == 25) test_link25();
	if(todas || test == 26) test_link26();
	if(todas || test == 27) test_link27();
	if(todas || test == 28) test_link28();
	if(todas || test == 29) test_link29();
	if(todas || test == 30) test_link30();
	if(todas || test == 31) test_link31();
	if(todas || test == 32) test_link32();


	PRINT_RESULTS();

	return 0;
}
