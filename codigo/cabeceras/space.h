/* ===================================================================
File: space.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the game spaces for each command 

Revision history: none

=================================================================== */


#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#include "types.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

/* --------------------------------------------------------------------
Function: space_create()

Date: 23/09/2016   

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Creates a new space for the game

Input: Id id (The id for the new space)

Output: Space* (The created space)

------------------------------------------------------------------- */
Space* space_create(Id id);

/* --------------------------------------------------------------------
Function: space_destroy();

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a non-empty space

Input: space* space (the space that is gonna be destroyed)

Output: a STATUS return: OK if the space was destroyed, ERROR if it wasn't

------------------------------------------------------------------- */
STATUS space_destroy(Space* space);

/* --------------------------------------------------------------------
Function: space_get_id()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns the Id of a given space

Input: Space* space (the space we want to know about)

Output: Id (the Id of the space)

------------------------------------------------------------------- */
Id space_get_id(Space* space);

/* --------------------------------------------------------------------
Function: space_set_name()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the name of a space

Input: Space* space (The space that has to be changed)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS space_set_name(Space* space, char* name);

/* --------------------------------------------------------------------
Function: space_get_name()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns the name of a given space

Input: Space* space (the space we want to know about)

Output: char* (the name of the space)

------------------------------------------------------------------- */
const char* space_get_name(Space* space);

/* --------------------------------------------------------------------
Function: space_set_north()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the north space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the north)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS space_set_north(Space* space, Id id);

/* --------------------------------------------------------------------
Function: space_get_north()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the north space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the north)

------------------------------------------------------------------- */
Id space_get_north(Space* space);

/* --------------------------------------------------------------------
Function: space_set_south()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the south space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the south)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS space_set_south(Space* space, Id id);

/* --------------------------------------------------------------------
Function: space_get_south()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the south space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the south)

------------------------------------------------------------------- */
Id space_get_south(Space* space);

/* --------------------------------------------------------------------
Function: space_set_east()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the east space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the east)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS space_set_east(Space* space, Id id);

/* --------------------------------------------------------------------
Function: space_get_east()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the east space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the east)

------------------------------------------------------------------- */
Id space_get_east(Space* space);

/* --------------------------------------------------------------------
Function: space_set_west()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the west space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the west)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */
STATUS space_set_west(Space* space, Id id);

/* --------------------------------------------------------------------
Function: space_get_west()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the west space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the west)

------------------------------------------------------------------- */
Id space_get_west(Space* space);

/* --------------------------------------------------------------------
Function: space_add_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it defines if a given space has an object inside

Input:  Space* space (the space we want to know about)
        Id id (the id of the object)

Output: a STATUS return: OK if everything went well, ERROR if it wasn't

------------------------------------------------------------------- */
STATUS space_add_object(Space* space, Id value);

/* --------------------------------------------------------------------
Function: space_get_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns TRUE if there's an object in the space

Input: Space* space (the space we want to know about)

Output: Id (The Id of the object)

------------------------------------------------------------------- */
Set* space_get_object(Space* space);

/* --------------------------------------------------------------------
Function: space_print

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints the given space in the standard output

Input: Space *space (The space to be printed)

Output STATUS (OK if everything went well, ERROR if something went wrong)
------------------------------------------------------------------- */
STATUS space_print(Space* space);

/* --------------------------------------------------------------------
Function: space_is_object_in()

Date: 14/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Checks if the object is in the given space

Input: Space* (The space to check)
       Id (The id to find)

Output: BOOL (TRUE if its in the space, FALSE if error or isn't in the space)

------------------------------------------------------------------- */
BOOL space_is_object_in(Space* space, Id id);

/* --------------------------------------------------------------------
Function: space_set_gdesc()

Date: 27/10/16

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: returns OK if the gdesc has been successfuly set

Input: Space* , char** the gdesc

Output: OK if it was successfuly set

------------------------------------------------------------------- */
STATUS space_set_gdesc(Space* space, char** gdesc);

/* --------------------------------------------------------------------
Function: space_set_gdesc()

Date: 27/10/16

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: returns OK if the gdesc has been successfuly set

Input: Space* , char** the gdesc

Output: OK if it was successfuly set

------------------------------------------------------------------- */
STATUS space_set_gdesc(Space* space, char** gdesc);

#endif
