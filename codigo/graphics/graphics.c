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
#include <string.h>
#include <math.h>

struct _Graphics{
	WINDOW* playground; /*!< Declared window for the playing zone*/
	WINDOW* dialogue; /*!< Declared winloguedow for dialogue zone*/
	WINDOW* commands; /*!< Declared winloguedow for command zone*/
	char dia[WORD_SIZE+1]; /*!< String for previous dialogue*/
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
* @param DIRECTION dir (The direction of the space in the playground, will be omitted if the zone is different of PLAYGROUND)
* @param char* string (The string to be printed)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS print_in_zone(Graphics* gra, ZONE zone, DIRECTION dir , char* print){
	int i = 0, j = 0;
	FILE *f;

	if(!gra || !print){
		return ERROR;
	}

	switch(zone){
		case PLAYGROUND:
			switch(dir){
				case NW:
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
			for(i = 0; i < (WIN3_X - 2); i++){
				if(i == strlen(print)){
					return OK;
				}
				mvwprintw(gra->commands, 1, 1+i, "%c", print[i]);
			}
			return OK;
		case DIALOGUE:
			j = 1;
			for(i = 0; i < strlen(print); i++){
				if(i > ((WIN2_X-2)*(WIN2_Y-2))){
					return OK;
				}
				if(i%(WIN2_X-2) == 0){
					j++;
				}
				mvwprintw(gra->dialogue, j, (i%(WIN2_X -2))+1, "%c", print[i]);
			}
			
			j = 10;
			for(i = 0; i < strlen(gra->dia); i++){
				if(i > ((WIN2_X-2)*(WIN2_Y-2))){
					return OK;
				}
				if(i%(WIN2_X-2) == 0){
					j++;
				}
				mvwprintw(gra->dialogue, j, (i%(WIN2_X -2))+1, "%c", gra->dia[i]);
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

	draw_borders(gra);
	
	wrefresh(gra->playground);
	wrefresh(gra->dialogue);
	wrefresh(gra->commands);

	return OK;
}