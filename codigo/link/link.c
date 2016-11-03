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