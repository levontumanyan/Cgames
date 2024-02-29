#include "test_include.h"

void test_winning_condition_row() {
	printf("Creating a new game... \n");
	Game *game = start_game();
	printf("Setting the board to have all zeroes on the first row. \n");
	for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
		game->board[0][j] = 0;
	}
	printf("Checking to see if winning condition will work for a row of zeroes.❓\n");
	ASSERT(check_winning_condition(game) == 1, "Winning condition function not working 😨");
	printf("Winning condition is successful for first row of zeroes. ✅\n");
	free(game);
}

