#include <math.h>
#include <stdio.h>

#include "level.h"
#include "game.h"

void start_new_level(Game* game, Level* new_level) {
	if (game->current_level < 1 || game->game_is_running != 1) {
		printf("The game is either not running or current level is less than 1. Exiting...\n");	
		return;
	}

	// Calculate the number of roads based on the current level
	new_level->car_lanes = (int)(2 * log10(game->current_level) + 1);
	if (new_level->car_lanes > MAX_CAR_LANES) {
		new_level->car_lanes = MAX_CAR_LANES;
	}

	new_level->safe_lanes = (int)log(game->current_level) + 1;
	if (new_level->safe_lanes > MAX_SAFE_LANES) {
		new_level->safe_lanes = MAX_SAFE_LANES;
	}

	new_level->level_is_running = 1;
	new_level->time_limit = 90 - (5*game->current_level); // in seconds
}
