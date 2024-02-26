#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>

#define SQUARE_DIMENSION 3

typedef struct {
	unsigned char board[SQUARE_DIMENSION][SQUARE_DIMENSION];
	// which player's turn it is currently
	unsigned char turn;
} Game;

void game_loop();
Game *start_game();
void monitor_game(WINDOW *win, Game *game);
void destroy_game(Game *game);

unsigned char check_winning_condition(Game *game);
unsigned char check_winning_condition_row(Game *game);
unsigned char check_winning_condition_column(Game *game);
unsigned char check_winning_condition_diagonal(Game *game);

#endif
