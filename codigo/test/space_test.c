#include "test.h"
#include "space.h"

#define MAX_TESTS 24
#define ID 1
#define GET_NAME(x) #x
#define NAME GET_NAME(default)


BOOL test_space1(){ /*<! Test space_create with id and space_get_id*/
	Id test=-1;
	BOOL res= FALSE;
	Space* space;
	space = space_create(ID);
	test = space_get_id(space);
	if(test == ID) res=TRUE;
	space_destroy(space);
	TEST_PRINT(res);
	return res;
	
}

BOOL test_space2(){ /*<! Test space_destroy with alloc'd space*/
	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);
	space_destroy(space);
	if(space==NULL) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space3(){ /*<! Test space_destroy with not alloc'd space*/
	STATUS res=OK;
	BOOL result=FALSE;
	res=space_destroy(NULL);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}


BOOL test_space4(){ /*<! Test space_get_name and space_set_name with alloc'd space*/
	Space* space;
	STATUS res1=FALSE, res2=FALSE;
	BOOL result=FALSE;
	char* name;

	space = space_create(ID);
	res1=space_set_name(space, NAME);
	name=space_get_name(space);
	if(!strcmp(name, NAME)) res2=OK;
	space_destroy(space);
	if(res1==OK && res2==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
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

BOOL test_space11(){
	Space* space;
	BOOL result=FALSE;
	space= space_create(ID);
	if(space_print(space)==OK) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;;
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

	if(todas || test == 1) test_space1();
	if(todas || test == 2) test_space2();
	if(todas || test == 3) test_space3();
	if(todas || test == 4) test_space4();
	if(todas || test == 5) test_space5();
	if(todas || test == 6) test_space6();
	if(todas || test == 7) test_space7();
	if(todas || test == 8) test_space8();
	if(todas || test == 9) test_space9();
	if(todas || test == 10) test_space10();
	if(todas || test == 11) test_space11();
	if(todas || test == 12) test_space12();



	PRINT_RESULTS();

	return 0;
}
