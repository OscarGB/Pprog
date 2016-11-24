/**
 * @brief Main to test the Inventory module
 * @file inventory_test.c
 * @author Andrea Ruiz
 * @version 1.0
 * @date 20/11/2016
 */

#include "test.h"
#include "inventory.h"
#include "types.h"
 
#define MAX_TESTS 24
#define SIZE 4
#define ID 1

/*<! Test to see if functions work when they are used properly */

BOOL test_inventory1(){ /*<! inventory_create */
	Inventory *inventory = NULL;
	inventory = inventory_create(SIZE);

	if(!inventory){
		return FALSE;
	}

	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory2(){ /*<! inventory_destroy */
 	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);

	if(!inventory){
		return FALSE;
	}

	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory3(){ /*<! inventory_is_full */
	Inventory * inventory = NULL;
	int i;
	inventory = inventory_create(SIZE);

	for(i=1; i<=SIZE; i++)
		inventory_add_item(inventory, i);

	if(inventory_is_full(inventory) == TRUE){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;

}

BOOL test_inventory4(){ /*<! inventory_is_empty */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_is_empty(inventory) == TRUE){
		inventory_destroy(inventory);
		return TRUE;		
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory5(){ /*<! inventory_add_item */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_add_item(inventory, ID) == OK){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory6(){ /*<! inventory_delete_item */
	Inventory * inventory = NULL;
	inventory = inventory_create(SIZE);

	inventory_add_item(inventory, ID);
	if(inventory_delete_item(inventory, ID) == OK){
		inventory_destroy(inventory);
		return TRUE;
	}
	
	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory7(){ /*<! inventory_set_set */
	Inventory * inventory = NULL;
	Set * set = NULL;
	inventory = inventory_create(SIZE);
	set = set_create(SIZE);

	set_add(set, ID);
	if(inventory_set_set(inventory, set) == OK){
		inventory_destroy(inventory);
		return TRUE;
	}
	
	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory8(){ /*<! inventory_get_set */
	Inventory * inventory = NULL;
	Set * set = NULL;
	inventory = inventory_create(SIZE);
	set = set_create(SIZE);

	set_add(set, ID);
	inventory_set_set(inventory, set);
	if(inventory_get_set(inventory) == set){
		inventory_destroy(inventory);
		return TRUE;
	}
	
	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory9(){ /*<! inventory_get_size */
	Inventory * inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_get_size(inventory) == SIZE){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory10(){ /*<! inventory_set_size */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);
	
	if(inventory_set_size(inventory, 2*SIZE) == OK){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory11(){ /*<! inventory_get_num_items */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);
	
	if(inventory_get_num_items(inventory) == 0){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory12(){ /*<! inventory_print */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);
	
	if(inventory_print(inventory) == OK){
		inventory_destroy(inventory);
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

/*<! Test to see if functions don't work when they aren't used properly */

BOOL test_inventory13(){ /*<! inventory_create */
	Inventory *inventory = NULL;
	inventory = inventory_create(-1);

	if(!inventory){
		return TRUE;
	}

	inventory_destroy(inventory);
	return FALSE;
}

BOOL test_inventory14(){ /*<! inventory_destroy */
 	Inventory* inventory = NULL;

	if(inventory_destroy(inventory) == ERROR)
		return TRUE;

	return FALSE;
}

BOOL test_inventory15(){ /*<! inventory_is_full */
	Inventory * inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_is_full(inventory) == TRUE){
		inventory_destroy(inventory);
		return FALSE;
	}

	inventory_destroy(inventory);
	return TRUE;

}

BOOL test_inventory16(){ /*<! inventory_is_empty */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);

	inventory_add_item(inventory, ID);
	if(inventory_is_empty(inventory) == TRUE){
		inventory_destroy(inventory);
		return FALSE;		
	}

	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory17(){ /*<! inventory_add_item */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_add_item(inventory, NO_ID) == OK){
		inventory_destroy(inventory);
		return FALSE;
	}

	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory18(){ /*<! inventory_delete_item */
	Inventory * inventory = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_delete_item(inventory, ID) == OK){
		inventory_destroy(inventory);
		return FALSE;
	}
	
	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory19(){ /*<! inventory_set_set */
	Inventory * inventory = NULL;
	Set * set = NULL;
	inventory = inventory_create(SIZE);

	if(inventory_set_set(inventory, set) == OK){
		inventory_destroy(inventory);
		return FALSE;
	}
	
	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory20(){ /*<! inventory_get_set */
	Inventory * inventory = NULL;
	Set * set = NULL;
	inventory = inventory_create(SIZE);
	set = set_create(SIZE);

	set_add(set, ID);
	inventory_set_set(inventory, set);
	if(inventory_get_set(inventory) != set){
		inventory_destroy(inventory);
		return FALSE;
	}
	
	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory21(){ /*<! inventory_get_size */
	Inventory * inventory = NULL;

	if(inventory_get_size(inventory) == -1){
		return TRUE;
	}

	return FALSE;
}

BOOL test_inventory22(){ /*<! inventory_set_size */
	Inventory* inventory = NULL;
	inventory = inventory_create(SIZE);
	
	if(inventory_set_size(inventory, -1) == OK){
		inventory_destroy(inventory);
		return FALSE;
	}

	inventory_destroy(inventory);
	return TRUE;
}

BOOL test_inventory23(){ /*<! inventory_get_num_items */
	Inventory* inventory = NULL;
	
	if(inventory_get_num_items(inventory) != -1){
		return FALSE;
	}

	return TRUE;
}

BOOL test_inventory24(){ /*<! inventory_print */
	Inventory* inventory = NULL;
	
	if(inventory_print(inventory) == OK){
		return FALSE;
	}

	return TRUE;
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

	if(todas || test == 1) TEST_PRINT(test_inventory1());
	if(todas || test == 2) TEST_PRINT(test_inventory2());
	if(todas || test == 3) TEST_PRINT(test_inventory3());
	if(todas || test == 4) TEST_PRINT(test_inventory4());
	if(todas || test == 5) TEST_PRINT(test_inventory5());
	if(todas || test == 6) TEST_PRINT(test_inventory6());
	if(todas || test == 7) TEST_PRINT(test_inventory7());
	if(todas || test == 8) TEST_PRINT(test_inventory8());
	if(todas || test == 9) TEST_PRINT(test_inventory9());
	if(todas || test == 10) TEST_PRINT(test_inventory10());
	if(todas || test == 11) TEST_PRINT(test_inventory11());
	if(todas || test == 12) TEST_PRINT(test_inventory12());
	if(todas || test == 13) TEST_PRINT(test_inventory13());
	if(todas || test == 14) TEST_PRINT(test_inventory14());
	if(todas || test == 15) TEST_PRINT(test_inventory15());
	if(todas || test == 16) TEST_PRINT(test_inventory16());
	if(todas || test == 17) TEST_PRINT(test_inventory17());
	if(todas || test == 18) TEST_PRINT(test_inventory18());
	if(todas || test == 19) TEST_PRINT(test_inventory19());
	if(todas || test == 20) TEST_PRINT(test_inventory20());
	if(todas || test == 21) TEST_PRINT(test_inventory21());
	if(todas || test == 22) TEST_PRINT(test_inventory22());
	if(todas || test == 23) TEST_PRINT(test_inventory23());
	if(todas || test == 24) TEST_PRINT(test_inventory24());


	PRINT_RESULTS();

	return 0;
}
