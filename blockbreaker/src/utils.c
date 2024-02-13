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

Coordinate get_random_coordinates(WINDOW* win) {
	static Coordinate coordinate;

	// Generate random x and y coordinates: 0 is x, 1 is y
	coordinate.x = rand() % (getmaxx(win) - 4) + 1;
	coordinate.y = rand() % (getmaxy(win)/2 - 1) + 2;

	return coordinate;
}
