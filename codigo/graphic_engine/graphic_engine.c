/**
 * @brief Implementation of the graphic interface
 * @file graphic_engine.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 01/12/2016
 */

#include "graphic_engine.h"
#include "command.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct _Graphics{
	WINDOW* playground; /*!< Declared window for the playing zone*/
	WINDOW* dialogue; /*!< Declared winloguedow for dialogue zone*/
	WINDOW* commands; /*!< Declared winloguedow for command zone*/
	char dia[WORD_SIZE+1]; /*!< String for previous dialogue*/
	int nv; /*Non verbose flag*/
};/*!< Graphics structure*/ 

/*--------------------------------------------*/
/* Private functions                          */
/*--------------------------------------------*/	

/**
* @brief Init the module Graphics
* @author Óscar Gómez
* @date 01/12/2016
* @param none
* @return void
*/
void screen_init(){
	initscr();
	echo();
	curs_set(TRUE);
	return;
}

/**
* @brief Ends the module Graphics
* @author Óscar Gómez
* @date 01/12/2016
* @param none
* @return void
*/
void screen_destroy(){
	endwin();
	return;
}


/*--------------------------------------------*/
/* Public functions                           */
/*--------------------------------------------*/

/**
* @brief Draw the borders of dialogue and commands zones
* @author Óscar Gómez
* @date 01/12/2016
* @param Graphics* gra (The graphics pointer to draw)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS draw_borders(Graphics* gra) {
	int i;

	if(!gra){
		return ERROR;
	}

	if(gra->nv == 1){
		return OK;
	}

	/*Borders of dialogue*/
	/*Corners*/
	mvwprintw(gra->dialogue, 0, 0, "+");
	mvwprintw(gra->dialogue, WIN2_Y - 1, 0, "+");
	mvwprintw(gra->dialogue, 0, WIN2_X - 1, "+");
	mvwprintw(gra->dialogue, WIN2_Y - 1, WIN2_X - 1, "+");
	/*Sides*/ 
	for (i = 1; i < (WIN2_Y - 1); i++) {
		mvwprintw(gra->dialogue, i, 0, "|");
		mvwprintw(gra->dialogue, i, WIN2_X - 1, "|");
	}
	for (i = 1; i < (WIN2_X - 1); i++) {
		mvwprintw(gra->dialogue, 0, i, "-");
		mvwprintw(gra->dialogue, WIN2_Y - 1, i, "-");
	}
	/*Borders of commands*/
	/*Corners*/
	mvwprintw(gra->commands, 0, 0, "+");
	mvwprintw(gra->commands, WIN3_Y - 1, 0, "+");
	mvwprintw(gra->commands, 0, WIN3_X - 1, "+");
	mvwprintw(gra->commands, WIN3_Y - 1, WIN3_X - 1, "+"); 
	/*Sides*/
	for (i = 1; i < (WIN3_Y - 1); i++) {
		mvwprintw(gra->commands, i, 0, "|");
		mvwprintw(gra->commands, i, WIN3_X - 1, "|");
	}
	for (i = 1; i < (WIN3_X - 1); i++) {
		mvwprintw(gra->commands, 0, i, "-");
		mvwprintw(gra->commands, WIN3_Y - 1, i, "-");
	}

	return OK;
}

/**
* @brief Creates a graphic structure
* @author José Ignacio Gómez
* @date 01/12/2016
* @param int nv (Declares if the nv mode is active) 
* @return Graphics* (The created grapghics)
*/
Graphics* graphics_create(int nv){
	Graphics *gra = NULL;

	gra = (Graphics *) malloc (sizeof(Graphics));
	if(!gra){
		return NULL;
	}
	gra->nv = nv;
	if(nv != 1){ 
		screen_init();
	
		gra->playground = newwin(WIN1_Y, WIN1_X, 0, 0);
		if (!gra->playground){
			free(gra);
			return NULL;
		}
	
		gra->dialogue = newwin(WIN2_Y, WIN2_X, 0, WIN1_X);
		if (!gra->dialogue){
			delwin(gra->playground);
			free(gra);
			return NULL;
		}
	
		gra->commands = newwin(WIN3_Y, WIN3_X, WIN1_Y, 0);
		if (!gra->commands){
			delwin(gra->playground);
			delwin(gra->dialogue);
			free(gra);
			return NULL;
		}
	
		gra->dia[0] = '\0';
	}
	return gra;
}

/**
* @brief Destroys a graphics structure
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to be destroy)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_destroy(Graphics* gra){
	
	if(!gra){
		return ERROR;
	}
	if(gra->nv != 1){
		/*Delete the windows*/
		delwin(gra->playground);
		delwin(gra->commands);
		delwin(gra->dialogue);
		/*End graphics*/
		screen_destroy();
	}
	free(gra);

	return OK;
}

