/**
 * @brief Definition of the link module
 * @file link.h
 * @author Óscar Gómez
 * @version 1.0
 * @date 3/11/2016
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

#define MAX_LINKS 10000 /*!< Macro for the max amount of links*/

typedef struct _Link Link; /*!<Definition of the Link structure*/

typedef enum enum_link{
	CLOSEDL = 0,
	OPENL
} State; /*!<Definition of the State enumeration (controling an open or closed link)*/

/**
* @brief Creates a Link, it reserves memory and set values to default
* @author Óscar Gómez
* @date 3/11/2016
* @param Id (The Id of the link)
* @return Link* (The created link)
*/
Link* link_create(Id id);

/**
* @brief Destroys a Link, freeing all the memory
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to destroy)
* @return STATUS (OK if the space was destroyed, ERROR if it wasn't)
*/
STATUS link_destroy(Link *deslink);

/**
* @brief Returns the id of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the Link)
*/
Id link_get_id(Link *link);

/**
* @brief Returns the name of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return cons char* (The name of the Link)
*/
const char* link_get_name(Link* link);

/**
* @brief Returns the state of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return State (The state of the Link)
*/
State link_get_state(Link* link);

/**
* @brief Returns the Id of the first conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the first conection)
*/
Id link_get_conection1(Link* link);

/**
* @brief Returns the Id of the second conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the second conection)
*/
Id link_get_conection2(Link* link);

/**
* @brief Sets the name of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param char* (The new name)
* @return STATUS (OK if the name have been changed, ERROR if haven't)
*/
STATUS link_set_name(Link* link, char* name);

/**
* @brief Sets the first conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param Id (The Id of the new first conection)
* @return STATUS (OK if the conection have been changed, ERROR if haven't)
*/
STATUS link_set_conection1(Link* link, Id id);

/**
* @brief Sets the second conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param Id (The Id of the new second conection)
* @return STATUS (OK if the conection have been changed, ERROR if haven't)
*/
STATUS link_set_conection2(Link* link, Id id);

/**
* @brief Sets the State of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param State (The new State)
* @return STATUS (OK if the State have been changed, ERROR if haven't)
*/
STATUS link_set_state(Link* link, State state);

/**
* @brief It prints the content of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to print)
* @return STATUS (OK if the Link have been printed, ERROR if haven't)
*/
STATUS link_print(Link* link);

/**
* @brief Opens a link
* @author José Ignacio Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @return STATUS (OK if the State have been changed, ERROR if haven't)
*/
STATUS link_open(Link* link);

/**
* @brief Closes a link
* @author José Ignacio Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @return STATUS (OK if the State have been changed, ERROR if haven't)
*/
STATUS link_close(Link* link);

#endif