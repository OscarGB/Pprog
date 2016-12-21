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
	char mdesc[WORD_SIZE+1]; /*!<Written description when the object is moved*/ 
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
	char desc[WORD_SIZE]=" ", mdesc[WORD_SIZE]=" ";
	if (id  == NO_ID)
		return NULL;

	newObject = (Object *)malloc(sizeof(Object));

	if(!newObject){
		return NULL;
	}

	/*Default values*/
	newObject->id = id;
	newObject->name[0]='\0';
	newObject->location = NO_ID;
	newObject->symbol = CHAR_ERROR;
	strcpy(newObject->desc, desc);
	strcpy(newObject->mdesc, mdesc);
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
* @brief It sets the mdesc of the given object
* @author Óscar Pinto
* @date 15/12/2016
* @param Object* object(the object to change)
	 char* name(the new mdesc of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_mdesc(Object* object, char* mdesc){
	if(!object || !mdesc){
		return ERROR;
	}


	if(!strcpy(object->mdesc, mdesc)){
		return ERROR;
	}

	return OK;
}


/*
* @brief It sets the desc of the given object
* @author Óscar Pinto
* @date 15/12/2016
* @param Object* object(the object to change)
	 char* desc(the desc of the object)
* @return STATUS (OK if everything went well, ERROR if didn't)
*/

STATUS object_set_desc(Object* object, char* desc){
	if(!object || !desc){
		return ERROR;
	}


	if(!strcpy(object->desc, desc)){
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

STATUS object_set_movable(Object* object, BOOL value){
	if(!object){
		return ERROR;
	}
	object->movable = value; 
	return OK;
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

STATUS object_set_moved(Object* object, BOOL value){
	if(!object){
		return ERROR;
	}
	object->moved = value; 
	return OK;
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

STATUS object_set_hidden(Object* object, BOOL value){
	if(!object){
		return ERROR;
	}
	object->hidden = value; 
	return OK;
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

STATUS object_set_light(Object* object, BOOL value){
	if(!object){
		return ERROR;
	}
	object->light = value; 
	return OK;
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

STATUS object_set_on_off(Object* object, BOOL value){
	if(!object){
		return ERROR;
	}
	object->on_off = value; 
	return OK;
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

STATUS object_set_open(Object* object, Id value){
	if(!object){
		return ERROR;
	}
	object->open= value; 
	return OK;
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

STATUS object_set_duration(Object* object, Id value){
	if(!object){
		return ERROR;
	}
	object->duration = value; 
	return OK;
}

/*
* @brief It gets the name of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return char* (name of the given object)
*/

char* object_get_name(Object* object){
	if(!object){
		return "\0";
	}
	return object->name;
}

/*
* @brief It gets the mdesc of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return char* (description for moved object)
*/

char* object_get_mdesc(Object* object){
	if(!object){
		return "\0";
	}
	return object->mdesc;
}

/*
* @brief It gets the desc of the given object
* @author Óscar Pinto.
* @date 02/12/2016
* @param Object pointer
* @return char* (description for object in original location)
*/

char* object_get_desc(Object* object){
	if(!object){
		return "\0";
	}
	return object->desc;
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

STATUS object_print(FILE *f, Object* object){

	char mvbl[100], mvd[100], light[100], O_F[100], hddn[100];

	if(!object){
		return ERROR;
	}

	strcpy(mvbl, GET_BOOL(object->movable));
	strcpy(mvd, GET_BOOL(object->movable));
	strcpy(light, GET_BOOL(object->movable));
	strcpy(O_F, GET_BOOL(object->movable));
	strcpy(hddn, GET_BOOL(object->movable));


	fprintf(f, "--> Object (Id: %ld; Name: %s; Symbol: %c; Location: %ld;\n"
		"Desc: %s\n"
		"Movable: %s; Moved: %s; Hidden: %s;\n"
		"Light: %s; On_Off: %s; Open: %ld; Duration: %d\n",
		object->id, object->name, object->symbol, object->location, object->desc,
		mvbl, mvd, hddn, light, O_F, object->open, object->duration);

	return OK;
}

/*
* @brief It turns on an object if it is possible
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return STATUS(Ok or error)
*/

STATUS object_turnon(Object* object){

	if(!object) return ERROR;
	
	if(object->light==FALSE || object->duration<=0) return ERROR; /*Object can't be turned on because it can't illuminate or hasn't got battery left*/
	if(object->on_off==TRUE) return ERROR; /*Object already on*/

	object->on_off=TRUE;

	return OK;
}

/*
* @brief It turns off an object if it is possible
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return STATUS(Ok or error)
*/

STATUS object_turnoff(Object* object){

	if(!object) return ERROR;
	
	if(object->on_off==FALSE) return ERROR; /*Object can't be turned off because it can't illuminate or is not on*/


	object->on_off=FALSE;

	return OK;
}

/*
* @brief Checks if input object can open input id
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer, Id id
* @return BOOL (can or cannot open)
*/

BOOL object_can_open(Object *object, Id id){
	if(!object || id==NO_ID) return FALSE;

	if(object_get_open(object)==id) return TRUE;
	return FALSE;
}

/*
* @brief Decreases duration of the battery if object can illuminate and it is on
* @author Óscar Pinto.
* @date 13/12/2016
* @param Object pointer
* @return int (current duration)
*/

int object_decrease_duration(Object *object){
	int dur=-1;
	if(!object) return -1;

	dur=object_get_duration(object);

	if(object_get_light(object)==TRUE){
		if (object_get_on_off(object)==TRUE){
			if(dur >= 0) dur--;
			object_set_duration(object, dur);
			return dur;
		}
	}
	
	return dur;
}

/*
* @brief Returns the desc field if object not moved, mdesc if moved
* @author Óscar Pinto.
* @date 15/12/2016
* @param Object pointer
* @return char* (the suitable description of the object)
*/

char* object_get_description(Object *object){
	if(!object) return NULL;

	if(object->moved == FALSE)
		return object_get_desc(object);
	return object_get_mdesc(object);
}


