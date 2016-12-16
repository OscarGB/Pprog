#include "dialogue.h"

struct _Dialogue {
	Command* prev;
	Command* current;

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

