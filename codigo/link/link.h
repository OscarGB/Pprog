/**
 * @brief Definition of the link module
 * @file link.h
 * @author Óscar Gómez
 * @version 1.0
 * @date 3/11/2016
 */

#ifndef LINK_H
#define LINK_H

typedef struct _Link Link; /*<!Definition of the Link structure*/

typedef enum enum_link{
	CLOSED = 0,
	OPEN
} State; /*<!Definition of the State enumeration (controling an open or closed link)*/

/**
* @brief Creates a Link, it reserves memory and set values to default
* @author Óscar Gómez
* @date 3/11/2016
* @param Id (The Id of the link)
* @return Link* (The created link)
*/
Link* link_create(Id id);

 #endif