#include "dialogue.h"

struct _Dialogue {
	Command* prev;
	Command* current;
	char print[MAX_DIALOGUE];

};

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

STATUS dialogue_standard(Dialogue* dialogue, char** objects){

	if(!dialogue || !objects){
		return ERROR;
	}

	strcat(dialogue->print, "Action: %s", dialogue->);

}

STATUS dialogue_generic(Dialogue* dialogue, STATUS check, char** objects, Space* space){
	T_command cmd;

	cmd = command_get_cmd(dialogue->current);
	switch cmd{
		case NO_CMD:
			return dialogue_error();
		case UNKNOWN:
			return dialogue_error();
		case QUIT:
			/***/
		case PICK:
			return dialogue_pick();
		case DROP:
			return dialogue_drop();
		case ROLL:
			return dialogue_roll();
		case INSPECT:
			return dialogue_inspect();
		case GO:
			return dialogue_go();
		case TURNON:
			return dialogue_turnon();
		case TURNOFF:
			return dialogue_turno():
		case OPEN:
		case SAVE:
		case LOAD:
	}

	if(!dialogue) return ERROR;

	if(check == OK){
		if(space_get_light(space) == TRUE){
			dialogue_standard(dialogue, objects);
			/*imprime mensaje correcto*/
		}
	}

	command_copy(prev, current);
}