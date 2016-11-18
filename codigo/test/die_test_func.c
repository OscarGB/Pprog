/**
 * @brief Implementation for the functions to test the Die module
 * @file die_test_func.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 17/11/2016
 */

#include "test.h"
#include "die.h"
#include "types.h"
 
#define MAX_TESTS 14

 Die* die = NULL;
 Id id = 3;
 int roll;

BOOL test_die1(){
	die = die_create(NO_ID);
	if(die == NULL){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die2(){
	die = die_create(id);
	if(!die){
		return FALSE;
	}
	return TRUE;
}

BOOL test_die3(){
	if(!die){
		die = die_create(id);
	}
	if(die_get_id(die) == id){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die4(){
	if(die_get_id(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die5(){
	if(!die){
		die = die_create(id);
	}
	roll = die_roll(die, 1, 6);
	if(roll < 1 || roll > 6){
		return FALSE;
	}
	return TRUE;
}

BOOL test_die6(){
	if(!die){
		die = die_create(id);
		roll = die_roll(die, 1, 6);
	}
	if(die_get_last_roll(die) == roll){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die7(){
	if(die_roll(NULL, 1, 6) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die8(){
	if(die_roll(die, -1, 1) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die9(){
	if(die_roll(die, 1, -1) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die10(){
	if(die_roll(die, 6, 1) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die11(){
	if(die_get_last_roll(NULL) == -1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die12(){
	if(die_print(NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die13(){
	if(!die){
		die = die_create(id);
	}
	if(die_destroy(die) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_die14(){
	if(die_destroy(NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}

void end_test(){
	die_destroy(die);
	return;
}