/**
 * @brief It implements the game spaces
 * @file space.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 2.0
 * @date 4/11/2016
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"

struct _Space {
	char adesc[MAX_ADESC+1]; /*!<Advanced desc of the space*/
    Id id; /*!<The id of the space*/
    char name[WORD_SIZE + 1]; /*!<the name of the space*/
    Id north; /*!<The id of the link located at the north*/
    Id south; /*!<The id of the link located at the south*/
    Id east; /*!<The id of the link located at the east*/
    Id west; /*!<The id of the link located at the west*/
    Id up; /*!<The id of the link located up*/
    Id down; /*!<The id of the link located down*/
    Set *object; /*!<The objects in the space*/
    BOOL light; /*!<TRUE if the space is illuminated*/
    char gdesc[MAX_GDESC+1]; /*!<The gdesc of the space (The drawing)*/
};/*!<Space structure*/

/**
* @brief Creates a new space for the game
* @author Óscar Gómez
* @date 4/11/2016
* @param Id id(The id for the new space)
* @return Space* (The created space)
*/
Space* space_create(Id id) {

    Space *newSpace = NULL; /*!<The new space to create*/

    if (id == NO_ID)
        return NULL;

    newSpace = (Space *) malloc(sizeof (Space));

    if (newSpace == NULL) {
        return NULL;
    }
    newSpace->id = id;

    /*Default values*/

    newSpace->name[0] = '\0';

    newSpace->north = NO_ID;
    newSpace->south = NO_ID;
    newSpace->east = NO_ID;
    newSpace->west = NO_ID;
    newSpace->up = NO_ID;
    newSpace->down = NO_ID;

    newSpace->object = set_create();
    if(!newSpace->object){
        space_destroy(newSpace);
	    newSpace = NULL;
        return NULL;
    }

    newSpace->light = TRUE;

    strcpy(newSpace->gdesc," ");
    strcpy(newSpace->adesc, " ");

    return newSpace;
}

/**
* @brief destroys a non-empty space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space that is going to be destroyed) 
* @return STATUS (OK if the space was destroyed, ERROR if it wasn't)
*/
STATUS space_destroy(Space* space) {
    if (!space) {
        return ERROR;
    }
    set_destroy(space->object);
    free(space);
    space = NULL;

    return OK;
}

/**
* @brief Sets the name of a Space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space that has to be changed)
* @param char* name (The new name for the space)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_name(Space* space, char* name) {
    if (!space || !name) {
        return ERROR;
    }

    if (!strcpy(space->name, name)) {
        return ERROR;
    }

    return OK;
}

/**
* @brief Sets the Id of the north Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the north)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_north(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->north = id;
    return OK;
}

/**
* @brief Sets the Id of the south Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the south)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_south(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->south = id;
    return OK;
}

/**
* @brief Sets the Id of the east Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the east)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_east(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->east = id;
    return OK;
}

/**
* @brief Sets the Id of the west Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the west)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_west(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->west = id;
    return OK;
}

/**
* @brief Sets the Id of the upper Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located up)
* @return STATUS (OK if everything went well, ERROR if something went wrong)

*/
STATUS space_set_up(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->up = id;
    return OK;
}

/**
* @brief Sets the Id of the lower Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located down)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_down(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }
    space->down = id;
    return OK;
}

/**
* @brief Adds an object to the space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @param Id id (the id of the object)
* @return STATUS (OK if everything went well, ERROR if it wasn't)
*/
STATUS space_add_object(Space* space, Id id) {
    if (!space || id == NO_ID) {
        return ERROR;
    }

    return set_add(space->object, id);
}

/**
* @brief it returns the name of a given space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @return char* (the name of the space)
*/
const char * space_get_name(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->name;
}

/**
* @brief It returns the Id of a given space
* @author José Ignacio Gómez, Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @return Id (the Id of the space)
*/
Id space_get_id(Space* space) {
    if (!space) {
        return NO_ID;
    }

    return space->id;
}

/**
* @brief Gets the id of the Link in the north
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the north)
*/
Id space_get_north(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->north;
}

/**
* @brief Gets the id of the Link in the south
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the south)
*/
Id space_get_south(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->south;
}

/**
* @brief Gets the id of the Link in the east
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the east)
*/
Id space_get_east(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->east;
}

/**
* @brief Gets the id of the Link in the west
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the west)
*/
Id space_get_west(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->west;
}

/**
* @brief Gets the Id of the upper Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @return Id id (The id of the link located up)
*/
Id space_get_up(Space* space) {
    if (!space) {
        return NO_ID;
    }

    return space->up;
}

/**
* @brief Gets the Id of the lower Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @return Id id (The id of the link located down)
*/
Id space_get_down(Space* space) {
    if (!space) {
        return NO_ID;
    }
    
    return space->down;
}

/**
* @brief It returns the Set of objects inside the Space
* @author Óscar Gómez
* @date 4/11/2106
* @param Space* space (the space we want to know about)
* @return Set* (The set inside the Space)
*/
Set* space_get_objects(Space* space) {
    if (!space) {
        return FALSE;
    }

    return space->object;
}

/**
* @brief Checks if the object is in the given space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* (The space to check)
* @param Id (The id to find)
* @return BOOL (TRUE if its in the space, FALSE if error or isn't in the space)
*/
BOOL space_is_object_in(Space* space, Id id){
    if(!space || id == NO_ID){
        return FALSE;
    }
    return set_is_id(space->object, id);
}

