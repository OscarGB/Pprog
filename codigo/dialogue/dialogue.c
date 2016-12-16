#include "dialogue.h"

struct _Dialogue {
	Command* prev;
	Command* current;
	char print[MAX_DIALOGUE];

};

/*PRIVATE FUNCTIONS*/

STATUS dialogue_error(Graphics* gra, Dialogue* dialogue, char** objects){
	char string[MAX_DIALOGUE];

	if(!gra || !dialogue) return ERROR;

	string = "I didn't understand you.\n";

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_pick(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE];
	char* picked = NULL;

	if(!gra || !dialogue) return ERROR;

	picked = command_get_symbol(dialogue->current);
	if(!picked) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You have picked %s\n", picked); 
	}
	else{
		strcpy(string, "Could not pick %s\n", picked);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_drop(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE];
	char* dropped = NULL;

	if(!gra || !dialogue) return ERROR;

	dropped = command_get_symbol(dialogue->current);
	if(!dropped) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You have dropped %s\n", dropped); 
	}
	else{
		strcpy(string, "Could not drop %s\n", dropped);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_go(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE];
	char* direction = NULL;

	if(!gra || !dialogue) return ERROR;

	direction = command_get_symbol(dialogue->current);
	if(!direction) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You have gone %s\n", direction); 
	}
	else{
		strcpy(string, "You cannot go %s\n", direction);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_turnon(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE];
	char* obj = NULL;

	if(!gra || !dialogue) return ERROR;

	obj = command_get_symbol(dialogue->current);
	if(!obj) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You turned the %s on\n", obj); 
	}
	else{
		strcpy(string, "You cannot turn the %s on\n", obj);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_turnoff(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE];
	char* obj = NULL;

	if(!gra || !dialogue) return ERROR;

	obj = command_get_symbol(dialogue->current);
	if(!obj) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You turned the %s off\n", obj); 
	}
	else{
		strcpy(string, "You cannot turn the %s off\n", obj);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

STATUS dialogue_open(){
	char string[MAX_DIALOGUE];
	char* str = NULL;

	if(!gra || !dialogue) return ERROR;

	str = command_get_symbol(dialogue->current);
	if(!str) return ERROR;

	if(check == OK){
		string = "";
		strcpy(string, "You opened %s\n", str); 
	}
	else{
		strcpy(string, "You cannot open %s\n", str);
	}

	return dialogue_standard(gra, dialogue, objects, string);
}

/*STATUS dialogue_save(){
	
}

STATUS dialogue_load(){
	
}*/

STATUS dialogue_inspect_space(Graphics* gra, Dialogue* dialogue, char* inventory, STATUS check){
	char string[MAX_DIALOGUE];

	string = "";

	if(check == OK){
		strcpy(string, "Inspecting space: \n");
		
	}
}

/*PUBLIC FUNCTIONS*/

Dialogue* dialogue_create(Command* current){
	Dialogue* dialogue = NULL;

	if(!current) return NULL;

	dialogue = (Dialogue*)malloc(sizeof(Dialogue));
	if(!dialogue) return NULL;

	dialogue->prev = command_create();
	if(!dialogue->prev){
		free(dialogue);
		return NULL;
	}

	dialogue->current = current;
}

STATUS dialogue_standard(Graphics* gra, Dialogue* dialogue, char** objects, char string[MAX_DIALOGUE]){
	int i;

	if(!dialogue || !objects || !gra){
		return ERROR;
	}

	strcat(string, "ITEMS IN THIS ROOM: \n");
	i = 0;
	while(objects[i] != NULL){
		strcat(string, object[i]);
		strcat(string, "\n");
		i++;
	}

	dialogue_print(gra, string);

	return OK;

}

STATUS dialogue_generic(Dialogue* dialogue, STATUS check, char** objects, Space* space, Graphics* gra){
	T_command cmd;

	if(!dialogue || !objects || !space) return ERROR;

	cmd = command_get_cmd(dialogue->current);
	switch cmd{
		case NO_CMD:
			return dialogue_error(Graphics* gra, Dialogue* dialogue, char** objects);
		case UNKNOWN:
			return dialogue_error(Graphics* gra, Dialogue* dialogue, char** objects);
		case QUIT:
			return dialogue_quit(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case PICK:
			return dialogue_pick(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case DROP:
			return dialogue_drop(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case GO:
			return dialogue_go(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case TURNON:
			return dialogue_turnon(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case TURNOFF:
			return dialogue_turnoff(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check):
		case OPEN:
			return dialogue_open(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case SAVE:
			return dialogue_save(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		case LOAD:
			return dialogue_load(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check);
		default:
			return ERROR;
	}

	return ERROR;
}

STATUS dialogue_inspect(Dialogue* dialogue, STATUS check, char** inventory, Graphics* gra, DIALOGUE_INSPECT type){
	if(!dialogue || !gra) return ERROR;

	switch type{
		case SPACE:
			return dialogue_inspect_space(gra, dialogue, inventory[0], check); /* Inventory[0] will be the description of the space/object*/
		case INVENTORY:
			return dialogue_inspect_inventory(gra, dialogue, inventory, check);
		case OBJECT:
			return dialogue_inspect_object(gra, dialogue, inventory[0], check);
	}
}
/*
* @brief prints on screen the dialogue
* @author José Ignacio Gómez
* @date 16/12/2016
* @param 
* @param 
* @return OK if it was printed successfuly
*/
STATUS dialogue_print(Graphics* gra, char string[MAX_DIALOGUE]){
	if(!gra) return NULL;

	return print_in_zone(gra, DIALOGUE, 0, string);
}