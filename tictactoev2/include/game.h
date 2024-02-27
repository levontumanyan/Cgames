#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// revisit this later in case if rectangle is also acceptable
#define SQUARE_DIMENSION 3

typedef struct {
	unsigned char board[SQUARE_DIMENSION][SQUARE_DIMENSION];
	// which player's turn it is currently
	unsigned char turn;
} Game;

void game_loop();
Game *start_game();

void monitor_game(ALLEGRO_DISPLAY *display, Game *game);

void draw_board(ALLEGRO_DISPLAY *display);
void draw_x(ALLEGRO_DISPLAY *display, unsigned char row, unsigned char col);
void draw_o(ALLEGRO_DISPLAY *display, unsigned char row, unsigned char col);

void destroy_game(Game *game);
void destroy_all(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP *bitmap);

unsigned char check_winning_condition(Game *game);
unsigned char check_winning_condition_row(Game *game);
unsigned char check_winning_condition_column(Game *game);
unsigned char check_winning_condition_diagonal(Game *game);

#endif
