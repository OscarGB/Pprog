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

 struct _Inventory {
 	Set *set;
 	int size;
 };


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
	if (!space) {
		return ERROR;
	}

	set_destroy(bag->set);
	free(bag);
	bag = NULL;

	return OK;
}

