/**
 * @brief Main to test the Graphics module
 * @file graphics_test.c
 * @author Óscar Gómez
 * @version 1.0
 * @date 02/12/2016
 */

#include "graphics.h"
#include "test.h"
#include "types.h"
#include <unistd.h>


#define MAX_TESTS 56
#define DELAY 1

BOOL test_graphics1(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(!gra){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics2(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(graphics_destroy(gra) == ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics3(){
	if(graphics_destroy(NULL) == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics4(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(draw_borders(gra) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics5(){
	if(draw_borders(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics6(){
	if(graphics_clear(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics7(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, DIALOGUE, N, "HELLO");
	print_in_zone(gra, COMMANDS, 0, "HOW ARE YOU?");
	print_in_zone(gra, PLAYGROUND, NW, "¡LET'S PLAY!");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear(gra) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics8(){
	if(graphics_clear(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics9(){
	if(graphics_clear_zone(NULL, COMMANDS) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics10(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(graphics_clear_zone(gra, 8) != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics11(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, DIALOGUE, N,"TESTING WITH A LONG SENTENCE TO SEE IF IT WORKS CORRECTLY");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, DIALOGUE) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics12(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, COMMANDS, 0,"TESTING");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, COMMANDS) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics13(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, NW,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra,PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics14(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, N,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics15(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, NE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics16(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, W,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics17(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, C,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics18(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, E,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics19(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, SW,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics20(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, S,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics21(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, SE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics22(){
	if(print_in_zone(NULL, PLAYGROUND, NW, "TESTING") != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics23(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(print_in_zone(gra, 8, NW, "TESTING") != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics24(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(print_in_zone(gra, PLAYGROUND, 805, "TESTING") != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics25(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	if(print_in_zone(gra, DIALOGUE, E, NULL) != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics26(){
	if(graphics_refresh(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics27(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, PLAYGROUND, NW,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, N,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, NE,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, W,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, C,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, E,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, SW,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, S,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, SE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics28(){
	Graphics* gra = NULL;
	gra = graphics_create(0);
	print_in_zone(gra, DIALOGUE, 0, "TESTING 2");
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_clear(gra);
	if(print_in_zone(gra, DIALOGUE, 0, "TESTING 1") == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics29(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(!gra){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics30(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(graphics_destroy(gra) == ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics31(){
	if(graphics_destroy(NULL) == OK){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics32(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(draw_borders(gra) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics33(){
	if(draw_borders(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics34(){
	if(graphics_clear(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics35(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, DIALOGUE, N, "HELLO");
	print_in_zone(gra, COMMANDS, 0, "HOW ARE YOU?");
	print_in_zone(gra, PLAYGROUND, NW, "¡LET'S PLAY!");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear(gra) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics36(){
	if(graphics_clear(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics37(){
	if(graphics_clear_zone(NULL, COMMANDS) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics38(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(graphics_clear_zone(gra, 8) != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics39(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, DIALOGUE, N,"TESTING WITH A LONG SENTENCE TO SEE IF IT WORKS CORRECTLY");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, DIALOGUE) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics40(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, COMMANDS, 0,"TESTING");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, COMMANDS) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics41(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, NW,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra,PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics42(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, N,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics43(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, NE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics44(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, W,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics45(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, C,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics46(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, E,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics47(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, SW,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics48(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, S,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics49(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, SE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics50(){
	if(print_in_zone(NULL, PLAYGROUND, NW, "TESTING") != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics51(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(print_in_zone(gra, 8, NW, "TESTING") != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics52(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(print_in_zone(gra, PLAYGROUND, 805, "TESTING") != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics53(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	if(print_in_zone(gra, DIALOGUE, E, NULL) != ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics54(){
	if(graphics_refresh(NULL) != ERROR){
		TEST_PRINT(FALSE);
		return FALSE;
	}
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics55(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, PLAYGROUND, NW,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, N,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, NE,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, W,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, C,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, E,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, SW,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, S,"--------------|            ||            ||            ||            ||            |--------------");
	print_in_zone(gra, PLAYGROUND, SE,"--------------|            ||            ||            ||            ||            |--------------");
	graphics_refresh(gra);
	sleep(DELAY);
	if(graphics_clear_zone(gra, PLAYGROUND) == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

BOOL test_graphics56(){
	Graphics* gra = NULL;
	gra = graphics_create(1);
	print_in_zone(gra, DIALOGUE, 0, "TESTING 2");
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_clear(gra);
	if(print_in_zone(gra, DIALOGUE, 0, "TESTING 1") == ERROR){
		graphics_destroy(gra);
		TEST_PRINT(FALSE);
		return FALSE;
	}
	graphics_refresh(gra);
	sleep(DELAY);
	graphics_destroy(gra);
	TEST_PRINT(TRUE);
	return TRUE;
}

int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas al modulo Graphics:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo Graphics: \n", test);
	}

	if(todas || test == 1) test_graphics1();
	if(todas || test == 2) test_graphics2();
	if(todas || test == 3) test_graphics3();
	if(todas || test == 4) test_graphics4();
	if(todas || test == 5) test_graphics5();
	if(todas || test == 6) test_graphics6();
	if(todas || test == 7) test_graphics7();
	if(todas || test == 8) test_graphics8();
	if(todas || test == 9) test_graphics9();
	if(todas || test == 10) test_graphics10();
	if(todas || test == 11) test_graphics11();
	if(todas || test == 12) test_graphics12();
	if(todas || test == 13) test_graphics13();
	if(todas || test == 14) test_graphics14();
	if(todas || test == 15) test_graphics15();
	if(todas || test == 16) test_graphics16();
	if(todas || test == 17) test_graphics17();
	if(todas || test == 18) test_graphics18();
	if(todas || test == 19) test_graphics19();
	if(todas || test == 20) test_graphics20();
	if(todas || test == 21) test_graphics21();
	if(todas || test == 22) test_graphics22();
	if(todas || test == 23) test_graphics23();
	if(todas || test == 24) test_graphics24();
	if(todas || test == 25) test_graphics25();
	if(todas || test == 26) test_graphics26();
	if(todas || test == 27) test_graphics27();
	if(todas || test == 28) test_graphics28();
	if(todas || test == 29) test_graphics29();
	if(todas || test == 30) test_graphics30();
	if(todas || test == 31) test_graphics31();
	if(todas || test == 32) test_graphics32();
	if(todas || test == 33) test_graphics33();
	if(todas || test == 34) test_graphics34();
	if(todas || test == 35) test_graphics35();
	if(todas || test == 36) test_graphics36();
	if(todas || test == 37) test_graphics37();
	if(todas || test == 38) test_graphics38();
	if(todas || test == 39) test_graphics39();
	if(todas || test == 40) test_graphics40();
	if(todas || test == 41) test_graphics41();
	if(todas || test == 42) test_graphics42();
	if(todas || test == 43) test_graphics43();
	if(todas || test == 44) test_graphics44();
	if(todas || test == 45) test_graphics45();
	if(todas || test == 46) test_graphics46();
	if(todas || test == 47) test_graphics47();
	if(todas || test == 48) test_graphics48();
	if(todas || test == 49) test_graphics49();
	if(todas || test == 50) test_graphics50();
	if(todas || test == 51) test_graphics51();
	if(todas || test == 52) test_graphics52();
	if(todas || test == 53) test_graphics53();
	if(todas || test == 54) test_graphics54();
	if(todas || test == 55) test_graphics55();
	if(todas || test == 56) test_graphics56();
	PRINT_RESULTS();

	return 0;
}