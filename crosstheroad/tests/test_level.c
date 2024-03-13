#include "test_include.h"
#include "game.h"
#include "level.h"

/* 
	Tests the start_new_level function to make sure that when a game is passed with wrong level it exits early.
*/
void test_start_new_level_0() {
	Game game;
	Level new_level;
	game.current_level = 0;
	game.game_is_running = 1;
	start_new_level(&game, &new_level);

	printf("Checking start new level function with game level 0... ❓\n");
	ASSERT(new_level.level_is_running == 0, "Level is running but shouldn't be. 😨");
	printf("Start new level function is not running as it should.  ✅\n");
	printf("---------------\n");
}

/* 
	Tests the start_new_level function to make sure that when a level is started all the variables are defined properly.
*/
void test_start_new_level_1() {
	Game game;
	Level new_level;
	game.current_level = 1;
	game.game_is_running = 1;
	start_new_level(&game, &new_level);

	printf("Checking start new level function with game level 1... ❓\n");
	ASSERT(new_level.car_lanes == 1, "Number of car lanes is not initialized correctly. 😨");
	ASSERT(new_level.safe_lanes == 1, "Number of safe lanes is not initialized correctly. 😨");
	printf("Start new level function is working fine.  ✅\n");
	printf("---------------\n");
}
