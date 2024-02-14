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
	// turns this into a random function
	game->turn = 0;
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			game->board[i][j] = 0;
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

void destroy_game(Game *game) {
	free(game);
}
