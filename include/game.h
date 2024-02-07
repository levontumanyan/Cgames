#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

typedef struct {
	int x;
	int y;
} Coordinate;

typedef struct {
	Coordinate body[100]; // Array of coordinates for the snake's body
	int length; // the overall length of the snake
	int direction; // the current direction which the snake is heading
} Snake;

WINDOW* initialize_screen();
Snake* initialize_head(WINDOW *win);
void game_loop(WINDOW *win, Snake* mysnake);
void initialize_game();
char food_eaten(Snake* snake, int* food_coordinates);
int* generate_food(WINDOW *win);

#endif
