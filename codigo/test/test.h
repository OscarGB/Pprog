#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wsequence-point"
#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NO_COLORS
#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define YELLOW "\x1B[33m"
#define GREEN "\x1B[32m"
#define RESET "\033[0m"
#else
#define RED 1
#define BLUE 1
#define YELLOW 1
#define GREEN 1
#define RESET 1
#endif


static int test_passed=0;
static int pass=0;
static int test_counter=0;
static int number_test_passed=0;

#define TEST_PRINT(x) do{\
pass= (x);\
test_counter++;\
test_passed = (pass)? test_passed=1 : test_passed;\
(pass)? number_test_passed++ : number_test_passed;\
printf(YELLOW "%s " RESET "line " "%d " BLUE "%s: " , __FILE__, __LINE__, __FUNCTION__);\
printf(RESET "%s\n", (pass)? GREEN "PASS" RESET : RED "ERROR" RESET);\
}while(0)

#define PRINT_RESULTS() do{\
	if(test_counter == number_test_passed){\
		printf(GREEN "ALL TESTS PASSED\n");\
	}\
	else{\
		printf(YELLOW "%d/%d TESTS PASSED, " RED "%d/%d TESTS FAILED\n", number_test_passed, test_counter, test_counter - number_test_passed, test_counter);\
	}\
}while(0)
