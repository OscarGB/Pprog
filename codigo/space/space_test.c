/**
 * @brief Test module for Space
 * @file space_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 10/11/2016
 */



int main(){
	Space* space = NULL;
	Set* set = NULL;

	fprintf(stdout, "TESTING SPACE MODULE\n");

	/*Test the space_create*/
 	fprintf(stdout, "Creating the space\n");
 	space = space_create(2);
 	if(!space){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: CREATING THE SPACE\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test get_id*/
 	if(space_get_id(space) != 2){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE ID\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test set_name and get_name*/
 	fprintf(stdout, "Testing name functions\n");
 	if(space_set_name(space, "Test") == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE NAME\n");
		#endif
		return 1;
 	}
 	if(strcmp(space_get_name(space), "Test")){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE NAME\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test the set_north and get_north*/
 	fprintf(stdout, "Testing north functions\n");
 	if(space_set_north(space, 2) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE NORTH\n");
		#endif
		return 1;
 	}
 	if(space_get_north(space) != 2){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE NORTH\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test the set_south and get_south*/
 	fprintf(stdout, "Testing south functions\n");
 	if(space_set_south(space, 3) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE SOUTH\n");
		#endif
		return 1;
 	}
 	if(space_get_south(space) != 3){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE SOUTH\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test the set_east and get_east*/
 	fprintf(stdout, "Testing east functions\n");
 	if(space_set_east(space, 4) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE EAST\n");
		#endif
		return 1;
 	}
 	if(space_get_east(space) != 4){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE EAST\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test the set_west and get_west*/
 	fprintf(stdout, "Testing west functions\n");
 	if(space_set_west(space, 5) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE WEST\n");
		#endif
		return 1;
 	}
 	if(space_get_west(space) != 5){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE WEST\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test add_object, get_object, is_object_in*/
 	if(space_add_object(space, 3) == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: ADDING AN OBJECT\n");
		#endif
		return 1;
 	}
 	if(space_is_object_in(space, 3) == FALSE){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SEARCHING AN OBJECT\n");
		#endif
		return 1;
 	}
 	if(space_is_object_in(space, 4) != FALSE){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SEARCHING AN OBJECT THAT IS NOT IN THE SPACE\n");
		#endif
		return 1;
 	}
 	set = space_get_object(space);
 	if(!set){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE OBJECT'S SET\n");
		#endif
		return 1;
 	}
 	if(set_is_id(set, 3) == FALSE){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: THE OBJECT ISN'T IN THE SET\n");
		#endif
		return 1;
 	}
 	fprintf(stdout, "OK\n");

 	/*Test set_gdesc and get_gdesc*/
 	if(space_set_gdesc(space, "Testing") == ERROR){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: SETTING THE GDESC\n");
		#endif
		return 1;
 	}
 	if(strcmp(space_Get_gdesc(space), "Testing")){
 		#ifdef DEBUG
		fprintf(stderr, "ERROR DEBUGING: GETTING THE GDESC\n");
		#endif
		return 1;
 	}

 	space_destroy(space);



	return 0;
}