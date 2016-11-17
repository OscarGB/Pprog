/**
 * @brief Implementation for the functions to test the link
 * @file link_test_fun
 * @author Óscar Gómez
 * @version 1.0
 * @date 17/11/2016
 */

#include "test.h"
#include "link.h"
#include "types.h"
 
#define MAX_TESTS 30

Link* link = NULL;
Id id = 3;
char name[] = "Testing";
Id id1 = 5;
Id id2 = 8;


BOOL test_link1(){
	Link* link;
	link = link_create(NO_ID);
	if(!link){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link2(){
	link = link_create(id);
	if(!link){
		return FALSE;
	}
	return TRUE;
}

BOOL test_link3(){
	if(link_get_id(link) == id){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link4(){
	if(strcmp(link_get_name(link), "") == 0){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link5(){
	if(link_get_state(link) == OPEN){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link6(){
	if(link_get_conection1(link) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link7(){
	if(link_get_conection2(link) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link8(){
	if(link_get_id(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link9(){
	if(link_get_name(NULL) == NULL){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link10(){
	if(link_get_state(NULL) == OPEN){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link11(){
	if(link_get_conection1(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link12(){
	if(link_get_conection2(NULL) == NO_ID){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link13(){
	if(link_set_name(link, name) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link14(){
	if(strcmp(link_get_name(link), name) == 0){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link15(){
	if(link_set_conection1(link, id1) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link16(){
	if(link_set_conection2(link, id2) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link17(){
	if(link_get_conection1(link) == id1){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link18(){
	if(link_get_conection2(link) == id2){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link19(){
	if(link_set_state(link, CLOSED) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link20(){
	if(link_get_state(link) == CLOSED){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link21(){
	if(link_set_name(link, NULL) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link22(){
	if(link_set_name(NULL, "") == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link23(){
	if(link_set_conection1(link, NO_ID) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link24(){
	if(link_set_conection1(NULL, id1) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link25(){
	if(link_set_conection2(link, NO_ID) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link26(){
	if(link_set_conection2(NULL, id2) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link27(){
	if(link_set_state(NULL, CLOSED) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link28(){
	if(link_set_state(link, 12) == ERROR){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link29(){
	if(link_destroy(link) == OK){
		return TRUE;
	}
	return FALSE;
}

BOOL test_link30(){
	if(link_destroy(NULL) == ERROR){
		return TRUE;
	}
	return TRUE;
}