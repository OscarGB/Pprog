/**
 * @brief Definition of the graphic interface
 * @file graphic_engine.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 01/12/2016
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "types.h"
#include "command.h"
/*PLAYGROUND*/
#define WIN1_X 42 /*!< X size of window 1*/
#define WIN1_Y 21 /*!< Y size of window 1*/
/*DIALOGUES*/
#define WIN2_X 38 /*!< X size of window 2*/
#define WIN2_Y 21 /*!< Y size of window 2*/
/*COMMANDS*/
#define WIN3_X 80 /*!< X size of window 3*/
#define WIN3_Y 3  /*!< Y size of window 3*/
/*SPACES*/
#define SPACE_SIZE_X 14 /*!< X size of each space*/
#define SPACE_SIZE_Y 7 /*!< Y size of each space*/

typedef enum{
	PLAYGROUND = 0, /*!< Playground zone*/
	COMMANDS, /*!< Command zone*/
	DIALOGUE /*!< Dialogue zone*/
}ZONE; /*!< Enumeration for the screen zones*/

typedef struct _Graphics Graphics; /*!< Definition of the structure "Graphics"*/

/**
* @brief Creates a graphics structure
* @author José Ignacio Gómez
* @date 01/12/2016
* @param none
* @return Graphics* (The created grapghics)
*/
Graphics* graphics_create();

/**
* @brief Destroys a graphics structure
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to be destroy)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_destroy(Graphics* gra);

/**
* @brief Draw the borders of dialogue and commands zones
* @author Óscar Gómez
* @date 01/12/2016
* @param Graphics* gra (The graphics pointer to draw)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS draw_borders(Graphics *gra);

/**
* @brief Clears a graphics structure without clearing the dialogue
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to be cleared)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_clear(Graphics* gra);

/**
* @brief Clears a zone of the graphics structure
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics)
* @param ZONE zone (The zone to be cleared)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_clear_zone(Graphics* gra, ZONE zone);

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
STATUS print_in_zone(Graphics* gra, ZONE zone, DIRECTION dir, char* string);

/**
* @brief Scans the user input from screen
* @author Óscar Gómez
* @date 16/12/2016
* @param Graphics* gra (The graphics to scan)
* @param Command* command (The place where you save the command)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS scan_from_screen(Graphics* gra, Command* command);

/**
* @brief Refreshes the graphics
* @author Óscar Gómez
* @date 02/12/2016
* @param Graphics* gra (The graphics to refresh)
* @return STATUS (OK if everything worked, ERROR if didnt)
*/
STATUS graphics_refresh(Graphics* gra);

#endif