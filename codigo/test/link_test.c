#include "test.h"
#include "link.h"
#include "types.h"

Link* link = NULL;
Id id = 3;


BOOL test1_link(){
	Link* link;
	link = link_create(NO_ID);
	if(!link){
		return TRUE;
	}
	return FALSE;
}

BOOL test2_link(){
	link = link_create(id);
	if(!link){
		return FALSE;
	}
	return TRUE;
}

BOOL test3_link(){
	if(link_get_id(link) == id){
		return TRUE;
	}
	return FALSE;
}


int main(){
	TEST_PRINT(test1_link());
	TEST_PRINT(test2_link());
	TEST_PRINT(test3_link());
	return 0;
}