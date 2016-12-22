/**
 * @brief Main to test the Game_management module
 * @FILE game_management_test.c
 * @author Andrea Ruiz
 * @version 1.0
 * @date 20/12/2016
 */

#include "test.h"
#include "game_management.h"
 
#define MAX_TESTS 8
#define ID 5
#define pos 2

BOOL test_game_management1(){ /*Test for print_space_save*/
	Space *space = NULL;
	Game * game = NULL;
	FILE * f = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	space = game_get_space(game, ID);
	f = fopen("game_management_space.txt", "w");
	s = print_space_save(f, space);
	if(s == OK){
		game_destroy(game);
		fclose(f);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	fclose(f);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management2(){ /*Test for print_link_save*/
 	Link * link = NULL;
	Game * game = NULL;
	FILE * f = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	link = game_get_link_n(game, pos);
	f = fopen("game_management_link.txt", "w");
	s = print_link_save(f, link);
	if(s == OK){
		game_destroy(game);
		fclose(f);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	fclose(f);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management3(){ /*Test for print_object_save*/
	Object * object = NULL;
	Game * game = NULL;
	FILE * f = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	object = game_get_object(game, ID);
	f = fopen("game_management_object.txt", "w");
	s = print_object_save(f, object);
	if(s == OK){
		game_destroy(game);
		fclose(f);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	fclose(f);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management4(){ /*Test for print_player_save*/ 
	Player * player = NULL;
	Game * game = NULL;
	FILE * f = NULL;
	STATUS s;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	player = game_get_player(game);
	f = fopen("game_management_player.txt", "w");
	s = print_player_save(f, player);
	if(s == OK){
		game_destroy(game);
		fclose(f);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	fclose(f);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management5(){ /*Test for game_save*/  
	STATUS s;
	Game * game = NULL;
	game = game_init(game);
	game_init_from_file(game, "loader.dat");
	s = game_save(game, "game_management_save.txt");
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management6(){ /*Test for game_load_player*/
	Game *game = NULL;
	STATUS s;
	game = game_init(game);
	
	s = game_load_player(game, "1|Player|1|");
	
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management7(){ /*Test for game_load_object*/
	Game *game = NULL;
	STATUS s;
	game = game_init(game);

	s = game_load_object(game, "5|2|Key|This is a key|Try to open a door with it|K|TRUE|2|FALSE|FALSE|FALSE|1|-1|");
	
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}


BOOL test_game_management8(){ /*Test for game_load_link*/
	Game *game = NULL;
	STATUS s;
	game = game_init(game);
	
	s = game_load_link(game, "3|1|4|Door3|OPENL|\n");
	
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management9(){ /*Test for game_load_space*/
	Game *game = NULL;
	STATUS s;
	game = game_init(game);
	
	s = game_load_space(game, "9|Casilla|-1|9|-1|-1|-1|-1|FALSE|EXIT|+------------+|            |+--+   EXIT  |   |         (   |         (   |         |   +---------+/");
	
	if(s == OK){
		game_destroy(game);
		TEST_PRINT(TRUE);
		return TRUE;
	}
	game_destroy(game);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_game_management10(){ /*Test for game_load*/ 
	Game *game = NULL;
	STATUS s;
	game = game_init(game);


	s = game_load(game, "game_management_save.txt");
	
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

	if(todas || test == 1) test_game_management1();
	if(todas || test == 2) test_game_management2();
	if(todas || test == 3) test_game_management3();
	if(todas || test == 4) test_game_management4();
	if(todas || test == 5) test_game_management5();
	if(todas || test == 6) test_game_management6();
	if(todas || test == 7) test_game_management7();
	if(todas || test == 8) test_game_management8();
	if(todas || test == 9) test_game_management9();
	if(todas || test == 10) test_game_management10();

	PRINT_RESULTS();

	return 0;
}
