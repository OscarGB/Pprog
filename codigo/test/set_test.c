#include "test.h"
#include "space.h"

#define MAX_TESTS 24
#define ID 1

BOOL test_set1(){ /*<! Test set_create*/
	BOOL res= FALSE;
	Set* set=NULL;
	set = set_create();
	if(set!=NULL) res=TRUE;
	set_destroy(set);
	TEST_PRINT(res);
	return res;
	
}

BOOL test_space2(){ /*<! Test set_destroy with alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	STATUS res=ERROR;
	set = set_create();
	res=set_destroy(set);
	if(res==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space3(){ /*<! Test set_destroy with not alloc'd set*/
	STATUS res=OK;
	BOOL result=FALSE;
	res=set_destroy(NULL);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}


BOOL test_space4(){ /*<! Test set_add with alloc'd set*/
	Set* set;
	STATUS res=FALSE;
	BOOL result=FALSE;

	set = set_create();
	
	res=set_add(set, ID);
	set_destroy(set);
	if(res==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space5(){ /*<! Test set_add with not alloc'd set*/
	Set* set;
	STATUS res=FALSE;
	BOOL result=FALSE;;
	
	res=set_add(set, ID);
	set_destroy(set);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space6(){ /*<! Test set_delete with alloc'd set*/
	Set* set;
	STATUS res=FALSE;
	BOOL result=FALSE;

	set = set_create();
	
	set_add(set, ID);
	res=set_delete(set, ID);

	set_destroy(set);
	if(res==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space7(){ /*<! Test set_delete with not alloc'd set*/
	Set* set;
	STATUS res=FALSE;
	BOOL result=FALSE;
	
	set_add(set, ID);
	res=set_delete(set, ID);

	set_destroy(set);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space8(){ /*<! Test set_print with alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	if(set_print(set)==OK) result=TRUE;
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_space9(){ /*<! Test set_print with not alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	if(set_print(set)==ERROR) result=TRUE;
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_space5(){ /*<! Test space_set_north and space_get_north with alloc'd space*/
	
	Space* space;
	Id test=-1;
	BOOL result=FALSE;
	space = space_create(ID);

	space_set_north(space, ID);
	test=space_get_north(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space6(){ /*<! Test space_set_south and space_get_south with alloc'd space*/
	
	Space* space;
	Id test=-1;
	BOOL result=FALSE;
	space = space_create(ID);

	space_set_south(space, ID);
	test=space_get_south(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space7(){ /*<! Test space_set_east and space_get_east with alloc'd space*/
		
	Space* space;
	Id test=-1;
	BOOL result=FALSE;
	space = space_create(ID);

	space_set_east(space, ID);
	test=space_get_east(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space8(){ /*<! Test space_set_west and space_get_west with alloc'd space*/
	
	Space* space;
	Id test=-1;
	BOOL result=FALSE;
	space = space_create(ID);

	space_set_west(space, ID);
	test=space_get_west(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space9(){ /*<! Test space_add_object and space_is_object_in with alloc'd space*/

	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);

	space_add_object(space, ID);
	result=space_is_object_in(space, ID);
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space10(){ /*<! Test space_get_object with alloc'd space*/
	
	Set* set;
	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);

	space_add_object(space, 100);
	set=space_get_object(space);
	if(set_delete(set, 100)==OK) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space12(){ /*Test space_set_gdesc and space_get_gdesc with alloc'd space*/

	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);
	space_set_gdesc(space, NAME);
	if(!strcmp(NAME, space_get_gdesc(space))) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}



int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Inventory:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Inventory: \n", test);
	}

	if(todas || test == 1) test_set1();
	if(todas || test == 2) test_set2();
	if(todas || test == 3) test_set3();
	if(todas || test == 4) test_set4();
	if(todas || test == 5) test_set5();
	if(todas || test == 6) test_set6();
	if(todas || test == 7) test_set7();
	if(todas || test == 8) test_set8();
	if(todas || test == 9) test_set9();
	if(todas || test == 10) test_set10();
	if(todas || test == 11) test_set11();
	if(todas || test == 12) test_set12();



	PRINT_RESULTS();

	return 0;
}
