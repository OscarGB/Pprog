#include "space_test.h"
#include "space.h"

int main(void){
	Id id=350;
	Space* space;

	space=test1_space_create(id);
	SPACE_TEST_PRINT(test1_space_get_id(space));
	SPACE_TEST_PRINT(space_get_id(test1_space_create(id))==id);
	SPACE_TEST_PRINT(test1_space_destroy(space));
return 0;
}

Space* test1_space_create(Id id){
	Space* space;
	space = space_create(id);
return space;
	
}

BOOL test1_space_destroy(Space* space){
	space_destroy(space);
	return (space==NULL);
}

BOOL test1_space_get_name(Space* space){
	char* name=NULL;
	name=space_get_name(space);
	return (name!=NULL);
}

BOOL test1_space_set_name(Space* space, char* name){
	space_set_name(space, name);
	return (!strcmp(space_get_name, name));
}

BOOL test1_space_set/get_north(Space* space, Id id){
	space_set_north(space, id);
	return (space_get_north(space)==id);
}

BOOL test1_space_set/get_south(Space* space, Id id){
	space_set_south(space, id);
	return (space_get_south(space)==id);
}

BOOL test1_space_set/get_east(Space* space, Id id){
	space_set_east(space, id);
	return (space_get_east(space)==id);
}

BOOL test1_space_set/get_west(Space* space, Id id){
	space_set_west(space, id);
	return (space_get_west(space)==id);
}

BOOL test1_space_add_object(Space* space, Id id){
	space_add_object(space, id);
	return space_is_object_in(space, id);
}

BOOL test1_space_get_id(Space* space){
	Space* space;
	Id id;
	space=space_create(10);
	id= space_get_id(space)
	space_destroy(space);
	return (id==10);
}

BOOL test1_space_get_object(Space* space){
	Set* set;
	space_add_object(space, 100);
	set=space_get_object(space);
return (set_delete(set, 100)==OK);
}

BOOL test1_space_is_object_in(Space* space, Id id){
	space_add_object(space, id);
	return (space_is_object_in(space, id)==TRUE);
}

BOOL test1_space_print(Space* space){
	return (space_print(space)==OK);
}

BOOL test1_space_set/get_gdesc(Space* space, char * gdesc){
	space_set_gdesc(space, gdesc);
	return (!strcmp(gdesc, space_get_gdesc(space));
}




