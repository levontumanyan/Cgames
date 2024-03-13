#include "test_include.h"
#include "game.h"

/* 
	Tests the game initialization function, to make sure that things like current_level and game_is_running are set properly.
*/
void test_initialize_game() {
	printf("---------------\n");
	Game game;
	initialize_game(&game);

	printf("Checking initialize game function... ❓\n");
	ASSERT(game.game_is_running == 1, "Game is running is not 1. 😨");
	ASSERT(game.current_level == 1, "Game did not initialize at level 1. 😨");
	printf("Initialize game function is working.  ✅\n");
	printf("---------------\n");
}