/**
* @brief Clears a graphics structure
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to be cleared)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_clear(Graphics* gra){

	int i;

	if(!gra){
		return ERROR;
	}

	if(gra->nv == 1){
		return OK;
	}

	for(i = PLAYGROUND; i <= COMMANDS; i++){
		if(graphics_clear_zone(gra, i) == ERROR){
			return ERROR;
		}
	}


	return OK;
}

/**
* @brief Clears a zone of the graphics structure
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics)
* @param ZONE zone (The zone to be cleared)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_clear_zone(Graphics* gra, ZONE zone){

	if(!gra){
		return ERROR;
	}

	switch(zone){
		case PLAYGROUND:
			if(gra->nv == 1){
				return OK;
			}
			wclear(gra->playground);
			return OK;
		case COMMANDS:
			if(gra->nv == 1){
				return OK;
			}
			wclear(gra->commands);
			return OK;
		case DIALOGUE:
			if(gra->nv == 1){
				return OK;
			}
			wclear(gra->dialogue);
			return OK;
		default:
			return ERROR;
	}
}

/**
* @brief Prints a string in a determined zone
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The grahpcis)
* @param ZONE zone (The zone in which you are going to print)
* @param DIRECTION dir (The direction of the space in the playground, will be omitted if the zone is different of PLAYGROUND)
* @param char* string (The string to be printed)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS print_in_zone(Graphics* gra, ZONE zone, DIRECTION dir , char* print){
	int i = 0, j = 0, p = 0, flag = 0;

	if(!gra || !print){
		return ERROR;
	}

	switch(zone){
		case PLAYGROUND:
			switch(dir){
				case NW:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, j, i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case N:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, j, SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case NE:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, j, 2*SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case W:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, SPACE_SIZE_Y + j, i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case C:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, SPACE_SIZE_Y + j, SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case E:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, SPACE_SIZE_Y + j, 2*SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case SW:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, 2*SPACE_SIZE_Y + j, i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case S:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, 2*SPACE_SIZE_Y + j, SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				case SE:
					if(gra->nv == 1){
						return OK;
					}
					j = 0;
					for(i = 0; i < (SPACE_SIZE_X*SPACE_SIZE_Y); i++){
						if(i == strlen(print)){
							return OK;
						}
						if(i%SPACE_SIZE_X == 0 && i != 0){
							j++;
						}
						mvwprintw(gra->playground, 2*SPACE_SIZE_Y + j, 2*SPACE_SIZE_X + i%SPACE_SIZE_X, "%c", print[i]);
					}
					return OK;
				default:
					return ERROR;
			}
		case COMMANDS:
			if(gra->nv == 1){
				return OK;
			}
			for(i = 0; i < (WIN3_X - 2); i++){
				if(i == strlen(print)){
					return OK;
				}
				mvwprintw(gra->commands, 1, 1+i, "%c", print[i]);
			}
			return OK;
		case DIALOGUE:
			if(gra->nv == 1){
				return OK;
			}
			j = 1;
			p = 0;
			for(i = 0; i < strlen(print); i++){
				if(p > ((WIN2_X-2)*(WIN2_Y-2))){
					return OK;
				}
				if(p%(WIN2_X-2) == 0 && flag != 1){
					j++;
				}
				flag = 0;
				if(print[i] == '\n'){
					while(p%(WIN2_X-2) != 0){
						p++;
					}
					j++;
					flag = 1;
				} else{
					mvwprintw(gra->dialogue, j, (p%(WIN2_X -2)+1), "%c", print[i]);
					p++;
				}
			}
			
			j = 10;
			p = 0;
			for(i = 0; i < strlen(gra->dia); i++){
				if(p > ((WIN2_X-2)*(WIN2_Y-2))){
					return OK;
				}
				if(p%(WIN2_X-2) == 0 && flag != 1){
					j++;
				}
				flag = 0;
				if(gra->dia[i] == '\n'){
					while(p%(WIN2_X-2) != 0){
						p++;
					}
					j++;
					flag = 1;
				} else{
					mvwprintw(gra->dialogue, j, (p%(WIN2_X -2)+1), "%c", gra->dia[i]);
					p++;
				}
			}

			strcpy(gra->dia, print);
			return OK;
		default:
			return ERROR;
	}
}

/**
* @brief Refreshes the graphics
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to refresh)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_refresh(Graphics* gra){

	if(!gra){
		return ERROR;
	}

	if(gra->nv == 1){
		return OK;
	}

	draw_borders(gra);
	
	wrefresh(gra->playground);
	wrefresh(gra->dialogue);
	wrefresh(gra->commands);

	return OK;
}

/**
* @brief Scans the user input from screen
* @author Óscar Gómez
* @date 16/12/2016
* @param Graphics* gra (The graphics to scan)
* @param Command* command (The place where you save the command)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS scan_from_screen(Graphics* gra, Command* command){
	char input[CMD_LENGHT]; /* The input */

	if(!gra || !command){
		return ERROR;
	}

	if(gra->nv == 1){
		return OK;
	}

	mvwprintw(gra->commands, 1, 1, "prompt:> ");
	graphics_refresh(gra);

	if(mvwgetstr(gra->commands, 1, 10, input) < 0){
		return ERROR;	
	}

	return get_user_input(command, input);
}