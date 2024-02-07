#include <stdlib.h>
#include <unistd.h> // sleep function

#include "game.h"
#include "utils.h"

void initialize_game() {
	WINDOW *win = initialize_screen();
	Snake* snake = initialize_head(win);
	game_loop(win, snake);
}

WINDOW* initialize_screen() {
	// Initialize ncurses
	initscr();
	noecho();
	cbreak();

	// Create a window for the snake to move in
	int height = 20, width = 40;
	WINDOW *win = newwin(height, width, 0, 0);

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

Snake* initialize_head(WINDOW *win) {
	Snake* mysnake = malloc(sizeof(Snake));

	// The head will be placed randomly on the board when the game starts
	int* head_coordinates = get_random_coordinates();
	mysnake->body[0].x = head_coordinates[0];
	mysnake->body[0].y = head_coordinates[1];

	// Display the snake's head
	mvwaddch(win, mysnake->body[0].x, mysnake->body[0].y, ACS_CKBOARD);
    wrefresh(win);

	// length is initialized to 1
	mysnake->length = 1;

	// direction is initialized to up, later this can be randomized too
	// assume 0, 1, 2, 3 to be directions - up, right, down, left
	mysnake->direction = 0;

	return mysnake;
}

void game_loop(WINDOW *win, Snake* mysnake) {	
	while (1) {
		int ch = getch();
		// If there's no input, ch will be ERR
		if (ch != ERR) {
			// Handle user input
			switch (ch) {
				case KEY_UP:
					mysnake->direction = 0;
					break;
				case KEY_RIGHT:
					mysnake->direction = 1;
					break;
				case KEY_DOWN:
					mysnake->direction = 2;
					break;
				case KEY_LEFT:
					mysnake->direction = 3;
					break;
				default:
					break;
			}
		}

		// Erase the previous position of the tail
		mvwaddch(win, mysnake->body[mysnake->length - 1].x, mysnake->body[mysnake->length - 1].y, ' ');

		switch (mysnake->direction) {
			case 0:
				// Move the snake up
				mysnake->body[0].x--;
				break;
			case 1:
				// Move the snake right
				mysnake->body[0].y++;
				break;
			case 2:
				// Move the snake down
				mysnake->body[0].x++;
				break;
			case 3:
				// Move the snake left
				mysnake->body[0].y--;
				break;
			
			default:
				break;
		}
		mvwaddch(win, mysnake->body[0].x, mysnake->body[0].y, ACS_CKBOARD);
		wrefresh(win);
		sleep(1);
	}

	// Clean up and close
	endwin();
}
