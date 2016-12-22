/**
 * @brief Main to test the Game_rules module
 * @file game_rules_test.c
 * @author Andrea Ruiz
 * @version 1.0
 * @date 17/12/2016
 */

#include "test.h"
#include "game_rules.h"
 
#define MAX_TESTS 8
#define ID 10

BOOL test_game_rules1(){ /*Test for change_light_space with valid game*/
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = change_light_space(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules2(){ /*Test for change_link_state with valid game*/
 	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = change_link_state(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules3(){ /*Test for change_object_location with valid game*/
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = change_object_location(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules4(){ /*Test for kill_player with valid game*/ 
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = kill_player(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules5(){ /*Test for useless_player_deserves_death with valid game*/  
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = useless_player_deserves_death(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules6(){ /*Test for turn_object_light_off with valid game*/ 
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = turn_object_light_off(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules7(){ /*Test for pick_aleat_function with valid game*/
	Game *game = NULL;
	Graphics * graphics = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	graphics = graphics_create(0);
	s = pick_aleat_function(game, graphics);
	if(s == OK){
		game_destroy(game);
		graphics_destroy(graphics);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	graphics_destroy(graphics);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_rules8(){ /*Test for pick_aleat_function with non valid game and non valid graphics*/
	Game *game = NULL;
	STATUS s;
	Graphics * graphics = NULL;
	s = pick_aleat_function(game, graphics);
	if(s == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_game_rules9(){ /*Test for pick_aleat_function with non valid game and valid graphics*/
	Game *game = NULL;
	STATUS s;
	Graphics * graphics = NULL;
	graphics = graphics_create(0);
	s = pick_aleat_function(game, graphics);
	if(s == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_game_rules10(){ /*Test for pick_aleat_function with valid game and non valid graphics*/
	Game *game = NULL;
	STATUS s;
	Graphics * graphics = NULL;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	s = pick_aleat_function(game, graphics);
	if(s == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
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

	if(todas || test == 1) test_game_rules1();
	if(todas || test == 2) test_game_rules2();
	if(todas || test == 3) test_game_rules3();
	if(todas || test == 4) test_game_rules4();
	if(todas || test == 5) test_game_rules5();
	if(todas || test == 6) test_game_rules6();
	if(todas || test == 7) test_game_rules7();
	if(todas || test == 8) test_game_rules8();
	if(todas || test == 8) test_game_rules9();
	if(todas || test == 8) test_game_rules10();

	PRINT_RESULTS();

	return 0;
}
