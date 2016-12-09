/**
 * @brief It defines the functionality of the objects
 * @file object.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 30/09/2016
 * @revision_history none
 */

#ifndef OBJECT_H
#define OBJECT_H
#define GET_BOOL(x) ("(x==0)? TRUE: FALSE)")


#define CHAR_ERROR '!' /*!< Macro for char_error (!)*/

#include "types.h"

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
	 char* name(the name of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_name(Object* object, char* name);


/*
* @brief It sets the symbol of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
	 char symbol(the symbol of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_symbol(Object* object, char symbol);


/*
* @brief It sets the location of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
	 Id id(the location of the object)
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
* @param Object pointer
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_print(Object* object);

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
* @param Object pointer
* @return BOOL (the moved field of the object)
*/

Object* object_set_movable(Object* object, BOOL value);

/*
* @brief It gets the moved field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

BOOL object_get_moved(Object* object);

/*
* @brief It sets the moved field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_moved(Object* object, BOOL value);

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

Object* object_set_hidden(Object* object, BOOL value);


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

Object* object_set_light(Object* object, BOOL value);
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

Object* object_set_on_off(Object* object, BOOL value);

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

Object* object_set_open(Object* object, id value);

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

Object* object_set_duration(Object* object, id value);


#endif
