/**
 * @brief Main to test the Game_rules module
 * @file game_rules_test.c
 * @author Andrea Ruiz
 * @version 1.0
 * @date 17/12/2016
 */

#include "test.h"
#include "game_rules.h"
 
#define MAX_TESTS 7

BOOL test_game1(){ /*Test for change_light_space with valid game*/
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = change_light_space(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game2(){ /*Test for change_link_state with valid game*/
 	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = change_link_state(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game3(){ /*Test for change_object_location with valid game*/
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = change_object_location(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game4(){ /*Test for kill_player with valid game*/ 
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = kill_player(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game5(){ /*Test for useless_player_deserves_death with valid game*/  
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = useless_player_deserves_death(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game6(){ /*Test for turn_object_light_off with valid game*/ 
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = turn_object_light_off(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game7(){ /*Test for pick_aleat_function with valid game*/
	Game *game = NULL;
	STATUS s;
	game = game_create(game);
	s = pick_aleat_function(game);
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}
int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Game:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Game: \n", test);
	}

	if(todas || test == 1) test_game1();
	if(todas || test == 2) test_game2();
	if(todas || test == 3) test_game3();
	if(todas || test == 4) test_game4();
	if(todas || test == 5) test_game5();
	if(todas || test == 6) test_game6();
	if(todas || test == 7) test_game7();

	PRINT_RESULTS();

	return 0;
}
