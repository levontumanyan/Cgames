#include "test_include.h"

int main() {
	// initialize a game struct
	Game *game = start_game();
	// test_game_not_over(game);
	test_game_board(game);
	test_winning_condition_row();
}
