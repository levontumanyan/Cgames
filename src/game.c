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
	int* head_coordinates = get_random_coordinates(win);
	mysnake->body[0].x = head_coordinates[0];
	mysnake->body[0].y = head_coordinates[1];

	// Display the snake's head
	mvwaddch(win, mysnake->body[0].y, mysnake->body[0].x, ACS_CKBOARD);
    wrefresh(win);

	// length is initialized to 1
	mysnake->length = 1;

	// direction is initialized to up, later this can be randomized too
	// assume 0, 1, 2, 3 to be directions - up, right, down, left
	mysnake->direction = 0;

	return mysnake;
}

int* generate_food(WINDOW *win) {
	int* food_coordinates = get_random_coordinates(win);

	// Erase the previous position of the tail
	mvwaddch(win, food_coordinates[1], food_coordinates[0], '$');

	return food_coordinates;
}

char food_eaten(Snake* snake, int* food_coordinates) {
	char is_food_eaten = 0;

	if (food_coordinates[0] == snake->body[0].x && food_coordinates[1] == snake->body[0].y) {
		is_food_eaten = 1;
		snake->length++;
	}
	return is_food_eaten;
}

char check_collision(WINDOW *win, Snake* snake) {
	char collision;
	if (snake->body[0].x > getmaxx(win) - 2 || snake->body[0].x < 1 || snake->body[0].y > getmaxy(win) - 2 || snake->body[0].y < 1) {
		collision = 1;
	}
	else {
		collision = 0;
	}
	return collision;
}

void print_the_end(WINDOW *win, Snake* snake) {
	// move the cursor to the center of the screen
	move(getmaxy(win) / 2, getmaxx(win) / 2 - 10);

	// Display the end banner
	printw("Game Over! Your Score: %d", snake->length);

	// Refresh the screen to update the changes
	wrefresh(win);

}

void game_loop(WINDOW *win, Snake* mysnake) {
	unsigned char food_exists = 0;
	int* food_coordinates;
	char collision = 0;

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
		mvwaddch(win, mysnake->body[mysnake->length - 1].y, mysnake->body[mysnake->length - 1].x, ' ');

		switch (mysnake->direction) {
			case 0:
				// Move the snake up
				mysnake->body[0].y--;
				break;
			case 1:
				// Move the snake right
				mysnake->body[0].x++;
				break;
			case 2:
				// Move the snake down
				mysnake->body[0].y++;
				break;
			case 3:
				// Move the snake left
				mysnake->body[0].x--;
				break;
			
			default:
				break;
		}
		mvwaddch(win, mysnake->body[0].y, mysnake->body[0].x, ACS_CKBOARD);
		wrefresh(win);
		if (food_exists == 0) {
			food_coordinates = generate_food(win);
			food_exists = 1;
		}
		if (food_eaten(mysnake, food_coordinates) == 1) {
			food_exists = 0;
		}

		// in case of a collision print the end banner and exit the loop
		collision = check_collision(win, mysnake);
		if (collision == 1) {
			print_the_end(win, mysnake);
			// Wait for a key press before exiting
			nodelay(stdscr, FALSE);
			getch();
			break;
		}

		wrefresh(win);
		// Move the cursor to the bottom of the window and print debugging information
        move(getmaxy(win) - 1, 0);
        clrtoeol();  // Clear the current line
        printw("Snake's head is at: %d, %d: Collision: %d\n", mysnake->body[0].x, mysnake->body[0].y, collision);
        printw("Maxx: %d Maxy: %d", getmaxx(win), getmaxy(win));

        // Refresh the screen to update the changes
        wrefresh(win);
		sleep(1);
	}

	// Clean up and close
	endwin();
}
