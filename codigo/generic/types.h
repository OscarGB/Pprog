/**
 * @brief It defines common types
 * @file types.h
 * @author Óscar Gómez, José Ignacio Gómez
 * @version 1.0
 * @date 23/09/2016
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*!< Macro for the word size*/
#define NO_ID -1 /*!< Macro for an invalid ID*/

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
    ERROR = -1, OK = 0
} STATUS;

typedef enum {
    N = 0, NE, E, SE, S, SW, W, NW, C
} DIRECTION;

#endif
