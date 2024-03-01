#ifndef GAME_H
#define GAME_H

#include <time.h> // for the random function to pick a player to start
#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>

// revisit this later in case if rectangle is also acceptable
#define SQUARE_DIMENSION 3

// each cell's width and height in pixels
#define CELL_WIDTH 150
#define CELL_HEIGHT 150

// Starting x and y coordinates of the board to be drawn
#define DISPLAY_WIDTH al_get_display_width(display)
#define DISPLAY_HEIGHT al_get_display_height(display)
#define START_X ((DISPLAY_WIDTH) / 2 - SQUARE_DIMENSION * CELL_WIDTH)
#define START_Y ((DISPLAY_HEIGHT) / 2 - SQUARE_DIMENSION * CELL_HEIGHT)
#define END_X (START_X + SQUARE_DIMENSION * CELL_WIDTH)
#define END_Y (START_Y + SQUARE_DIMENSION * CELL_HEIGHT)

typedef struct {
	unsigned char board[SQUARE_DIMENSION][SQUARE_DIMENSION];
	// which player's turn it is currently, 0 for O, 1 for x
	unsigned char turn;
} Game;

typedef struct {
	unsigned char row;
	unsigned char col;
} Cell;

void game_loop();
Game *start_game();

void monitor_game(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, ALLEGRO_EVENT_QUEUE *event_queue, Game *game);

void destroy_game(Game *game);

#endif
