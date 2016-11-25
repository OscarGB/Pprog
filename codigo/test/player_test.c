/**
 * @brief Main to test the Player module
 * @file player_test.c
 * @author José Ignacio Gómez
 * @version 1.0
 * @date 21/11/2016
 */

#include "test.h"
#include "player.h"
#include "types.h"
 
#define MAX_TESTS 14
#define ID 3
#define NAME "Lucille"
#define SPAIN 1

BOOL test_player1(){ /*Test for player create with NO_ID*/
	Player *player = NULL;
	player = player_create(NO_ID);
	if(player == NULL){
		TEST_PRINT(TRUE);
		return TRUE;
	}
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_player2(){ /*Test for player create with  valid ID*/
 	Player* player = NULL;
	player = player_create(ID);
	if(!player){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_player3(){ /*Test for set_name and get_name*/
	Player* player = NULL;
	player = player_create(ID);
	if(player_set_name(player, NAME) == ERROR){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	else if(strcmp(player_get_name(player), NAME) != 0){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_player4(){ /*Test for set_location and get_location*/
	Player* player = NULL;
	player = player_create(ID);
	if(player_set_location(player, SPAIN) == ERROR){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	else if(player_get_location(player) != SPAIN){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_player5(){ /*Test for set_location with invalid location*/
	Player* player = NULL;
	player = player_create(ID);
	if(player_set_location(player, NO_ID) == ERROR){
		player_destroy(player);
		TEST_PRINT(TRUE);
		return TRUE;
	}

	player_destroy(player);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_player6(){ /*Test for drop_object (empty bag)*/
	Player* player = NULL;
	player = player_create(ID);
	if (player_drop_object(player, ID) != FALSE){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_player7(){ /*Test for pick_object (empty bag)*/
	Player* player = NULL;
	player = player_create(ID);
	if (player_pick_object(player, ID) == TRUE){
		player_destroy(player);
		TEST_PRINT(TRUE);
		return TRUE;
	}

	player_destroy(player);
	TEST_PRINT(FALSE);
	return FALSE;
}

BOOL test_player8(){ /*Test for drop_object (non-empty bag)*/
	Player* player = NULL;
	player = player_create(ID);
	player_pick_object(player, ID);
	if(player_drop_object(player, ID) != TRUE){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
	
}


BOOL test_player9(){ /*Test for player_pick_object (full bag)*/
	int i = 0;

	Player* player = NULL;
	player = player_create(ID);

	
	while(i <= player_get_bag_size(player)){
		player_pick_object(player, i);
		i++;
	} /*Player's bag is full*/

	if(player_pick_object(player, i) != FALSE){
		player_destroy(player);
		TEST_PRINT(FALSE);
		return FALSE;
	}

	player_destroy(player);
	TEST_PRINT(TRUE);
	return TRUE;
	
}

BOOL test_player10(){ /*Test for player_destoy (NULL player)*/
	Player* player = NULL;

	if(player_destroy(player) != ERROR){
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
		printf("Pasando todas las pruebas al modulo Player:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Player: \n", test);
	}

	if(todas || test == 1) test_player1();
	if(todas || test == 2) test_player2();
	if(todas || test == 3) test_player3();
	if(todas || test == 4) test_player4();
	if(todas || test == 5) test_player5();
	if(todas || test == 6) test_player6();
	if(todas || test == 7) test_player7();
	if(todas || test == 8) test_player8();
	if(todas || test == 9) test_player9();
	if(todas || test == 10) test_player10();

	PRINT_RESULTS();

	return 0;
}