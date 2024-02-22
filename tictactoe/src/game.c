#include "game.h"
#include "utils.h"

void game_loop() {
	WINDOW *window = initialize_screen();
	while(1) {
		Game *new_game = start_game();
		if (new_game == NULL) {
			continue;
		}
		monitor_game(window, new_game);
		destroy_game(new_game);
	}
}

Game *start_game() {
	Game *game = malloc(sizeof(Game));
	if (game == NULL) {
		return NULL;
	}
	game->game_over = 0;
	// turn this into a random function
	game->turn = 1;

	// fill up the game board with 2s each time a user clicks on a box that cell's value in the board will become either 0 or 1. 0 for 0, 1 for x
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			game->board[i][j] = 2;
		}
	}
	return game;
}

void monitor_game(WINDOW *win, Game *game) {
	while(1) {
		draw_board(win);
		if (game->game_over == 1) {
			break;
		}
	}
}

unsigned char check_winning_condition(Game *game) {
	// idea will be take the board and check for a line or diagonal full of 1s or 2s
	// return 1 if there is a winner, 0 otherwise
	// check rows for the sum is my idea
	unsigned char row_sum = 0;
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			row_sum += game->board[i][j];
		}
		if (row_sum == SQUARE_DIMENSION || row_sum == 0) {
			return 1;
		}
	}
}

void destroy_game(Game *game) {
	free(game);
}
