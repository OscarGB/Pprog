/**
 * @brief Definition of the graphic interface
 * @file graphics.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 01/12/2016
 */

#define WIN1_X 42 /*!< X size of window 1*/
#define WIN1_Y 21 /*!< Y size of window 1*/
#define WIN2_X 38 /*!< X size of window 2*/
#define WIN2_Y 21 /*!< Y size of window 2*/
#define WIN3_X 80 /*!< X size of window 3*/
#define WIN3_Y 3  /*!< Y size of window 3*/

typedef enum{
	PLAYGROUND = 0, /*!< Playground zone*/
	COMMANDS, /*!< Command zone*/
	DIALOGUE /*!< Dialogue zone*/
}ZONE; /*!< Enumeration for the screen zones*/

typedef struct _Graphics Graphics; /*!< Definition of the structure "Graphics"*/

/**
* @brief Draw the borders of dialogue and commands zones
* @author Óscar Gómez
* @date 01/12/2016
* @param Graphics* gra (The graphics pointer to draw)
* @return void
*/
void draw_borders(Graphics *gra);

Graphics* graphics_create();

void graphics_destroy(Graphics* gra);

void clear_graphics(Graphics* gra);

void print_in_window(Graphics* gra, ZONE zone , char* print);

void refresh_graphics(Graphics* gra);