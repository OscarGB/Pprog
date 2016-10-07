/* ===================================================================
File: set.h

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the capability of store sets
of things

Revision history: none

=================================================================== */

#ifndef SET_H
#define SET_H

#define MAX_IDS 4 /*We assume the max amount of players
					is 4*/

#include "types.h"

typedef struct _Set Set;


/* --------------------------------------------------------------------
Function: set_create()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: creates a new set

Input: 

Output: Set* (created set)

------------------------------------------------------------------- */
Set* set_create();


/* --------------------------------------------------------------------
Function: set_destroy()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a set

Input: Set* 

Output: OK if it was successfuly destroyed

------------------------------------------------------------------- */
STATUS set_destroy(Set* set);


/* --------------------------------------------------------------------
Function: set_add()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: adds something to a given set

Input: Set* , Id (the id of the thing we want to add)

Output: OK if it was successfuly added

------------------------------------------------------------------- */
STATUS set_add(Set* set, Id id);


/* --------------------------------------------------------------------
Function: set_delete()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: deletes the id from the set if it's inside

Input: Set* , Id (the id of the thing we want to delete)

Output: OK if it was successfuly deleted

------------------------------------------------------------------- */
STATUS set_delete(Set* set, Id id);


/* --------------------------------------------------------------------
Function: set_print()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints the set's array

Input: Set*

Output: OK if it was successfuly printed

------------------------------------------------------------------- */
STATUS set_print(Set* set);


/* --------------------------------------------------------------------
Function: set_get_num_ids()

Date: 07/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: gives the number of stored ids

Input: Set*

Output: the number of stored ids

------------------------------------------------------------------- */
int set_get_num_ids(Set* set);

#endif