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
	WINDOW* dialogue; /*!< Declared window for dialogue zone*/
	WINDOW* commands; /*!< Declared window for command zone*/
}/*!< Graphics structure*/

/**
* @brief Draw the borders of dialogue and commands zones
* @author José Ignacio Gómez, Óscar Gómez
* @date 
* @param 
* @return 
*/
void draw_borders(Graphics* gra) {
	int max_x, max_y, i;

	if(!ven){
		return;
	}

	getmaxyx(ven->win, max_y, max_x); 
	mvwprintw(ven->win, 0, 0, "+");
	mvwprintw(ven->win, max_y - 1, 0, "+");
	mvwprintw(ven->win, 0, max_x - 1, "+");
	mvwprintw(ven->win, max_y - 1, max_x - 1, "+"); 
	for (i = 1; i < (max_y - 1); i++) {
		mvwprintw(ven->win, i, 0, "|");
		mvwprintw(ven->win, i, max_x - 1, "|");
	}
	for (i = 1; i < (max_x - 1); i++) {
		mvwprintw(ven->win, 0, i, "-");
		mvwprintw(ven->win, max_y - 1, i, "-");
	}
}

void screen_init(){
	initscr();
	noecho();
	curs_set(FALSE);
	return;
}