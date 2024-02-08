#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h> // sleep function

#include "utils.h"

typedef struct {
	int x;
	int y;
} Coordinate;

typedef struct {
	Coordinate body[100]; // Array of coordinates for the snake's body
	int length; // the overall length of the snake
	int direction; // the current direction which the snake is heading
	int speed;
} Snake;

WINDOW* initialize_screen();
Snake* initialize_head(WINDOW *win);
void initialize_game();
char food_eaten(Snake *snake, int *food_coordinates);
int* generate_food(WINDOW* win);
char check_collision(WINDOW *win, Snake* snake);
char check_body_collision(Snake* snake);
void print_the_end(WINDOW *win, Snake* snake);
void game_loop(WINDOW *win, Snake *mysnake);

#endif
