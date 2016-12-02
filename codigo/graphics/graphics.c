/**
 * @brief Implementation of the graphic interface
 * @file graphics.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 01/12/2016
 */

#include "graphics.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>

struct _Graphics{
	WINDOW* playground; /*!< Declared window for the playing zone*/
	WINDOW* dialogue; /*!< Declared winloguedow for dialogue zone*/
	WINDOW* commands; /*!< Declared winloguedow for command zone*/
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
	noecho();
	curs_set(FALSE);
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
* @param none
* @return Graphics* (The created grapghics)
*/
Graphics* graphics_create(){
	Graphics *gra = NULL;

	gra = (Graphics *) malloc (sizeof(Graphics));
	if(!gra){
		return NULL;
	}

	screen_init();

	gra->playground = newwin(WIN1_Y, WIN1_X, 0, 0);
	if (!gra->playground){
		free(gra);
		return NULL;
	}

	gra->dialogue = newwin(WIN2_Y, WIN2_X, 0, WIN1_X + 1);
	if (!gra->dialogue){
		delwin(gra->playground);
		free(gra);
		return NULL;
	}

	gra->commands = newwin(WIN3_Y, WIN3_X, WIN1_Y + 1, 0);
	if (!gra->commands){
		delwin(gra->playground);
		delwin(gra->dialogue);
		free(gra);
		return NULL;
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
	/*Delete the windows*/
	delwin(gra->playground);
	delwin(gra->commands);
	delwin(gra->dialogue);
	/*End graphics*/
	screen_destroy();

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

	for(i = PLAYGROUND; i <= DIALOGUE; i++){
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
			wclear(gra->playground);
			return OK;
		case COMMANDS:
			wclear(gra->commands);
			return OK;
		case DIALOGUE:
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
* @param DIRECTION dir (The direction of the space int he playground, will be omitted if the zone is different of PLAYGROUND)
* @param char* print (The string to be printed)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS print_in_zone(Graphics* gra, ZONE zone, DIRECTION dir , char* print){
	
	if(!gra || !print){
		return ERROR;
	}

	switch(zone){
		case PLAYGROUND:
			switch(dir){
				case NW:
					mvwprintw(gra->playground, 0, 0, "%s", print);
					return OK;
				case N:
					mvwprintw(gra->playground, 0, SPACE_SIZE_X, "%s", print);
					return OK;
				case NE:
					mvwprintw(gra->playground, 0, 2*SPACE_SIZE_X, "%s", print);
					return OK;
				case W:
					mvwprintw(gra->playground, SPACE_SIZE_Y, 0, "%s", print);
					return OK;
				case C:
					mvwprintw(gra->playground, SPACE_SIZE_Y, SPACE_SIZE_X, "%s", print);
					return OK;
				case E:
					mvwprintw(gra->playground, SPACE_SIZE_Y, 2*SPACE_SIZE_X, "%s", print);
					return OK;
				case SW:
					mvwprintw(gra->playground, 2*SPACE_SIZE_Y, 0, "%s", print);
					return OK;
				case S:
					mvwprintw(gra->playground, 2*SPACE_SIZE_Y, SPACE_SIZE_X, "%s", print);
					return OK;
				case SE:
					mvwprintw(gra->playground, 2*SPACE_SIZE_Y, 2*SPACE_SIZE_X, "%s", print);
					return OK;
				default:
					return ERROR;
			}
		case COMMANDS:
			mvwprintw(gra->commands, 1, 1, "%s", print);
			return OK;
		case DIALOGUE:
			mvwprintw(gra->dialogue, 1, 1, "%s", print);
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

	draw_borders(gra);
	
	wrefresh(gra->playground);
	wrefresh(gra->dialogue);
	wrefresh(gra->commands);

	return OK;
}