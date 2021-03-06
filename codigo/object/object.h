/**
 * @brief It defines the functionality of the objects
 * @file object.h
 * @author Óscar Gómez, José Ignacio Gómez, Óscar Pinto Santmaría
 * @version 2.0
 * @date 30/09/2016
 * @revision_history 16/12/2016 (by Óscar Pinto Santamaría)
 */

#ifndef OBJECT_H
#define OBJECT_H
#define True "TRUE"
#define False "FALSE"
#define GET_BOOL(x) ((x==0)? (False): (True))


#define CHAR_ERROR '!' /*!< Macro for char_error (!)*/

#include "types.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _Object Object; /*<! Definition of Object structure */


/*
* @brief it creates an object, setting all the fields to error
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Id id(The id of the object to create)
* @return Object* (a pointer to the object)
*/

Object* object_create(Id id);


/*
* @brief It destroys an object, freeing all the memory
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param object pointer
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_destroy(Object* object);


/*
* @brief It sets the name of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
* @param char* name(the name of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_name(Object* object, char* name);


/*
* @brief It sets the symbol of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
* @param char symbol(the symbol of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_symbol(Object* object, char symbol);


/*
* @brief It sets the location of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
* @param Id id(the location of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/
STATUS object_set_location(Object* object, Id id);


/*
* @brief It gets the symbol of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return char (the symbol of the object)
*/

char object_get_symbol(Object* object);


/*
* @brief It gets the name of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return char* (the name of the object)
*/

char* object_get_name(Object* object);


/*
* @brief It gets the id of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return Id (the id of the object)
*/

Id object_get_id(Object* object);


/*
* @brief It gets the location of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return Id (the location of the object)
*/

Id object_get_location(Object* object);


/*
* @brief It prints the atributes of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param FILE *f
* @param Object pointer
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_print(FILE *f, Object* object);

/*
* @brief It gets the movable field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the movable field the object)
*/

BOOL object_get_movable(Object* object);

/*
* @brief It sets the movable field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object* object
* @param Object pointer
* @return BOOL (the moved field of the object)
*/

STATUS object_set_movable(Object* object, BOOL value);

/*
* @brief It tells if an object has been moved
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (TRUE if it has been moved)
*/
BOOL object_get_moved(Object* object);

/*
* @brief It sets the original_location field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param Id value
* @return STATUS Ok if everything worked
*/

STATUS object_set_original_location(Object* object, Id value);

/*
* @brief It gets the original_location field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @param BOOL value
* @return Id (the original location)
*/

Id object_get_original_location(Object* object);

/*
* @brief It gets the hidden field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the hidden field of the object)
*/

BOOL object_get_hidden(Object* object);

/*
* @brief It sets the hidden field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

STATUS object_set_hidden(Object* object, BOOL value);


/*
* @brief It gets the light field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the light field of the object)
*/

BOOL object_get_light(Object* object);

/*
* @brief It sets the light field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

STATUS object_set_light(Object* object, BOOL value);
/*
* @brief It gets the on_off field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the on_off field of the object)
*/

BOOL object_get_on_off(Object* object);

/*
* @brief It sets the on_off field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

STATUS object_set_on_off(Object* object, BOOL value);

/*
* @brief It gets the open field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return Id (the open field of the object)
*/

Id object_get_open(Object* object);
/*
* @brief It sets the open field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param id value
* @return BOOL (the moved field of the object)
*/

STATUS object_set_open(Object* object, Id value);

/*
* @brief It gets the duration field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return int (the duration field of the object)
*/

int object_get_duration(Object* object);
/*
* @brief It sets the duration field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

STATUS object_set_duration(Object* object, Id value);

/*
* @brief It turns on an object if it is possible
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return STATUS(Ok or error)
*/

STATUS object_turnon(Object* object);

/*
* @brief It turns off an object if it is possible
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return STATUS(Ok or error)
*/

STATUS object_turnoff(Object* object);

/*
* @brief Checks if input object can open input id
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer, Id id
* @return BOOL (can or cannot open)
*/

BOOL object_can_open(Object *object, Id id);

/*
* @brief Decreases duration of the battery if object can illuminate and it is on
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return int (current duration)
*/

int object_decrease_duration(Object *object);

/*
* @brief It gets the mdesc of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return char* (description for moved object)
*/

char* object_get_mdesc(Object* object);

/*
* @brief It gets the desc of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return char* (description for object in original location)
*/

char* object_get_desc(Object* object);


/*
* @brief It sets the mdesc of the given object
* @author Óscar Pinto
* @date 15/12/2016
* @param Object* object(the object to change)
* @param char* name(the new mdesc of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_mdesc(Object* object, char* mdesc);

/*
* @brief It sets the desc of the given object
* @author Óscar Pinto
* @date 15/12/2016
* @param Object* object(the object to change)
* @param char* desc(the desc of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_desc(Object* object, char* desc);

/*
* @brief Returns the desc field if object not moved, mdesc if moved
* @author Óscar Pinto.
* @date 15/12/2016
* @param Object pointer
* @return char* (the suitable description of the object)
*/

char* object_get_description(Object *object);

#endif
