#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

typedef struct {
	int x;
	int y;
} Coordinate;

typedef struct {
	Coordinate* body; // Array of coordinates
	unsigned char length; // the overall block
	unsigned char health; // health of the block
} Block;

typedef struct {
	Coordinate* body; // Array of coordinates for the bottom bar
	unsigned char length; // the overall length of the bar
} Bar;

WINDOW* initialize_screen();
void initialize_game();
void construct_level(WINDOW *window, unsigned char level);
void monitor_level(WINDOW *window, Bar *bottom_bar, unsigned char level);
void game_loop(WINDOW* window);
void handle_user_input(WINDOW *window, Bar *bottom_bar);
Bar* generate_bottom_bar(WINDOW *window);
void display_bottom_bar(WINDOW *window, Bar* bottom_bar);
Block* generate_block(WINDOW *window);
void display_block(WINDOW *window, Block *block);
#endif
