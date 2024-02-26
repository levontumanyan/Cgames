#include <assert.h>
#include <stdio.h>

#include <game.h>

// void test_game_not_over(Game *game);
void test_game_board(Game *game);
void test_winning_condition_row();

#define ASSERT(condition, message) \
	do { \
		if (!(condition)) { \
			fprintf(stderr, "%s:%d: Assertion failed: %s. %s\n", __FILE__, __LINE__, #condition, message); \
			assert(condition); \
		} \
	} while(0)
