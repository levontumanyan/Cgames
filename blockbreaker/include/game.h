#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <unistd.h> // sleep function
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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

typedef struct {
	Coordinate body; // Array of coordinates for the ball
	unsigned char direction; // direction to which the ball is moving - 8 possible dirs
} Ball;

struct handle_user_input_thread_args {
	WINDOW *window;
	Bar *bottom_bar;
};

WINDOW* initialize_screen();
void initialize_game();
void construct_level(WINDOW *window, unsigned char level);
unsigned char monitor_level(WINDOW *window, Bar *bottom_bar);
void game_loop(WINDOW* window);

void handle_user_input(WINDOW *window, Bar *bottom_bar);
void *handle_user_input_thread(void *args);

Bar* generate_bottom_bar(WINDOW *window);
void display_bottom_bar(WINDOW *window, Bar* bottom_bar);
Block* generate_block(WINDOW *window);
void display_block(WINDOW *window, Block *block);

unsigned char is_overlap(Coordinate coordinate);
unsigned char is_overlap_block(Coordinate coordinate, unsigned char length);

void check_for_collision_with_block(Ball *ball);
void check_for_collision_with_bar(Ball *ball, Bar *bottom_bar);
unsigned char check_for_collision_boundaries(WINDOW *window,Ball *ball);

void print_the_end(WINDOW *window, unsigned char current_level);

void debug(WINDOW* window, Ball *ball);

#endif
