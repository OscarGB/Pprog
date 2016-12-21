/**
 * @brief Main to test the Object module
 * @file object_test.c
 * @author Óscar Pinto Santamaría
 * @version 1.0
 * @date 16/12/2016
 */

#include "test.h"
#include "object.h"
#include "types.h"

#define MAX_TESTS 41
#define ID 3
#define ID1 5
#define ID2 8
#define NAME "TRIFORCE"
#define TEST_CHAR 'A'
#define TEST_INT 2728


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
	if(strcmp(object_get_name(object), "") == 0){
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
	if(strcmp(object_get_desc(object), " ") == 0){
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
	if(strcmp(object_get_mdesc(object), " ") == 0){
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
	
	Object* object = NULL;
	object = object_create(ID1);
	if(object_get_id(object) == ID1){
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
	if(strcmp(object_get_name(object), NAME) == 0 && res == OK){
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
	if(object_get_symbol(object) == TEST_CHAR && res == OK){
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
	if(object_get_location(object) == ID2 && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object20(){ /*!< Test object_set_desc*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_desc(object, NAME);
	if(strcmp(object_get_desc(object), NAME) == 0 && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object21(){ /*!< Test object_set_mdesc*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_mdesc(object, NAME);
	if(strcmp(object_get_mdesc(object), NAME) == 0 && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object22(){ /*!< Test object_set_movable*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_movable(object, TRUE);
	if(object_get_movable(object) == TRUE && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object23(){ /*!< Test object_set_moved*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_original_location(object, ID2);
	if(object_get_moved(object) == TRUE && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object24(){ /*!< Test object_set_light*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_light(object, TRUE);
	if(object_get_light(object) == TRUE && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object25(){ /*!< Test object_set_hidden*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_hidden(object, TRUE);
	if(object_get_hidden(object) == TRUE && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object26(){ /*!< Test object_set_on_off*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_on_off(object, TRUE);
	if(object_get_on_off(object) == TRUE && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object27(){ /*!< Test object_set_open*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_open(object, ID2);
	if(object_get_open(object) == ID2 && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object28(){ /*!< Test object_set_duration*/
	
	STATUS res = ERROR;
	Object* object = NULL;
	object = object_create(ID);
	res = object_set_duration(object, TEST_INT);
	if(object_get_duration(object) == TEST_INT && res == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object29(){ /* Test object_turnon with object which can't be turned on (light == FALSE)*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_turnon(object);
	if( object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object30(){ /* Test object_turnon with object which can't be turned on (duration <= 0)*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_light(object, TRUE);
	object_turnon(object);
	if( object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object31(){ /* Test object_turnon with object which can be turned on*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_light(object, TRUE);
	object_set_duration(object, 5);
	object_turnon(object);
	if( object_get_on_off(object) == TRUE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object32(){ /* Test object_turnoff with object which is off*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_on_off(object, FALSE);
	object_turnoff(object);
	if( object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object33(){ /* Test object_turnoff with object which is on*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_on_off(object, TRUE);
	object_turnoff(object);
	if( object_get_on_off(object) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object34(){ /* Test object_decrease_duration with object with light == FALSE*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_decrease_duration(object);
	if( object_get_duration(object) == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object35(){ /* Test object_decrease_duration with object with light == TRUE and on_off == FALSE*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_light(object, TRUE);
	object_decrease_duration(object);
	if( object_get_duration(object) == 0){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object36(){ /* Test object_decrease_duration with object with light == TRUE and on_off == TRUE*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_light(object, TRUE);
	object_set_on_off(object, TRUE);
	object_decrease_duration(object);
	if(object_get_duration(object) == -1){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object37(){ /* Test object_decrease_duration with object with light == TRUE and on_off == TRUE and duration < 0*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_duration(object, -1);
	object_decrease_duration(object);
	if( object_get_duration(object) == -1){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object38(){ /* Test object_can_open with incorrect Id*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_open(object, ID2);
	if(object_can_open(object, ID1) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object39(){ /* Test object_can_open with NO_ID*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_open(object, NO_ID);
	if(object_can_open(object, NO_ID) == FALSE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object40(){ /* Test object_can_open with correct Id*/
	
	Object* object = NULL;
	object = object_create(ID);
	object_set_open(object, ID2);
	if(object_can_open(object, ID2) == TRUE){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_object41(){ /* Test object_can_open with correct Id*/
	
	Object* object = NULL;
	object = object_create(ID);
	if(object_print(stdout, object) == OK){
		object_destroy(object);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	object_destroy(object);
	TEST_PRINT(FALSE);
	return FALSE;
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
	if(todas || test == 33) test_object33();
	if(todas || test == 34) test_object34();
	if(todas || test == 35) test_object35();
	if(todas || test == 36) test_object36();
	if(todas || test == 37) test_object37();
	if(todas || test == 38) test_object38();
	if(todas || test == 39) test_object39();
	if(todas || test == 40) test_object40();
	if(todas || test == 41) test_object41();

	PRINT_RESULTS();

	return 0;
}
