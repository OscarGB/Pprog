/**
 * @brief It implements the inventory
 * @file inventory.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 5/11/2016
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "types.h"
 #include "set.h"
 #include "inventory.h"

 struct _Inventory {
 	Set *set;
 	int size;
 };

/* !< Private functions*/

BOOL inventory_is_full(Inventory* bag) {
	if (set_get_num_ids(bag->set) == bag->size){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL inventory_is_empty(Inventory* bag) {
	if (set_get_num_ids(bag->set) == 0){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/* !< Public functions*/

/**
* @brief Creates a new inventory for the game
* @author José Ignacio Gómez
* @date 5/11/2016
* @param None
* @return Inventory* (The created Inventory)
*/
Inventory* inventory_create(Set* set, int size) {
	Inventory* bag = NULL;

	if (!set || size <= 0 || set_get_num_ids(set) > size) {
		return NULL;
	}

	bag = (Inventory *)malloc(sizeof(Inventory));
	if (!bag) {
		return NULL;
	}

	bag->set = set;
	bag->size = size; /* !< the size of the bag
						will be set outside the inventory
						module in order to modify the size
						of the bag during the game*/

	return bag;
}

/**
* @brief Destroyes an inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return STATUS
*/
STATUS inventory_destroy(Inventory* bag) {
	if (!bag) {
		return ERROR;
	}

	set_destroy(bag->set);
	free(bag);
	bag = NULL;

	return OK;
}

/**
* @brief Adds an item to the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, Id (of the item) 
* @return STATUS
*/
STATUS inventory_add_item(Inventory* bag, Id id) {

	if (!bag || id == NO_ID) {
		return ERROR;
	}
	if (inventory_is_full(bag) == TRUE) {
		return ERROR;
	}

	return set_add(bag->set, id);
}

/**
* @brief Deletes an item from the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, Id (item Id)
* @return STATUS
*/
STATUS inventory_delete_item(Inventory* bag, Id id) {

	if (!bag || id == NO_ID) {
		return ERROR;
	}
	if (inventory_is_empty(bag) == TRUE) {
		return ERROR;
	}

	return set_delete(bag->set, id);
}

/**
* @brief Gets the set of items from the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return Set*
*/
Set* inventory_get_set(Inventory* bag) {

	if (!bag) return NULL;

	return bag->set;
}

/**
* @brief Gets the size of the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return int size
*/
int inventory_get_size(Inventory* bag) {

	if(!bag) return NULL;

	return bag->size;
}

/**
* @brief Sets the size of the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, int size
* @return STATUS
*/
STATUS inventory_set_size(Inventory* bag, int size) {

	if (!bag || size < 0) {
		return ERROR;
	}
	if (size < set_get_num_ids(bag->set)){
		return ERROR;
	}

	bag->size = size;
}

/**
* @brief Prints the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return STATUS
*/
STATUS inventory_print(Inventory* bag) {

	if(!bag) return ERROR;

	fprintf(stdout, "Inventory size: %d\n", bag->set);

	set_print(bag->set);

	return OK;
}