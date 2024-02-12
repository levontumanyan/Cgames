#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#define WINDOW_HEIGHT 20
#define WINDOW_WIDTH 40

typedef struct {
	int x;
	int y;
} Coordinate;

typedef struct {
	Coordinate* body; // Array of coordinates for the snake's body
	unsigned char length; // the overall length of the snake
	unsigned char health; // the current direction which the snake is heading
} Block;

WINDOW* initialize_screen();
void initialize_game();

#endif
