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

void display_board() {

}
