/**
 * @brief It implements the dialogue of the game
 * @file dialogue.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 16/12/2016
 * @revision_history none
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "dialogue.h"
#include "graphic_engine.h"
#include "command.h"
#include <unistd.h>

struct _Dialogue {
	Command* prev; /*!< The previous command*/
	Command* current; /*!< The current command*/
	char print[MAX_DIALOGUE]; /*!< String for print*/

}; /*!< Dialogue structure*/

/*
* @brief Private functions
*/

/**
* @brief prints the quit dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_quit(Graphics* gra, Dialogue* dialogue){
	if(!gra || !dialogue) return ERROR;

	graphics_clear(gra);
	graphics_clear_zone(gra, DIALOGUE);

	print_in_zone(gra, DIALOGUE, 0, " ");
	graphics_clear_zone(gra, DIALOGUE);
	print_in_zone(gra, DIALOGUE, 0, "See you soon!");

	graphics_refresh(gra);

	sleep(3);

	return OK;
}

/**
* @brief prints the win dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_win(Graphics* gra, Dialogue* dialogue){
	if(!gra || !dialogue) return ERROR;

	graphics_clear(gra);
	graphics_clear_zone(gra, DIALOGUE);

	print_in_zone(gra, DIALOGUE, 0, "Congratulations! You've won the most difficult game ever!\n");

	graphics_refresh(gra);

	sleep(3);

	return OK;
}

/**
* @brief prints the help dialogue
* @author Óscar Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_help(Graphics* gra){
	return dialogue_print(gra, "The available commands are:\nquit, go, pick, drop, inspect,\nturnon, turnoff, open x with y,\nsave, load and help.");
}

/**
* @brief prints the error dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_error(Graphics* gra, Dialogue* dialogue, char** objects){
	char string[MAX_DIALOGUE]; /*!< string for print*/

	if(!gra || !dialogue) return ERROR;

	strcpy(string, "I didn't understand you.\n");

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;

	dialogue_help(gra);
	return dialogue_print(gra, string);
}

