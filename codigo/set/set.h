/**
 * @brief It defines the capability of store sets of things
 * @file set.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 07/10/2016
 * @revision_history none
 */

#ifndef SET_H
#define SET_H

#define MAX_IDS 1000 /*!< The max amount of objects	is 4*/

#include "types.h"

typedef struct _Set Set; /*!<Definition of the Set structure*/

/*
* @brief creates a new set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param none
* @return Set* (created set)
*/

Set* set_create();


/*
* @brief destroys a set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer (set to destroy)
* @return STATUS (OK if it was successfuly destroyed)
*/

STATUS set_destroy(Set* set);


/*
* @brief adds something to a given set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param Set* , Id (the id of the thing we want to add)
* @return STATUS (OK if it was successfuly added)
*/

STATUS set_add(Set* set, Id id);


/*
* @brief deletes the id from the set if it's inside
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param Set* , Id (the id of the thing we want to delete)
* @return STATUS (OK if it was successfuly deleted)
*/

STATUS set_delete(Set* set, Id id);


/*
* @brief prints the set's array
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer
* @return STATUS (OK if it was successfuly printed)
*/

STATUS set_print(Set* set);


/*
* @brief gives the number of stored ids
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 07/10/2016
* @param set pointer
* @return the number of stored ids
*/

int set_get_num_ids(Set* set);


/*
* @brief checks if the set is full
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param Set* (the set to inspect)
* @return BOOL (TRUE if the set is full)
*/

BOOL set_is_full(Set* set);


/*
* @brief checks if the set is empty
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param Set* (the set to inspect)
* @return BOOL (TRUE if the set is empty)
*/

BOOL set_is_empty(Set* set);


/*
* @brief Checks if id is in the set
* @author Óscar Gómez, Jose Ignacio Gómez
* @date 14/10/2016
* @param set pointer, id
* @return BOOL (returns TRUE if the id is inside the set)
*/

BOOL set_is_id(Set* set, Id id);

#endif
