#include "level.h"
#include "game.h"

void start_new_level(Game* game, Level* new_level) {
	// Calculate the number of roads based on the current level
	new_level->car_lanes = (int)log(game->current_level) + 1;
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
