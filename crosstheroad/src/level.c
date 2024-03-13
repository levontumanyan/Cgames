#include "level.h"
#include "game.h"

Level start_new_level(Game* game) {
	Level new_level;

	// Calculate the number of roads based on the current level
	if (game->current_level <= 10) {
		new_level.car_lanes = (game->current_level + 2) / 3;
	} 
	else if (game->current_level > 10 && game->current_level < 20) {
		new_level.car_lanes = 4;
	}
	else {
		new_level.car_lanes = 5;
	}

	return new_level;
}
