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
Function: space_set_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it defines if a given space has an object inside

Input:  Space* space (the space we want to know about)
        BOOL value (TRUE if there's an object inside, FALSE if not)

Output: a STATUS return: OK if everything went well, ERROR if it wasn't

------------------------------------------------------------------- */
STATUS space_set_object(Space* space, BOOL value);

/* --------------------------------------------------------------------
Function: space_get_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns TRUE if there's an object in the space

Input: Space* space (the space we want to know about)

Output: BOOL (TRUE if there's an object, FALSE it there isn't)

------------------------------------------------------------------- */
BOOL space_get_object(Space* space);

/* --------------------------------------------------------------------
Function: space_print

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints the given space in the standard output

Input: Space *space (The space to be printed)

Output STATUS (OK if everything went well, ERROR if something went wrong)
------------------------------------------------------------------- */
STATUS space_print(Space* space);

#endif
