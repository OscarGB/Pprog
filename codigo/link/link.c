/**
 * @brief ImplementaTion of the link module
 * @file link.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 3/11/2016
 */

#include "link.h"
#include "space.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Link{
	Id id; /*!<The id of the Link*/
	char name[WORD_SIZE + 1]; /*!<The name of the link*/
	Id conection1; /*!<One of the conections of the link*/
	Id conection2; /*!<The other conection of the link*/
	State state; /*!<The state (open or closed)*/
};/*!<Link structure*/

/**
* @brief Creates a Link, it reserves memory and set values to default
* @author Óscar Gómez
* @date 3/11/2016
* @param Id (The Id of the link)
* @return Link* (The created link)
*/
Link* link_create(Id id){
	Link *newlink = NULL; /*!<The pointer to link that we are going to create*/

	if(id == NO_ID){
		return NULL;
	}

	newlink = (Link *)malloc(sizeof(Link));
	if(!newlink){
		return NULL;
	}

	newlink->id = id;
	newlink->name[0] = '\0';
	newlink->conection1 = NO_ID;
	newlink->conection2 = NO_ID;
	newlink->state = OPEN;

	return newlink;
}

/**
* @brief Destroys a Link, freeing all the memory
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to destroy)
* @return STATUS (OK if the Link was destroyed, ERROR if it wasn't)
*/
STATUS link_destroy(Link *deslink){
	if(!deslink){
		return ERROR;
	}

	free(deslink);
	deslink = NULL;

	return OK;
}

/**
* @brief Returns the id of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the Link)
*/
Id link_get_id(Link *link){
	if(!link){
		return NO_ID;
	}

	return link->id;
}

/**
* @brief Returns the name of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return cons char* (The name of the Link)
*/
const char* link_get_name(Link* link){
	if(!link){
		return NULL;
	}

	return link->name;
}

/**
* @brief Returns the state of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return State (The state of the Link)
*/
State link_get_state(Link* link){
	if(!link){
		return OPEN;
	}

	return link->state;
}

/**
* @brief Returns the Id of the first conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the first conection)
*/
Id link_get_conection1(Link* link){
	if(!link){
		return NO_ID;
	}

	return link->conection1;
}

/**
* @brief Returns the Id of the second conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to inspect)
* @return Id (The id of the second conection)
*/
Id link_get_conection2(Link* link){
	if(!link){
		return NO_ID;
	}

	return link->conection2;
}

/**
* @brief Sets the name of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param char* (The new name)
* @return STATUS (OK if the name have been changed, ERROR if haven't)
*/
STATUS link_set_name(Link* link, char* name){
	if(!link || !name){
		return ERROR;
	}

	if(!strcpy(link->name, name)){
		return ERROR;
	}

	return OK;

}

/**
* @brief Sets the first conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param Id (The Id of the new first conection)
* @return STATUS (OK if the conection have been changed, ERROR if haven't)
*/
STATUS link_set_conection1(Link* link, Id id){
	if(!link || id == NO_ID){
		return ERROR;
	}

	link->conection1 = id;

	return OK;
}

/**
* @brief Sets the second conection of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param Id (The Id of the new second conection)
* @return STATUS (OK if the conection have been changed, ERROR if haven't)
*/
STATUS link_set_conection2(Link* link, Id id){
	if(!link || id == NO_ID){
		return ERROR;
	}

	link->conection2 = id;

	return OK;
}

/**
* @brief Sets the State of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to change)
* @param State (The new State)
* @return STATUS (OK if the State have been changed, ERROR if haven't)
*/
STATUS link_set_state(Link* link, State state){
	if(!link){
		return ERROR;
	}

	link->state = state;

	return OK;
}

/**
* @brief It prints the content of a Link
* @author Óscar Gómez
* @date 3/11/2016
* @param Link* (The Link to print)
* @return STATUS (OK if the Link have been printed, ERROR if haven't)
*/
STATUS link_print(Link* link){
	Id idaux = NO_ID;

	if(!link){
		return ERROR;
	}

	fprintf(stdout, "-->Link (Id: %ld; Name: %s)\n", link->id, link->name);

	idaux = link_get_conection1(link);
	if(idaux != NO_ID){
		fprintf(stdout, "---> Conection 1: %ld.\n", idaux);
	}
	else{
		fprintf(stdout, "---> No conection 1.\n");
	}

	idaux = link_get_conection2(link);
	if(idaux != NO_ID){
		fprintf(stdout, "---> Conection 2: %ld.\n", idaux);
	}
	else{
		fprintf(stdout, "---> No conection 2.\n");
	}

	if(link_get_state(link) == OPEN){
		fprintf(stdout,"----> State: Open.\n");
	}
	else{
		fprintf(stdout,"----> State: Closed.\n");
	}

	return OK;
}
