#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

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
	// which player's turn it is currently
	unsigned char turn;
} Game;

typedef struct {
	unsigned char row;
	unsigned char col;
} Cell;

void game_loop();
Game *start_game();

void monitor_game(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, ALLEGRO_EVENT_QUEUE *event_queue, Game *game);

void draw_board(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap);
void draw_x(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap,unsigned char row, unsigned char col);
void draw_o(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, unsigned char row, unsigned char col);

ALLEGRO_MOUSE_EVENT get_mouse_click_event(ALLEGRO_EVENT_QUEUE *event_queue);
unsigned char check_click_out_of_bounds(ALLEGRO_DISPLAY *display, ALLEGRO_MOUSE_EVENT click_event);

void destroy_game(Game *game);
void destroy_all(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP *bitmap);

unsigned char check_winning_condition(Game *game);
unsigned char check_winning_condition_row(Game *game);
unsigned char check_winning_condition_column(Game *game);
unsigned char check_winning_condition_diagonal(Game *game);

#endif
