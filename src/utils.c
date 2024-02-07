#include "utils.h"
#include <stdlib.h>
#include <time.h>

#define MAX_X 19;
#define MAX_Y 19;

int* get_random_coordinates() {
	static int coordinates[2];

	// Seed the random number generator
	srand(time(NULL));

	// Generate random x and y coordinates
	coordinates[0] = rand() % MAX_X;
	coordinates[1] = rand() % MAX_Y;

	return coordinates;
}
