/**
 * @brief Test module for inventory
 * @file link_test.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 6/11/2016
 */

 #include <stdio.h>
 #include "inventory.h"
 #include "set.h"

 int main() {
 	Inventory *bag = NULL; /* !< Bag pointer*/

 	fprintf(stdout, "TESTING INVENTORY MODULE\n");

 	/*Testing inventory_create*/
 	fprintf(stdout, "Creating an inventory\n");
 	bag = inventory_create(4); /*Size 4 inventory*/
 	if(!bag){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: CREATING THE INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_destroy*/
 	fprintf(stdout, "Destroying an inventory\n");
 	if (inventory_destroy(bag) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: DESTROYING THE INVENTORY\n");
 		#endif
 		return 1;
 	}
 	
 	fprintf(stdout, "OK\n");

 	/*Creating an invalid inventory size < 0*/
 	fprintf(stdout, "Creating an inventory with invalid size\n");
 	bag = inventory_create(-1); /*Invalid size inventory*/
 	if(bag != NULL){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: AN INVALID-SIZED INVENTORY HAS BENN CREATED\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_add_item*/
 	fprintf(stdout, "Creating inventory for testing\n");
 	bag = inventory_create(1);
 	if(!bag){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: CREATING THE INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	fprintf(stdout, "Adding item to an empty inventory\n");
 	if(inventory_add_item(bag, 2) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: ADDING AN ITEM TO AN EMPTY INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Now, the inventory is full*/
 	/*Adding item to a full inventory*/
 	fprintf(stdout, "Adding item to a full inventory\n");
 	if(inventory_add_item(bag, 3) != ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: AN ITEM HAS BEEN ADDED TO A FULL INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_set_size*/
 	fprintf(stdout, "Changing the size of the inventory\n");
 	if(inventory_set_size(bag, 2) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: COULDN'T CHANGE THE SIZE OF THE INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Changin the size to an invalid size*/
 	fprintf(stdout, "Changing the size to an invalid size\n");
 	if(inventory_set_size(bag, 0) != ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: INVALID SIZE\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Now, we are going to add a repeated item*/
 	fprintf(stdout, "Adding repeated item\n");
 	if(inventory_add_item(bag, 2) != ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: A REPEATED ITEM HAS BEEN ADDED TO THE INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*The current inventory should have only one item,
 	so we are gonna check it*/

 	/*Testing inventory_get_num_ids*/
 	fprintf(stdout, "Testing inventory_get_num_items()\n");
 	if(inventory_get_num_items(bag) != 1){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: inventory_get_num_items()\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_print*/
 	fprintf(stdout, "Printing inventory with one item\n");
 	if(inventory_print(bag) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: PRINTING INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_get_set*/
 	fprintf(stdout, "Testing inventory_get_set()\n");
 	if(inventory_get_set(bag) == NULL){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: inventory_get_set()\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Deleting an item that is not inside the inventory*/
 	fprintf(stdout, "Deleting an item that is not inside the inventory\n");
 	if(inventory_delete_item(bag, 3) != ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: IT HAS BEEN REMOVED AN ITEM THAT IS NOT INSIDE\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Testing inventory_delete_item*/
 	fprintf(stdout, "Deleting item\n");
 	if(inventory_delete_item(bag, 2) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: DELENTING ITEM\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Now, the inventory is empty*/
 	/*Deleting from an empty inventory*/
 	fprintf(stdout, "Deleting item from an empty inventory\n");
 	if(inventory_delete_item(bag, 2) != ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: AN ITEM HAS BEEN REMOVED FROM AN EMPTY INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");


 	/*Testing inventory_print*/
 	fprintf(stdout, "Printing empty inventory\n");
 	if(inventory_print(bag) == ERROR){
 		#ifdef DEBUG
 		fprintf(stderr, "ERROR DEBUGING: PRINTING INVENTORY\n");
 		#endif
 		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	return 0;
 }