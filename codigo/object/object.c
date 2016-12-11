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
	Id id; /*!<Id of the object*/
	char name[WORD_SIZE + 1]; /*!<Name of the object*/
	char symbol; /*!<symbol of the object*/
	Id location; /*!<Location in the game*/
	char desc[WORD_SIZE+1]; /*!<Written description of the object*/
	BOOL movable; /*!<Object can be moved or not*/
	BOOL moved; /*!<Object has been moved or not*/
	BOOL hidden; /*!<Object is hidden and not mentioned in description of space*/
	Id open; /*!<Object can open the given ID link*/
	BOOL light; /*!<Object can illuminate spaces or not*/
	BOOL on_off; /*!<Object which can light is on or off*/
	int duration; /*!< Amount of turns the object can still be on*/
};/*!<Object structure*/


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
	newObject->movable = FALSE;
	newObject->moved = FALSE;
	newObject->light = FALSE;
	newObject->hidden = FALSE;
	newObject->on_off = FALSE;
	newObject->open = NO_ID;
	newObject->duration = 0;

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
* @brief It gets the movable field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the movable field the object)
*/

BOOL object_get_movable(Object* object){
	if(!object){
		return FALSE;
	}
	return object->movable;
}

/*
* @brief It sets the movable field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @return BOOL (the moved field of the object)
*/

Object* object_set_movable(Object* object, BOOL value){
	if(!object){
		return FALSE;
	}
	object->movable = value; 
	return object;
}

/*
* @brief It gets the moved field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

BOOL object_get_moved(Object* object){
	if(!object){
		return FALSE;
	}
	return object->moved;
}

/*
* @brief It sets the moved field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_moved(Object* object, BOOL value){
	if(!object){
		return FALSE;
	}
	object->moved = value; 
	return object;
}

/*
* @brief It gets the hidden field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the hidden field of the object)
*/

BOOL object_get_hidden(Object* object){
	if(!object){
		return FALSE;
	}
	return object->hidden;
}

/*
* @brief It sets the hidden field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_hidden(Object* object, BOOL value){
	if(!object){
		return FALSE;
	}
	object->hidden = value; 
	return object;
}


/*
* @brief It gets the light field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the light field of the object)
*/

BOOL object_get_light(Object* object){
	if(!object){
		return FALSE;
	}
	return object->light;
}

/*
* @brief It sets the light field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_light(Object* object, BOOL value){
	if(!object){
		return FALSE;
	}
	object->light = value; 
	return object;
}

/*
* @brief It gets the on_off field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return BOOL (the on_off field of the object)
*/

BOOL object_get_on_off(Object* object){
	if(!object){
		return FALSE;
	}
	return object->on_off;
}

/*
* @brief It sets the on_off field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_on_off(Object* object, BOOL value){
	if(!object){
		return FALSE;
	}
	object->on_off = value; 
	return object;
}

/*
* @brief It gets the open field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return Id (the open field of the object)
*/

Id object_get_open(Object* object){
	if(!object){
		return NO_ID;
	}
	return object->open;
}

/*
* @brief It sets the open field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param id value
* @return BOOL (the moved field of the object)
*/

Object* object_set_open(Object* object, Id value){
	if(!object){
		return FALSE;
	}
	object->id = value; 
	return object;
}

/*
* @brief It gets the duration field of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return int (the duration field of the object)
*/

int object_get_duration(Object* object){
	if(!object){
		return -1;
	}
	return object->duration;
}

/*
* @brief It sets the duration field of the given object
* @author Óscar Pinto.
* @date 09/12/2016
* @param Object pointer
* @param BOOL value
* @return BOOL (the moved field of the object)
*/

Object* object_set_duration(Object* object, Id value){
	if(!object){
		return FALSE;
	}
	object->open = value; 
	return object;
}

/*
* @brief It gets the name of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return int (the duration field of the object)
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

	fprintf(stdout, "--> Object (Id: %ld; Name: %s; Symbol: %c; Location: %ld;\n"
		"Desc: %s"
		"Movable: %s; Moved: %s; Hidden: %s; Light: %s; On_Off: %s; Open: %ld; Duration: %d",
		object->id, object->name, object->symbol, object->location, object->desc, GET_BOOL(object->movable), 
		GET_BOOL(object->moved), GET_BOOL(object->hidden), GET_BOOL(object->light), GET_BOOL(object->on_off), 
		object->open, object->duration);

	return OK;
}
