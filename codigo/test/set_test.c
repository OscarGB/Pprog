#include "test.h"
#include "space.h"

#define MAX_TESTS 17
#define ID 1

BOOL test_set1(){ /*!< Test set_create*/
	BOOL res= FALSE;
	Set* set=NULL;
	set = set_create();
	if(set!=NULL) res=TRUE;
	set_destroy(set);
	TEST_PRINT(res);
	return res;
	
}

BOOL test_set2(){ /*!< Test set_destroy with alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	STATUS res=ERROR;
	set = set_create();
	res=set_destroy(set);
	if(res==OK) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_set3(){ /*!< Test set_destroy with not alloc'd set*/
	STATUS res=OK;
	BOOL result=FALSE;
	res=set_destroy(NULL);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}


BOOL test_set4(){ /*!< Test set_add with alloc'd set*/
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

BOOL test_set5(){ /*!< Test set_add with not alloc'd set*/
	Set* set=NULL;
	STATUS res=FALSE;
	BOOL result=FALSE;;
	
	res=set_add(set, ID);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_set6(){ /*!< Test set_delete with alloc'd set*/
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

BOOL test_set7(){ /*!< Test set_delete on a not added id with alloc'd set*/
	Set* set;
	STATUS res=FALSE;
	BOOL result=FALSE;

	set = set_create();
	
	res=set_delete(set, ID);

	set_destroy(set);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_set8(){ /*!< Test set_delete with not alloc'd set*/
	Set* set=NULL;
	STATUS res=FALSE;
	BOOL result=FALSE;
	
	set_add(set, ID);
	res=set_delete(set, ID);
	if(res==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;
}

BOOL test_set9(){ /*!< Test set_print with alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	if(set_print(set)==OK) result=TRUE;
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set10(){ /*!< Test set_print with not alloc'd set*/
	Set* set=NULL;
	BOOL result=FALSE;
	if(set_print(set)==ERROR) result=TRUE;
	TEST_PRINT(result);
	return result;;
}

BOOL test_set11(){ /*!< Test set_is_empty with empty alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	result=set_is_empty(set);
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set12(){ /*!< Test set_is_empty with not empty alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	set_add(set, ID);
	result=!(set_is_empty(set));
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set13(){ /*!< Test set_is_empty with not alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	set_add(set, ID);
	result=!(set_is_empty(set));
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set14(){ /*!< Test set_is_full with not full alloc'd set*/
	Set* set;
	BOOL result=FALSE;
	set= set_create();
	set_add(set, ID);
	result=!(set_is_full(set));
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set15(){ /*!< Test set_is_full with full alloc'd set*/
	int i;
	Set* set=NULL;
	BOOL result=FALSE;
	set= set_create();
	for(i=0; i<MAX_IDS; i++){
		set_add(set, ID+i);
	}
	result=set_is_full(set);
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set16(){ /*!< Test set_is_full with not alloc'd set*/
	Set* set=NULL;
	BOOL result=FALSE;
	set= set_create();
	result=!(set_is_full(set));
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set17(){ /*!< Test set_get_num_ids with alloc'd set*/
	Set* set=NULL;
	BOOL result=FALSE;
	set= set_create();
	set_add(set, ID);
	set_add(set, ID+1);
	set_add(set, ID+2);
	if(set_get_num_ids(set)==3) result=TRUE;
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
}

BOOL test_set18(){ /*!< Test set_is_id with alloc'd set*/
	Set* set=NULL;
	BOOL result=FALSE;
	set= set_create();
	set_add(set, ID+7);
	if(set_is_id(set,ID+7)) result=TRUE;
	set_destroy(set);
	TEST_PRINT(result);
	return result;;
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
	if(todas || test == 12) test_set13();
	if(todas || test == 12) test_set14();
	if(todas || test == 12) test_set15();
	if(todas || test == 12) test_set16();
	if(todas || test == 12) test_set17();
	if(todas || test == 12) test_set18();



	PRINT_RESULTS();

	return 0;
}
