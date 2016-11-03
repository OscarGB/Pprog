/**
 * @brief ImplementaTion of the link module
 * @file link.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 3/11/2016
 */

struct _Link{
	Id id; /*<!The id of the Link*/
	char name[WORD_SIZE + 1]; /*<!The name of the link*/
	Id conection1; /*<!One of the conections of the link*/
	Id conection2; /*<!The other conection of the link*/
	State state; /*<!The state (open or closed)*/
};/*<!Link structure*/

/**
* @brief Creates a Link, it reserves memory and set values to default
* @author Óscar Gómez
* @date 3/11/2016
* @param Id (The Id of the link)
* @return Link* (The created link)
*/
Link* link_create(Id id){
	Link *newlink = NULL; /*<!The pointer to link that we are going to create*/

	if(id == NO_ID){
		return NULL
	}

	newlink = (Link *)malloc(sizeof(Link));
	if(!newlink){
		return NULL;
	}

	newlink->id = id;
	newlink->name = "";
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
* @return STATUS (OK if the space was destroyed, ERROR if it wasn't)
*/
STATUS link_destroy(Link *deslink){
	if(!deslink){
		return ERROR;
	}

	free(deslink);
	deslink = NULL;

	return OK;
}

Id link_get_id(Link *link){
	if(!link){
		return NO_ID;
	}

	return link->id;
}

const char* link_get_name(Link* link){
	if(!link){
		return NULL;
	}

	return link->name;
}


State link_get_state(Link* link){
	if(!link){
		return OPEN;
	}

	return link->state;
}

Id link_get_conection1(Link* link){
	if(!link){
		return NO_ID;
	}

	return link->conection1;
}

Id link_get_conection2(Link* link){
	if(!link){
		return NO_ID;
	}

	return link->conection2;
}

STATUS link_set_name(Link* link, char* name){
	if(!link || !name){
		return ERROR;
	}

	if(!strcpy(link->name, name)){
		return ERROR;
	}

	return OK;

}

STATUS link_set_conection1(Link* link, Id id){
	if(!link || id == NO_ID){
		return ERROR;
	}

	link->conection1 = id;

	return OK;
}

STATUS link_set_conection2(Link* link, Id id){
	if(!link || id == NO_ID){
		return ERROR;
	}

	link->conection2 = id;

	return OK;
}

STATUS link_set_state(Link* link, State state){
	if(!link){
		return ERROR;
	}

	link->state = state;

	return OK;
}

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
}