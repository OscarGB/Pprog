/**
 * @brief It implements the inventory
 * @file inventory.h
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 5/11/2016
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include "types.h"

typedef struct _Inventory Inventory; /* !< Definition of the Inventory structure */

BOOL inventory_is_full(Inventory* bag);
BOOL inventory_is_empty(Inventory* bag);

/**
* @brief Creates a new inventory for the game
* @author José Ignacio Gómez
* @date 5/11/2016
* @param None
* @return Inventory* (The created Inventory)
*/
Inventory* inventory_create(int size);

/**
* @brief Destroyes an inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return STATUS
*/
STATUS inventory_destroy(Inventory* bag);

/**
* @brief Adds an item to the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, Id (of the item) 
* @return STATUS
*/
STATUS inventory_add_item(Inventory* bag, Id id);

/**
* @brief Deletes an item from the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, Id (item Id)
* @return STATUS
*/
STATUS inventory_delete_item(Inventory* bag, Id id);

/**
* @brief Gets the set of items from the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return Set*
*/
Set* inventory_get_set(Inventory* bag);

/**
* @brief Gets the size of the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return int size
*/
int inventory_get_size(Inventory* bag);

/**
* @brief Sets the size of the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*, int size
* @return STATUS
*/
STATUS inventory_set_size(Inventory* bag, int size);

/**
* @brief Gets the number of items in the inventory
* @author José Ignacio Gómez
* @date 6/11/2016
* @param Inventory*
* @return STATUS
*/
int inventory_get_num_items(Inventory* bag);

/**
* @brief Prints the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return STATUS
*/
STATUS inventory_print(Inventory* bag);

#endif
