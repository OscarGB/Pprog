/**
 * @brief It implements the functionality of the objects
 * @file object.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 30/09/2016
 * @revision_history none
 */

#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

struct _Object{
	Id id; /*<!Id of the object*/
	char name[WORD_SIZE + 1]; /*<!Name of the object*/
	char symbol; /*<!symbol of the object*/
	Id location; /*<!Location in the game*/
	char desc[WORD_SIZE+1]; /*<!Written description of the object*/
};


/*
* @brief it creates an object, setting all the fields to error
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Id id(The id of the object to create)
* @return Object* (a pointer to the object)
*/

Object* object_create(Id id){
	Object *newObject = NULL; /*New object to create*/

	if (id  == NO_ID)
		return NULL;

	newObject = (Object *)malloc(sizeof(Object));

	if(!newObject){
		return NULL;
	}

	/*Default values*/
	newObject->id = id;
	newObject->name[0]='\0';
	newObject->symbol = CHAR_ERROR;
	newObject->desc[0] = '\0';

	return newObject;
}


/*
* @brief It destroys an object, freeing all the memory
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param object pointer
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_destroy(Object *object){
	if(!object){
		return ERROR;
	}

	free(object);
	object = NULL;

	return OK;
}


/*
* @brief It sets the name of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
	 char* name(the name of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_name(Object* object, char* name){
	if(!object || !name){
		return ERROR;
	}

	if(!strcpy(object->name, name)){
		return ERROR;
	}

	return OK;
}


/*
* @brief It sets the symbol of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
	 char symbol(the symbol of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_symbol(Object* object, char symbol){
	if(!object){
		return ERROR;
	}

	object->symbol = symbol;

	return OK;
}


/*
* @brief It sets the location of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object* object(the object to change)
	 Id id(the location of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_location(Object* object, Id id){
	if(!object){
		return ERROR;
	}

	object->location = id;

	return OK;
}


/*
* @brief It gets the symbol of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return char (the symbol of the object)
*/

char object_get_symbol(Object* object){
	if(!object){
		
		return CHAR_ERROR; 
	}
	return object->symbol;
}


/*
* @brief It gets the name of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return char* (the name of the object)
*/

char* object_get_name(Object* object){
	if(!object){
		return "\0";
	}

	return object->name;
}


/*
* @brief It gets the id of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return Id (the id of the object)
*/

Id object_get_id(Object* object){
	if(!object){
		return NO_ID;
	}
	return object->id;
}


/*
* @brief It gets the location of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return Id (the location of the object)
*/

Id object_get_location(Object* object){
	if(!object){
		return NO_ID;
	}
	return object->location;
}


/*
* @brief It prints the atributes of the given object
* @author Óscar Gómez, Jose Ignacio Gómez.
* @date 30/09/2016
* @param Object pointer
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_print(Object* object){
	if(!object){
		return ERROR;
	}

	fprintf(stdout, "--> Object (Id: %ld; Name: %s; Symbol: %c",object_get_id(object), object_get_name(object), object_get_symbol(object));

	return OK;
}
