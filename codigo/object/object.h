/* ===================================================================
File: object.h

Version: 1.0

Date: 30/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines the functionality of the objects

Revision history: none

=================================================================== */

#ifndef OBJECT_H
#define OBJECT_H

#define CHAR_ERROR '!' /*We decided to use ! as an error for the symbol*/

#include "types.h"

typedef struct _Object Object;

/* --------------------------------------------------------------------
Function: object_create()
 
Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It creates an object, setting all the fields to error

Input: Id id(The id of the object to create)

Output: Object* (a pointer to the object)

------------------------------------------------------------------- */
Object* object_create(Id id);

/* --------------------------------------------------------------------
Function: object_destroy()
 
Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It destroys an object, freeing all the memory

Input: Object* object(a pointer to the object)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_destroy(Object* object);

/* --------------------------------------------------------------------
Function: object_set_name()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the name of the given object

Input:Object* object(the object to change)
	  char* name(the name of the object)

Output: STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_name(Object* object, char* name);

/* --------------------------------------------------------------------
Function:object_set_symbol()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the symbol of the given object

Input:Object* object(the object to change)
	  char symbol(the symbol of the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_symbol(Object* object, char symbol);

/* --------------------------------------------------------------------
Function:object_set_location()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It sets the symbol of the given object

Input:Object* object(the object to change)
	  char symbol(the symbol of the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_set_location(Object* object, Id id);

/* --------------------------------------------------------------------
Function:object_get_symbol()

Date:30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the symbol of the given object

Input:Object* object(the object)

Output:char (the symbol of the object)

------------------------------------------------------------------- */
char object_get_symbol(Object* object);

/* --------------------------------------------------------------------
Function: object_get_name()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the name of the given object

Input:Object* object(the object)

Output:char* (the symbol of the object)

------------------------------------------------------------------- */
char* object_get_name(Object* object);

/* --------------------------------------------------------------------
Function:object_get_id()

Date: 30/19/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the id of the object

Input: Object* object(the object)

Output: Id (the Id of the object)

------------------------------------------------------------------- */
Id object_get_id(Object* object);

/* --------------------------------------------------------------------
Function:object_get_location()

Date: 30/19/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It gets the location of the object

Input: Object* object(the object)

Output: Id (the Id of the location)

------------------------------------------------------------------- */
Id object_get_location(Object* object);


/* --------------------------------------------------------------------
Function: object_print()

Date: 30/09/2016

Author:Óscar Gómez, Jose Ignacio Gómez.

Description: It prints the atributes of the given object

Input: Object* object (the object)

Output:STATUS (OK if everything went well, ERROR if didn't)

------------------------------------------------------------------- */
STATUS object_print(Object* object);


#endif
