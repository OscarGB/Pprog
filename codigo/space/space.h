/**
 * @brief It defines the game spaces
 * @file space.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 2.0
 * @date 4/11/2016
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#include "types.h"

typedef struct _Space Space; /*!<Definition of the Space structure*/

#define MAX_SPACES 10000 /*!<Max number of spaces*/
#define FIRST_SPACE 1 /*!<Definition of the first space*/
#define MAX_GDESC  100 /*!<Max number of characters in gdesc*/
#define MAX_adesc 100 /*!<Max number of characters in advanced gdesc*/

/**
* @brief Creates a new space for the game
* @author Óscar Gómez
* @date 4/11/2016
* @param Id id(The id for the new space)
* @return Space* (The created space)
*/
Space* space_create(Id id);

/**
* @brief destroys a non-empty space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space that is going to be destroyed) 
* @return STATUS (OK if the space was destroyed, ERROR if it wasn't)
*/
STATUS space_destroy(Space* space);

/**
* @brief Sets the name of a Space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space that has to be changed)
* @param char* name (The new name for the space)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_name(Space* space, char* name);

/**
* @brief Sets the Id of the nort Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the north)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_north(Space* space, Id id);

/**
* @brief Sets the Id of the south Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the south)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_south(Space* space, Id id);

/**
* @brief Sets the Id of the east Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the east)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_east(Space* space, Id id);

/**
* @brief Sets the Id of the west Link
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located at the west)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_west(Space* space, Id id);

/**
* @brief Sets the Id of the upper Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located up)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_up(Space* space, Id id);

/**
* @brief Sets the Id of the lower Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @param Id id (The id of the Link located down)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_set_down(Space* space, Id id);
/**
* @brief Adds an object to the space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @param Id id (the id of the object)
* @return STATUS (OK if everything went well, ERROR if it wasn't)
*/
STATUS space_add_object(Space* space, Id id);

/**
* @brief it returns the name of a given space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @return char* (the name of the space)
*/
const char * space_get_name(Space* space);

/**
* @brief It returns the Id of a given space
* @author José Ignacio Gómez, Óscar Gómez
* @date 4/11/2016
* @param Space* space (the space we want to know about)
* @return Id (the Id of the space)
*/
Id space_get_id(Space* space);

/**
* @brief Gets the id of the Link in the north
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the north)
*/
Id space_get_north(Space* space);

/**
* @brief Gets the id of the Link in the south
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the south)
*/
Id space_get_south(Space* space);

/**
* @brief Gets the id of the Link in the east
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the east)
*/
Id space_get_east(Space* space);

/**
* @brief Gets the id of the Link in the west
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* Space (The space to evaluate)
* @return Id id (The id of the link located at the west)
*/
Id space_get_west(Space* space);

/**
* @brief Gets the Id of the upper Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @return Id id (The id of the link located up)
*/
Id space_get_up(Space* space);

/**
* @brief Gets the Id of the lower Link
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* Space (The space which need to be set)
* @return Id id (The id of the link located down)
*/
Id space_get_down(Space* space);
/**
* @brief It returns the Set of objects inside the Space
* @author Óscar Gómez
* @date 4/11/2106
* @param Space* space (the space we want to know about)
* @return Set* (The set inside the Space)
*/
Set* space_get_objects(Space* space);

/**
* @brief Checks if the object is in the given space
* @author Óscar Gómez
* @date 4/11/2016
* @param Space* (The space to check)
* @param Id (The id to find)
* @return BOOL (TRUE if its in the space, FALSE if error or isn't in the space)
*/
BOOL space_is_object_in(Space* space, Id id);

/**
* @brief Prints the given space in the standard output
* @author Óscar Gómez
* @date 4/11/2016
* @param Space *space (The space to be printed)
* @return STATUS (OK if everything went well, ERROR if something went wrong)
*/
STATUS space_print(Space* space);

/**
* @brief Sets the gdesc of a Space
* @author José Ignacio Gómez
* @date 4/11/2016
* @param Space* space (The space to modify)
* @param char* gdesc (The new gdesc)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_gdesc(Space* space, char* gdesc);

/**
* @brief Returns the gdesc of a space
* @author José Ignacio Gómez
* @date 4/11/2016
* @param Space* space (The space to inspect)
* @return char* (The gdesc inside the Space)
*/
char* space_get_gdesc(Space* space);

/**
* @brief Sets the advanced description of a Space
* @author Andrea Ruiz
* @date 2/12/2016
* @param Space* space (The space to modify)
* @param char* adesc (The new adesc)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_adesc(Space* space, char* adesc);

/**
* @brief Returns the advanced description of a space
* @author Andrea Ruiz
* @date 5/12/2016
* @param Space* space (The space to inspect)
* @return char* (The adesc inside the Space)
*/
char* space_get_adesc(Space* space);
/**
* @brief Sets the light of the input space
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* space (The space to modify)
* @param BOOL (TRUE to illuminate)
* @return STATUS (OK if it was successfuly set)
*/
STATUS space_set_light(Space* space, BOOL light);

/**
* @brief Gets the light status of the input space
* @author Andrea Ruiz
* @date 1/12/2016
* @param Space* space
* @return BOOL (TRUE if illuminated, FALSE if not)
*/
BOOL space_get_light(Space* space);

#endif
