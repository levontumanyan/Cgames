#include <time.h>
#include <stdlib.h>

#include <unistd.h> // for sleep function

#include <ncurses.h>

int* get_random_coordinates();
WINDOW* initialize_screen();
void game_loop(WINDOW* win);

typedef struct {
	int x;
	int y;
} Coordinate;

typedef struct {
	Coordinate body[100]; // Array of coordinates for the snake's body
	int length; // the overall length of the snake
	int direction; // the current direction which the snake is heading
} Snake;

int main() {
	WINDOW *win = initialize_screen();
	game_loop(win);
	return 0;
}

WINDOW* initialize_screen() {
	// Initialize ncurses
	initscr();
	noecho();
	cbreak();

	// Create a window for the snake to move in
	int height = 20, width = 40;
	WINDOW *win = newwin(height, width, 0, 0);

	// Display the window
	refresh();
	box(win, 0, 0);
	wrefresh(win);

	return win;
}

void game_loop(WINDOW *win) {
	Snake mysnake;

	// The head will be placed randomly on the board when the game starts
	int* head_coordinates = get_random_coordinates();
	mysnake.body[0].x = head_coordinates[0];
	mysnake.body[0].y = head_coordinates[1];

	// Display the snake's head
	mvwaddch(win, mysnake.body[0].x, mysnake.body[0].y, ACS_CKBOARD);
    wrefresh(win);

	// length is initialized to 1
	mysnake.length = 1;

	// direction is initialized to up, later this can be randomized too
	// assume 0, 1, 2, 3 to be directions - up, right, down, left
	mysnake.direction = 1;

	while (1) {
		// Wait for user input
		// getch();
		switch (mysnake.direction) {
		case 0:
			// Move the snake up
			mysnake.body[0].x--;
			break;
		case 1:
			// Move the snake right
			mysnake.body[0].y++;
			break;
		case 2:
			// Move the snake down
			mysnake.body[0].x++;
			break;
		case 3:
			// Move the snake left
			mysnake.body[0].y--;
			break;
		
		default:
			break;
		}
		mvwaddch(win, mysnake.body[0].x, mysnake.body[0].y, ACS_CKBOARD);
		wrefresh(win);
		sleep(1);
	}

	// Clean up and close
	endwin();
}

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