/**
* @brief Prints the given space in the standard output
* @author Óscar Gómez
* @date 4/11/2016
* @param Space *space (The space to be printed)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_print(Space* space) {
    Id idaux = NO_ID; /*!<Auxiliar Id*/
	char light[5] = ""; /*!<To check light status*/
  
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
    
   if (set_is_empty(space_get_objects(space)) == FALSE) {
        fprintf(stdout, "---> Object in the space.\n");
    } else {
        fprintf(stdout, "---> No object in the space.\n");
    }

    if(strcmp(space->gdesc, "") == 0)
        fprintf(stdout, "---> No gdesc\n");
    else{
        fprintf(stdout, "---> Gdesc: %s\n", space->gdesc);
    }
	

	if(strcmp(space->adesc, "") == 0){
		fprintf(stdout, "---> No advanced gdesc\n");
    }
	else{
	   	fprintf(stdout, "---> Advanced gdesc: %s\n", space->adesc);
    }
	
	
	if(space_get_light(space) == TRUE){
		strcpy(light, "ON");
    }
	else{
		strcpy(light, "OFF");
    }


	fprintf(stdout, "---> Light: %s\n", light);

    return OK;
}

/**
* @brief Sets the gdesc of a Space
* @author José Ignacio Gómez
* @date 4/11/2016
* @param Space* space (The space to modify)
* @param char* gdesc (The new gdesc)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_gdesc(Space* space, char* gdesc){
 
    if(!space || !gdesc){
        return ERROR;
    }

    strcpy(space->gdesc, gdesc);

    return OK;
}

/**
* @brief Returns the gdesc of a space
* @author José Ignacio Gómez
* @date 4/11/2016
* @param Space* space (The space to inspect)
* @return char* (The gdesc inside the Space)
*/
char* space_get_gdesc(Space* space){
    if(!space){
        return NULL;
    }
 
    return space->gdesc;
}

/**
* @brief Sets the advanced description of a Space
* @author Andrea Ruiz
* @date 2/12/2016
* @param Space* space (The space to modify)
* @param char* adesc (The new adesc)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_adesc(Space* space, char* adesc){

	if(!space || !adesc){
		return ERROR;
	}

	strcpy(space->adesc, adesc);

	return OK;
}

/**
* @brief Returns the advanced description of a space
* @author Andrea Ruiz
* @date 2/12/2016
* @param Space* space (The space to inspect)
* @return char* (The adesc inside the Space)
*/
char* space_get_adesc(Space* space){
    
    if(!space){
        return NULL;
    }
 
    return space->adesc;
}


/**
* @brief Sets the light of the input space
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* space (The space to modify)
* @param BOOL (TRUE to illuminate)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_light(Space* space, BOOL light){
 
    if(!space){
        return ERROR;
    }

    space->light = light;

    return OK;
}

/**

* @brief Gets the light status of the input space
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* space
* @return BOOL (TRUE if illuminated, FALSE if not)

*/
BOOL space_get_light(Space* space){
    if(space == NULL){
        return FALSE;
    }
 
    return space->light;
}

/**
* @brief Changes the gdesc to show an open door
* @author Óscar Gómez
* @date 16/12/2016
* @param Space* space (The space to modify)
* @param DIRECTION (The direction where you open the door)
* @return STATUS (OK if it was successfuly changed)
*/
STATUS space_open_door(Space* space, DIRECTION dir){
    if(!space){
        return ERROR;
    }
    switch(dir){
        case N:
            space->gdesc[4] = '|';
            space->gdesc[5] = ' ';
            space->gdesc[6] = ' ';
            space->gdesc[7] = '|';
            return OK;
        case S:
            space->gdesc[88] = '|';
            space->gdesc[89] = ' ';
            space->gdesc[90] = ' ';
            space->gdesc[91] = '|';
            return OK;
        case W:
            space->gdesc[42] = '-';
            space->gdesc[56] = '_';
            return OK;
        case E:
            space->gdesc[55] = '-';
            space->gdesc[69] = '_';
            return OK;
        default:
            return OK;
    }
}

/**
* @brief Changes the gdesc to show a closed door
* @author Óscar Gómez
* @date 16/12/2016
* @param Space* space (The space to modify)
* @param DIRECTION (The direction where you close the door)
* @return STATUS (OK if it was successfuly changed)
*/
STATUS space_close_door(Space* space, DIRECTION dir){
    if(!space){
        return ERROR;
    }
    switch(dir){
        case N:
            space->gdesc[4] = '|';
            space->gdesc[5] = '*';
            space->gdesc[6] = '*';
            space->gdesc[7] = '|';
            return OK;
        case S:
            space->gdesc[88] = '|';
            space->gdesc[89] = '*';
            space->gdesc[90] = '*';
            space->gdesc[91] = '|';
            return OK;
        case W:
            space->gdesc[32] = ')';
            space->gdesc[46] = ')';
            return OK;
        case E:
            space->gdesc[45] = '(';
            space->gdesc[59] = '(';
            return OK;
        case C:
            return OK;
        default:
            return ERROR;
    }
}

/**
* @brief Gets where is that link
* @author Óscar Gómez
* @date 20/12/2016
* @param Space* space (The space to modify)
* @param Id link_id (The link to search)
* @return DIRECTION (where the link is)
*/
DIRECTION space_get_link_direction(Space* spa, Id link_id){
    if(!spa || link_id == NO_ID) return C;

    if(spa->north == link_id){
        return N;
    }
    if(spa->south == link_id){
        return S;
    }
    if(spa->east == link_id){
        return E;
    }
    if(spa->west == link_id){
        return W;
    }
    return C;
}