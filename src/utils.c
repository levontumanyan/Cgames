#include "utils.h"

int* get_random_coordinates(WINDOW* win) {
	static int coordinates[2];

	// Seed the random number generator
	srand(time(NULL));

	// Generate random x and y coordinates
	coordinates[0] = rand() % (getmaxx(win) - 2) + 1;
	coordinates[1] = rand() % (getmaxy(win) - 2) + 1;

	return coordinates;
}
