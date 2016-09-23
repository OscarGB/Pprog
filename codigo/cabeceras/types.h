/* ===================================================================
File: types.h

Version: 1.0

Date: 23/09/2016

Author: Óscar Gómez, Jose Ignacio Gómez.

Description: It defines common types

Revision history: none

=================================================================== */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
    ERROR, OK
} STATUS;

typedef enum {
    N, S, E, W
} DIRECTION;

#endif
