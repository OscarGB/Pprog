/* ===================================================================
File: space.c

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the game spaces for each command 

Revision history: none

=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"

struct _Space {
    Id id;
    char name[WORD_SIZE + 1];
    Id north;
    Id south;
    Id east;
    Id west;
    Set *object;
    char gdesc[3][7];
};

/* --------------------------------------------------------------------
Function: space_create()

Date: 23/09/2016   

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Creates a new space for the game

Input: Id id (The id for the new space)

Output: Space* (The created space)

------------------------------------------------------------------- */

Space* space_create(Id id) {
    int i;

    Space *newSpace = NULL;

    if (id == NO_ID)
        return NULL;

    newSpace = (Space *) malloc(sizeof (Space));

    if (newSpace == NULL) {
        return NULL;
    }
    newSpace->id = id;

    newSpace->name[0] = '\0';

    newSpace->north = NO_ID;
    newSpace->south = NO_ID;
    newSpace->east = NO_ID;
    newSpace->west = NO_ID;

    newSpace->object = set_create();
    if(!newSpace->object){
        space_destroy(newSpace);
        return NULL;
    }

    for(i = 0; i <= 2; i++){
        newSpace->gdesc[i] = "";
    }

    return newSpace;
}

/* --------------------------------------------------------------------
Function: space_destroy();

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: destroys a non-empty space

Input: space* space (the space that is gonna be destroyed)

Output: a STATUS return: OK if the space was destroyed, ERROR if it wasn't

------------------------------------------------------------------- */
STATUS space_destroy(Space* space) {
    if (!space) {
        return ERROR;
    }
    set_destroy(space->object);
    free(space);
    space = NULL;

    return OK;
}

/* --------------------------------------------------------------------
Function: space_set_name()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the name of a space

Input: Space* space (The space that has to be changed)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */

STATUS space_set_name(Space* space, char* name) {
    if (!space || !name) {
        return ERROR;
    }

    if (!strcpy(space->name, name)) {
        return ERROR;
    }

    return OK;
}

/* --------------------------------------------------------------------
Function: space_set_north()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the north space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the north)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */

STATUS space_set_north(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->north = id;
    return OK;
}

/* --------------------------------------------------------------------
Function: space_set_south()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the south space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the south)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */

STATUS space_set_south(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->south = id;
    return OK;
}

/* --------------------------------------------------------------------
Function: space_set_east()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the east space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the east)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */

STATUS space_set_east(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->east = id;
    return OK;
}

/* --------------------------------------------------------------------
Function: space_set_west()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Sets the west space for the given one

Input:  Space* Space (The space which need to be set)
        Id id (The id of the space located at the west)

Output: STATUS (OK if everything went well, ERROR if something went wrong)

------------------------------------------------------------------- */

STATUS space_set_west(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->west = id;
    return OK;
}

/* --------------------------------------------------------------------
Function: space_add_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it defines if a given space has an object inside

Input:  Space* space (the space we want to know about)
        Id id (the id of the object)

Output: a STATUS return: OK if everything went well, ERROR if it wasn't

------------------------------------------------------------------- */
STATUS space_add_object(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }

    return set_add(space->object, id);
}

/* --------------------------------------------------------------------
Function: space_get_name()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns the name of a given space

Input: Space* space (the space we want to know about)

Output: char* (the name of the space)

------------------------------------------------------------------- */
const char * space_get_name(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->name;
}

/* --------------------------------------------------------------------
Function: space_get_id()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns the Id of a given space

Input: Space* space (the space we want to know about)

Output: Id (the Id of the space)

------------------------------------------------------------------- */
Id space_get_id(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->id;
}

/* --------------------------------------------------------------------
Function: space_get_north()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the north space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the north)

------------------------------------------------------------------- */

Id space_get_north(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->north;
}

/* --------------------------------------------------------------------
Function: space_get_south()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the south space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the south)

------------------------------------------------------------------- */

Id space_get_south(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->south;
}

/* --------------------------------------------------------------------
Function: space_get_east()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the east space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the east)

------------------------------------------------------------------- */

Id space_get_east(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->east;
}

/* --------------------------------------------------------------------
Function: space_get_west()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Gets the id of the west space for the given one

Input:  Space* Space (The space to evaluate)

Output: Id id (The id of the space located at the west)

------------------------------------------------------------------- */

Id space_get_west(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->west;
}

/* --------------------------------------------------------------------
Function: space_get_object()

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: it returns TRUE if there's an object in the space

Input: Space* space (the space we want to know about)

Output: Id (The Id of the object)

------------------------------------------------------------------- */

Set* space_get_object(Space* space) {
    if (!space) {
        return FALSE;
    }

    return space->object;
}

/* --------------------------------------------------------------------
Function: space_is_object_in()

Date: 14/10/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: Checks if the object is in the given space

Input: Space* (The space to check)
       Id (The id to find)

Output: BOOL (TRUE if its in the space, FALSE if error or isn't in the space)

------------------------------------------------------------------- */

BOOL space_is_object_in(Space* space, Id id){
    if(!space || id == NO_ID){
        return FALSE;
    }
    return set_is_id(space->object, id);
}

/* --------------------------------------------------------------------
Function: space_print

Date: 23/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: prints the given space in the standard output

Input: Space *space (The space to be printed)

Output STATUS (OK if everything went well, ERROR if something went wrong)
------------------------------------------------------------------- */

STATUS space_print(Space* space) {
    Id idaux = NO_ID;
    int i;
  
    if (!space) {
        return ERROR;
    }

    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
    
    idaux = space_get_north(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No north link.\n");
    }
    
    idaux = space_get_south(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No south link.\n");
    }
    
    idaux = space_get_east(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No east link.\n");
    }
    
    idaux = space_get_west(space);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No west link.\n");
    }
    
   if (set_is_empty(space_get_object(space)) == FALSE) {
        fprintf(stdout, "---> Object in the space.\n");
    } else {
        fprintf(stdout, "---> No object in the space.\n");
    }

    for(i = 0; i <= 2; i++){
        fprintf(stdout, "%s\n", space->gdesc[i]);
    }

    return OK;
}

STATUS space_set_gdesc(Space* space, char** gdesc){
    int i;

    if(!space || !gdesc){
        return ERROR;
    }

    for(i = 0; i < 3; i++){
        strcpy(space->gdesc[i], gdesc[i]);
    }

    return OK;
}

char** space_get_gdesc(Space* space){
    if(!space){
        return NULL;
    }

    return space->gdesc;
}

