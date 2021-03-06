/**
 * @brief It defines the inventory
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
* @brief Checks if the inventory is full
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return BOOL (TRUE if full)
*/

BOOL inventory_is_full(Inventory* bag);

/**
* @brief Checks if the inventory is empty
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return BOOL (TRUE if empty)
*/

BOOL inventory_is_empty(Inventory* bag);

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
* @param Inventory*
* @param Id (item Id)
* @return STATUS
*/
STATUS inventory_delete_item(Inventory* bag, Id id);

/**
* @brief Sets the set of items of the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @param Set*
* @return STATUS
*/
STATUS inventory_set_set(Inventory* bag, Set* set);

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
* @param Inventory*
* @param int size
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
* @brief Search for an item in the inventory
* @author José Ignacio Gómez
* @date 9/12/2016
* @param Inventory*
* @param bag
* @return BOOL
*/
BOOL inventory_is_in(Inventory* bag, Id id);

/**
* @brief Prints the inventory
* @author José Ignacio Gómez
* @date 5/11/2016
* @param Inventory*
* @return STATUS
*/
STATUS inventory_print(Inventory* bag);

/**
* @brief Returns a string with the names of the objects, for the dialogue
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Inventory*
* @return char* string
*/
long* inventory_get_ids(Inventory* bag);

#endif
