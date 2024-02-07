#include "utils.h"
#include <stdlib.h>
#include <time.h>

#define MAX_X 16;
#define MAX_Y 36;

int* get_random_coordinates() {
	static int coordinates[2];

	// Seed the random number generator
	srand(time(NULL));

	// Generate random x and y coordinates
	coordinates[0] = rand() % MAX_X + 1;
	coordinates[1] = rand() % MAX_Y + 1;

	return coordinates;
}
