/**
 * @brief Main to test the Object module
 * @file object_test.c
 * @author Óscar Pinto Santamaría
 * @version 1.0
 * @date 17/11/2016
 */

#include "test.h"
#include "object.h"
#include "types.h"

#define MAX_TESTS 31
#define ID 3
#define ID1 5
#define ID2 8
#define NAME "TRIFORCE"
#define TEST_CHAR A


BOOL test_object1(){ /*!< Test object_create && object_destroy with invalid id*/
	Object* object = NULL;
	object = object_create(NO_ID);
	if(!object){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object2(){ /*!< Test object_create && object_destroy with valid id*/

	Object* object = NULL;
	object = object_create(ID);
	if(!object){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	object_destroy(object);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_object3(){ /*!< Test object_get_id with valid id in created object*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_id(object) == ID){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object4(){ /*!< Test object_get_name with no name*/

	Object* object = NULL;
	object = object_create(ID);
	if(!strcmp(object_get_name(object), "") == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object5(){ /*!< Test object_get_symbol with no char*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_symbol(object) == CHAR_ERROR){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object6(){ /*!< Test object_get_location with default location*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(object_get_location(object) == NO_ID){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object7(){ /*!< Test object_get_desc with default location*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(strcmp(object_get_desc(object), "") == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object8(){ /*!< Test object_get_mdesc with default location*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(strcmp(object_get_mdesc(object), "") == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object9(){ /*!< Test object_get_movable with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_movable(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object10(){ /*!< Test object_get_moved with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_moved(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object11(){ /*!< Test object_get_light with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_light(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object12(){ /*!< Test object_get_hidden with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_hidden(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object13(){ /*!< Test object_get_on_off with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object14(){ /*!< Test object_get_open with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_open(object) == NO_ID){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object15(){ /*!< Test object_get_open with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_duration(object) == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object16(){ /*!< Test object_set_id with valid id*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_id(object, ID1);
	if(object_get_id(object) == ID1 && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object17(){ /*!< Test object_set_name with name*/

	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_name(object, NAME);
	if(!strcmp(object_get_name(object), NAME) == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object18(){ /*!< Test object_set_symbol char*/

	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_symbol(object, TEST_CHAR);
	if(object_get_symbol(object) == TEST_CHAR){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object19(){ /*!< Test object_set_location */
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_location(object, ID2);
	if(object_get_location(object) == ID2){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object20(){ /*!< Test object_get_desc with default location*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(strcmp(object_get_desc(object), "") == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object8(){ /*!< Test object_get_mdesc with default location*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(strcmp(object_get_mdesc(object), "") == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object9(){ /*!< Test object_get_movable with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_movable(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object10(){ /*!< Test object_get_moved with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_moved(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object11(){ /*!< Test object_get_light with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_light(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object12(){ /*!< Test object_get_hidden with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_hidden(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object13(){ /*!< Test object_get_on_off with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object14(){ /*!< Test object_get_open with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_open(object) == NO_ID){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object15(){ /*!< Test object_get_open with default location*/

	Object* object = NULL;
	object = object_create(ID);
	if(object_get_duration(object) == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object28(){
	Object* object = NULL;
	object = object_create(ID);
	if(object_set_state(object, 12) == ERROR){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object29(){
	Object* object = NULL;
	object = object_create(ID);
	if(object_destroy(object) == OK){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object30(){
	if(object_destroy(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object31(){
	if(object_print(NULL) == ERROR){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object32(){
	if(object_open(NULL) != ERROR){
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
		printf("Pasando todas las pruebas al modulo Object:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Object: \n", test);
	}


	if(todas || test == 1) test_object1();
	if(todas || test == 2) test_object2();
	if(todas || test == 3) test_object3();
	if(todas || test == 4) test_object4();
	if(todas || test == 5) test_object5();
	if(todas || test == 6) test_object6();
	if(todas || test == 7) test_object7();
	if(todas || test == 8) test_object8();
	if(todas || test == 9) test_object9();
	if(todas || test == 10) test_object10();
	if(todas || test == 11) test_object11();
	if(todas || test == 12) test_object12();
	if(todas || test == 13) test_object13();
	if(todas || test == 14) test_object14();
	if(todas || test == 15) test_object15();
	if(todas || test == 16) test_object16();
	if(todas || test == 17) test_object17();
	if(todas || test == 18) test_object18();
	if(todas || test == 19) test_object19();
	if(todas || test == 20) test_object20();
	if(todas || test == 21) test_object21();
	if(todas || test == 22) test_object22();
	if(todas || test == 23) test_object23();
	if(todas || test == 24) test_object24();
	if(todas || test == 25) test_object25();
	if(todas || test == 26) test_object26();
	if(todas || test == 27) test_object27();
	if(todas || test == 28) test_object28();
	if(todas || test == 29) test_object29();
	if(todas || test == 30) test_object30();
	if(todas || test == 31) test_object31();
	if(todas || test == 32) test_object32();


	PRINT_RESULTS();

	return 0;
}
