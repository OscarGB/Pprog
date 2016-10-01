/* ===================================================================
File: object.c

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It implements the functionality of the objects

Revision history: none

=================================================================== */

#include "object.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

struct _Object{
	Id id;
	char name[WORD_SIZE + 1];
	char symbol;
	Id location;
}

/* --------------------------------------------------------------------
Function: object_create()
 
Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates an object, setting all the fields to error

Input: Id id(The id of the object to create)

Output: Object* (a pointer to the object)

------------------------------------------------------------------- */
Object* object_create(Id id){
	Object *newObject = NULL;

	if (id  == NO_ID)
		return NULL;

	newObject = (Object *)malloc(sizeof(Object));

	if(!newObject){
		return NULL;
	}

	newObject->id = id;
	newObject->name[0]='\0';
	newObject->symbol = CHAR_ERROR;

	return newObject;
}

/* --------------------------------------------------------------------
Function: object_destroy()
 
Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroys an object, freeing all the memory

Input: Object* object(a pointer to the object)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_destroy(Object *object){
	if(!object){
		return ERROR;
	}

	free(object);
	object = NULL;

	return OK;
}

/* --------------------------------------------------------------------
Function: object_set_name()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the name of the given object

Input:Object* object(the object to change)
	  char* name(the name of the object)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_name(Object* object, char* name){
	if(!object || !name){
		return ERROR;
	}

	if(!strcpy(object->name, name)){
		return ERROR;
	}

	return OK;
}

/* --------------------------------------------------------------------
Function:object_set_symbol()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the symbol of the given object

Input:Object* object(the object to change)
	  char symbol(the symbol of the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_symbol(Object* object, char symbol){
	if(!object){
		return ERROR;
	}

	object->symbol = symbol;

	return OK;
}

/* --------------------------------------------------------------------
Function:object_set_location()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the symbol of the given object

Input:Object* object(the object to change)
	  char symbol(the symbol of the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_location(Object* object, Id id){
	if(!object){
		return ERROR;
	}

	object->location = id;

	return OK;
}

/* --------------------------------------------------------------------
Function:object_get_symbol()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the symbol of the given object

Input:Object* object(the object)

Output:char (the symbol of the object)

------------------------------------------------------------------- */
char object_get_symbol(Object* object){
	if(!object){
		return CHAR_ERROR; 
	}
	return object->symbol;
}

/* --------------------------------------------------------------------
Function: object_get_name()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the name of the given object

Input:Object* object(the object)

Output:char* (the symbol of the object)

------------------------------------------------------------------- */
char* object_get_name(Object* object){
	if(!object){
		return "\0"
	}

	return object->name;
}

/* --------------------------------------------------------------------
Function:object_get_id()

Date: 30/19/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the id of the object

Input: Object* object(the object)

Output: Id (the Id of the object)

------------------------------------------------------------------- */
Id object_get_id(Object* object){
	if(!object){
		return NO_ID;
	}
	return object->id;
}

/* --------------------------------------------------------------------
Function:object_get_location()

Date: 30/19/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the location of the object

Input: Object* object(the object)

Output: Id (the Id of the location)

------------------------------------------------------------------- */
Id object_get_location(Object* object){
	if(!object){
		return NO_ID;
	}
	return object->location;
}

/* --------------------------------------------------------------------
Function: object_print()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It prints the atributes of the given object

Input: Object* object (the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_print(Object* object){
	if(!object){
		return ERROR;
	}

	fprintf(stdout, "--> Object (Id: %ld; Name: %s; Symbol: %c",object_get_id(object), object_get_name(object), object_get_symbol(object));

	return OK;
}