/**
* @brief prints the pick dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_pick(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* picked = NULL; /*!< string for the picked object*/

	if(!gra || !dialogue) return ERROR;

	picked = command_get_symbol(dialogue->current);
	if(!picked) return ERROR;

	if(check == OK){
		strcpy(string, "You have picked "); 
		strcat(string, picked);
		strcat(string, "\n");
	}
	else{
		strcpy(string, "Could not pick "); 
		strcat(string, picked);
		strcat(string, "\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_standard(gra, dialogue, objects, string);
}

/**
* @brief prints the drop dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_drop(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* dropped = NULL; /*!< string for the dropped object*/

	if(!gra || !dialogue) return ERROR;

	dropped = command_get_symbol(dialogue->current);
	if(!dropped) return ERROR;

	if(check == OK){
		strcpy(string, "You have dropped "); 
		strcat(string, dropped);
		strcat(string, "\n"); 
	}
	else{
		strcpy(string, "Could not drop "); 
		strcat(string, dropped);
		strcat(string, "\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_standard(gra, dialogue, objects, string);
}

/**
* @brief prints the go dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_go(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* direction = NULL; /*!< string for the direction*/

	if(!gra || !dialogue) return ERROR;

	direction = command_get_symbol(dialogue->current);
	if(!direction) return ERROR;

	if(check == OK){
		strcpy(string, "You have gone "); 
		strcat(string, direction);
		strcat(string, "\n"); 
	}
	else{
		strcpy(string, "You cannot go "); 
		strcat(string, direction);
		strcat(string, "\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	
	return dialogue_standard(gra, dialogue, objects, string);
}

/**
* @brief prints the turnon dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_turnon(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* obj = NULL; /*!< string for the object*/

	if(!gra || !dialogue) return ERROR;

	obj = command_get_symbol(dialogue->current);
	if(!obj) return ERROR;

	if(check == OK){
		strcpy(string, "You turned on the "); 
		strcat(string, obj);
		strcat(string, "\n"); 
	}
	else{
		strcpy(string, "Cannot turn on the "); 
		strcat(string, obj);
		strcat(string, "\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_standard(gra, dialogue, objects, string);
}

/**
* @brief prints the turnoff dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_turnoff(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* obj = NULL; /*!< string for print*/

	if(!gra || !dialogue) return ERROR;

	obj = command_get_symbol(dialogue->current);
	if(!obj) return ERROR;

	if(check == OK){
		strcpy(string, "You turned off the "); 
		strcat(string, obj);
		strcat(string, "\n"); 
	}
	else{
		strcpy(string, "Cannot turn off the "); 
		strcat(string, obj);
		strcat(string, "\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_standard(gra, dialogue, objects, string);
}

/**
* @brief prints the open dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_open(Graphics* gra, Dialogue* dialogue, char** objects, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* str = NULL; /*!< string for the open command*/

	if(!gra || !dialogue) return ERROR;

	str = command_get_symbol(dialogue->current);
	if(!str) return ERROR;

	if(check == OK){
		strcpy(string, "You opened the "); 
		strcat(string, str);
		strcat(string, "\n"); 
	}
	else{
		if(strcmp("syntax", objects[0]) == 0){
			strcpy(string, "Maybe trying OPEN link WITH object?");
			return dialogue_print(gra, string);
		}
		else{
			strcpy(string, "Cannot open the "); 
			strcat(string, str);
			strcat(string, "\n");
		}
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_standard(gra, dialogue, objects, string);
}


/**
* @brief prints the inspect_space dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_inspect_space(Graphics* gra, Dialogue* dialogue, char* inventory, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/

	
	if(!gra || !dialogue || !inventory) return ERROR;
	if(check == OK){
		strcpy(string, "Inspecting space: \n");
		strcat(string, inventory);
	}
	else{
		strcpy(string, "You should use a lantern\n");
	}
	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_print(gra, string);
}

/**
* @brief prints the inspect_inventory dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_inspect_inventory(Graphics* gra, Dialogue* dialogue, char** inventory, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	int i; /*!< counter*/

	if(!gra || !dialogue || !inventory) return ERROR;

	if(check == OK){
		strcpy(string, "Inspecting inventory: \n");
		i = 0;
		while(inventory[i][0] != '\0'){
			strcat(string, inventory[i]);
			strcat(string, "\n");
			i++;
		}
		if(inventory[0][0] == '\0'){
			strcpy(string, "Uups, it seems that you inventory is empty!\n");
		}
	}
	else{
		strcpy(string, "Could not inspect inventory\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_print(gra, string);
}

/**
* @brief prints the inspect_object dialogue
* @author José Ignacio Gómez
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char** objects
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_inspect_object(Graphics* gra, Dialogue* dialogue, char* inventory, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/
	char* obj = NULL; /*!< string for the inspected object*/

	if(!gra || !dialogue || !inventory) return ERROR;
	obj = command_get_symbol(dialogue->current);
	if(!obj) return ERROR;

	if(check == OK){
		strcpy(string, "Inspecting object ");
		strcat(string, obj);
		strcat(string, ": \n");
		strcat(string, inventory);
	}
	else{
		strcpy(string, "Could not inspect the object\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;
	return dialogue_print(gra, string);
}



/*
* @brief Public functions
*/

/**
* @brief creates a new dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @return Dialogue* (created dialogue)
*/
Dialogue* dialogue_create(Command* current){
	Dialogue* dialogue = NULL; /*!< Dialogue*/

	if(!current) return NULL;

	dialogue = (Dialogue*)malloc(sizeof(Dialogue));
	if(!dialogue) return NULL;

	dialogue->prev = command_create();
	if(!dialogue->prev){
		free(dialogue);
		return NULL;
	}

	dialogue->current = current;

	return dialogue;
}

/**
* @brief destroys a dialogue
* @author Jose Ignacio Gómez
* @date 16/12/16
* @param Dialogue*
* @return OK if it was destroyed
*/
void dialogue_destroy(Dialogue* dialogue){
	if(!dialogue) return;

	command_destroy(dialogue->prev);
	free(dialogue);

	return;
}

/**
* @brief Print the standard dialogue (objects in the space)
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Graphics*
* @param Dialogue*
* @param char** objects
* @param char string
* @return OK if it worked
*/
STATUS dialogue_standard(Graphics* gra, Dialogue* dialogue, char** objects, char* string){
	int i; /*!< Counter*/

	if(!dialogue || !objects || !gra || !string){
		return ERROR;
	}

	strcat(string, "\nITEMS IN THIS ROOM: \n");
	i = 0;
	while(objects[i] != NULL){
		strcat(string, objects[i]);
		strcat(string, "\n");
		i++;
	}

	

	return dialogue_print(gra, string);

}

/**
* @brief generic dialogue engine
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Dialogue*
* @param STATUS
* @param char** objects
* @param Graphics*
* @return OK if it worked
*/
STATUS dialogue_generic(Dialogue* dialogue, STATUS check, char** objects, Graphics* gra){
	T_Command cmd; /*!< Command for switch*/
	T_Command cmdp; /*!< Previous command */

	if(!dialogue || !gra) return ERROR;

	cmd = command_get_cmd(dialogue->current);
	cmdp = command_get_cmd(dialogue->prev);

	switch (cmd){
		case NO_CMD:
			if(cmd == cmdp){
				dialogue_print(gra, "You should try typing something...\nTry again or ask for'help'");
				sleep(3);
			}
			return dialogue_error(gra, dialogue, objects);
		case UNKNOWN:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried that before and it\ndoesn't even exist\nTry something different or ask for\n'help'");
				sleep(3);
			}
			return dialogue_error(gra, dialogue, objects);
		case QUIT:
			return dialogue_quit(gra, dialogue);
		case WIN:
			return dialogue_win(gra, dialogue);
		case PICK:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried to pick that before.\nDid you suceed?");
				sleep(3);
			}
			return dialogue_pick(gra, dialogue, objects, check);
		case DROP:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried to drop that before.\nDid you suceed?");
				sleep(3);
			}
			return dialogue_drop(gra, dialogue, objects, check);
		case GO:
			return dialogue_go(gra, dialogue, objects, check);
		case TURNON:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried to turn on that\nbefore.\nDid you suceed?");
				sleep(3);
			}
			return dialogue_turnon(gra, dialogue, objects, check);
		case TURNOFF:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried to turn off that\nbefore.\nDid you suceed?");
				sleep(3);
			}
			return dialogue_turnoff(gra, dialogue, objects, check);
		case OPEN:
			if(cmd == cmdp){
				dialogue_print(gra, "You have tried to open that before.\nDid you suceed?");
				sleep(3);
			}
			return dialogue_open(gra, dialogue, objects, check);
		case HELP:
			return dialogue_help(gra);
		/*case SAVE:
			return dialogue_save(gra, dialogue, objects, check);
		case LOAD:
			return dialogue_load(gra, dialogue, check);*/
		default:
			return ERROR;
	}

	return ERROR;
}

/**
* @brief dialogue engine for inspect
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Dialogue*
* @param STATUS
* @param char** inventory
* @param Graphics*
* @param DIALOGUE_INSPECT type
* @return OK if it worked
*/
STATUS dialogue_inspect(Dialogue* dialogue, STATUS check, char** inventory, Graphics* gra, DIALOGUE_INSPECT type){
	if(!dialogue || !gra || !inventory) return ERROR;

	switch (type){
		case SPACE:
			return dialogue_inspect_space(gra, dialogue, inventory[0], check); /* Inventory[0] will be the description of the space/object*/
		case INVENTORY:
			return dialogue_inspect_inventory(gra, dialogue, inventory, check);
		case OBJECT:
			return dialogue_inspect_object(gra, dialogue, inventory[0], check);
	}

	return ERROR;
}

/**
* @brief prints on screen the dialogue
* @author José Ignacio Gómez
* @date 16/12/2016
* @param Graphics*
* @param char string
* @return OK if it was printed successfuly
*/
STATUS dialogue_print(Graphics* gra, char *string){
	STATUS result; /*!< STATUS for the result*/

	if(!gra || !string) return ERROR;

	if(graphics_clear_zone(gra, DIALOGUE) == ERROR) return ERROR;

	result = print_in_zone(gra, DIALOGUE, 0, string);

	graphics_refresh(gra);

	return result;
}

/**
* @brief prints on screen the dialogue the default starting string
* @author Óscar Gómez
* @date 19/12/2016
* @param Graphics*
* @return OK if it was printed successfuly
*/
STATUS dialogue_start_game(Graphics* gra){
	STATUS result; /*!< STATUS for the result*/

	if(!gra) return ERROR;

	if(graphics_clear_zone(gra, DIALOGUE) == ERROR) return ERROR;

	result = print_in_zone(gra, DIALOGUE, 0, "Welcome to this game!\nTry to escape from this building, \nfind the keys and get out.\nIf you need some help try typing\n\"help\"");

	graphics_refresh(gra);

	return result;
}

/**
* @brief prints the load dialogue
* @author Óscar Pinto Santamaría
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char* string
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_load_show(Graphics* gra, Dialogue* dialogue, char* str, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/

	if(!gra || !dialogue) return ERROR;

	if(!str) return ERROR;

	if(check == OK){
		strcpy(string, "Saved games: \n");
		strcat(string, str);
	}else{
		strcpy(string, "Something went wrong\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;

	return dialogue_print(gra, string);
}

/**
* @brief prints the load dialogue
* @author Óscar Pinto Santamaría
* @date 20/12/16
* @param Graphics* gra (The graphics where it prints)
* @param Dialogue* dialogue
* @param char* string
* @param STATUS (checks if the callback was successful)
* @return STATUS (OK if everything went well, ERROR if it didn't)
*/
STATUS dialogue_load(Graphics* gra, Dialogue* dialogue, char* str, STATUS check){
	char string[MAX_DIALOGUE]; /*!< string for print*/

	if(!gra || !dialogue) return ERROR;

	if(!str) return ERROR;

	if(check == OK){
		strcpy(string, "Game loaded from file: ");
		strcat(string, str);
		strcat(string, "\n");
	}else{
		strcpy(string, "Something went wrong\n");
	}

	if(command_copy(dialogue->prev, dialogue->current) == ERROR) return ERROR;

	return dialogue_print(gra, string);
}
