#ifndef LEVEL_H
#define LEVEL_H

#define MAX_CAR_LANES 6
#define MAX_SAFE_LANES 3

#include "game.h"

typedef struct Level {
	unsigned char car_lanes; // number of car lanes in this level
	unsigned char safe_lanes; // number of safe lanes in this level (minimum two)
	unsigned char time_limit; // amount of time to complete the level
	unsigned char level_is_running; // 0 means level over, 1 means level still running
} Level;

void start_new_level(Game* game, Level* new_level);

#endif
