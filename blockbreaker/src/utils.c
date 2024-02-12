#include <stdlib.h>
#include <time.h>

#include "utils.h"

WINDOW* initialize_screen() {
	// Initialize ncurses
	initscr();
	noecho();
	cbreak();
	curs_set(0); // Make the cursor invisible

	// Create a window
	WINDOW *win = newwin(WINDOW_HEIGHT, WINDOW_LENGTH, 0, 0);

	// Enable non-blocking input
	nodelay(stdscr, TRUE);

	// Enable keypad
	keypad(stdscr, TRUE);

	// Display the window
	refresh();
	box(win, 0, 0);
	wrefresh(win);

	return win;
}

unsigned char* get_random_coordinates(WINDOW* win) {
	static unsigned char coordinates[2];

	// Generate random x and y coordinates: 0 is x, 1 is y
	coordinates[0] = rand() % (getmaxx(win) - 4) + 1;
	coordinates[1] = rand() % (getmaxy(win)/2 - 1) + 1;

	return coordinates;
}
