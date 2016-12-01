/**
 * @brief Implementation of the graphic interface
 * @file graphics.c
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 01/12/2016
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "graphics.h"

struct _Graphics{
	WINDOW* playground; /*!< Declared window for the playing zone*/
	WINDOW* dialogue; /*!< Declared winloguedow for dialogue zone*/
	WINDOW* commands; /*!< Declared winloguedow for command zone*/
}/*!< Graphics structure*/

/*--------------------------------------------*/
/* Private functions                          */
/*--------------------------------------------*/	

/**
* @brief Init the module Graphics
* @author José Ignacio Gómez, Óscar Gómez
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

/*--------------------------------------------*/
/* Public functions                           */
/*--------------------------------------------*/

/**
* @brief Draw the borders of dialogue and commands zones
* @author José Ignacio Gómez, Óscar Gómez
* @date 01/12/2016
* @param Graphics* gra (The graphics pointer to draw)
* @return void
*/
void draw_borders(Graphics* gra) {
	int i;

	if(!gra){
		return;
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
}
