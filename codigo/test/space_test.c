#include "test.h"
#include "space.h"

#define MAX_TESTS 26
#define ID 1


BOOL test_space1(){ /*!< Test space_create */
	BOOL res= FALSE;
	Space* space = NULL;

	space = space_create(ID);
	if(!space){
		space_destroy(space);
		TEST_PRINT(res);
		return res;
	}
	res = TRUE;
	space_destroy(space);
	TEST_PRINT(res);
	return res;
	
}

BOOL test_space2(){ /*!< Test space_destroy with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;
	STATUS res=ERROR;

	space = space_create(ID);
	if(!space){
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}

	res = space_destroy(space);
	if(res == OK)
		result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space3(){ /*!< Test space_destroy with not alloc'd space*/
	Space *space = NULL;	
	STATUS res=OK;
	BOOL result=FALSE;

	res = space_destroy(space);

	if(res==ERROR)
		result=TRUE;
	TEST_PRINT(result);
	return result;
}


BOOL test_space4(){ /*!< Test space_get_name with alloc'd space*/
	Space* space = NULL;
	BOOL result = FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(strcmp(space_get_name(space), "\0") == 0){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}

	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space5(){ /*!< Test space_set_name with alloc'd space*/
	Space* space = NULL;
	STATUS res1=FALSE, res2=FALSE;
	BOOL result=FALSE;
	const char* name;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}
	res1=space_set_name(space, "NAME");
	name=space_get_name(space);
	if(!strcmp(name, "NAME")) res2=OK;
	space_destroy(space);
	if(res1==OK && res2==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_space6(){ /*!< Test space_get_north with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_north(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}



BOOL test_space7(){ /*!< Test space_set_north and space_get_north with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;
	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_north(space, ID);
	test=space_get_north(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space8(){ /*!< Test space_get_south with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_south(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space9(){ /*!< Test space_set_south with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_south(space, ID);
	test=space_get_south(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space10(){ /*!< Test space_get_east with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_east(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space11(){ /*!< Test space_set_east with alloc'd space*/
		
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_east(space, ID);
	test=space_get_east(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space12(){ /*!< Test space_get_west with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_west(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space13(){ /*!< Test space_set_west with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_west(space, ID);
	test=space_get_west(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space14(){ /*!< Test space_add_object and space_is_object_in with alloc'd space*/

	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	space_add_object(space, ID);
	result=space_is_object_in(space, ID);
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space15(){ /*!< Test space_get_objects with alloc'd space*/
	
	Set* set = NULL;
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	space_add_object(space, 100);
	set=space_get_objects(space);
	if(set_delete(set, 100)==OK) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space16(){ /*!< Test space_print with alloc'd space*/
	Space* space;
	BOOL result=FALSE;
	space= space_create(ID);
	if(space_print(space)==OK) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;;
}

BOOL test_space17(){ /*Test space_get_gdesc with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(strcmp(space_get_gdesc(space), "") == 0){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}

	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space18(){ /*Test space_set_gdesc with alloc'd space*/

	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);
	space_set_gdesc(space, "NAME");
	if(!strcmp("NAME", space_get_gdesc(space))) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space19(){ /*!< Test space_get_up with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_up(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space20(){ /*!< Test space_set_up with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_up(space, ID);
	test=space_get_up(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space21(){ /*!< Test space_get_down with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_down(space) == NO_ID){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space22(){ /*!< Test space_set_down with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_down(space, ID);
	test=space_get_down(space);
	if(test==ID) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space23(){ /*Test space_get_adesc with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(strcmp(space_get_adesc(space), "") == 0){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}

	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space24(){ /*Test space_set_adesc with alloc'd space*/

	Space* space;
	BOOL result=FALSE;
	space = space_create(ID);
	space_set_adesc(space, "NAME");
	if(!strcmp("NAME", space_get_adesc(space))) result=TRUE;
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}


BOOL test_space25(){ /*!< Test space_get_light with alloc'd space*/
	Space* space = NULL;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}

	if(space_get_light(space) == TRUE){
		result = TRUE;
		space_destroy(space);
		TEST_PRINT(result);
		return result;
	}
		
	space_destroy(space);
	TEST_PRINT(result);
	return result;
}

BOOL test_space26(){ /*!< Test space_set_light with alloc'd space*/
	
	Space* space = NULL;
	Id test=-1;
	BOOL result=FALSE;

	space = space_create(ID);
	if(!space){
		TEST_PRINT(result);
		return result;
	}


	space_set_light(space, FALSE);
	test=space_get_light(space);
	if(test==FALSE) result=TRUE;
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
	if(todas || test == 13) test_space13();
	if(todas || test == 14) test_space14();
	if(todas || test == 15) test_space15();
	if(todas || test == 16) test_space16();
	if(todas || test == 17) test_space17();
	if(todas || test == 18) test_space18();
	if(todas || test == 19) test_space19();
	if(todas || test == 20) test_space20();
	if(todas || test == 21) test_space21();
	if(todas || test == 22) test_space22();
	if(todas || test == 23) test_space23();
	if(todas || test == 24) test_space24();
	if(todas || test == 25) test_space25();
	if(todas || test == 26) test_space26();



	PRINT_RESULTS();

	return 0;
}
