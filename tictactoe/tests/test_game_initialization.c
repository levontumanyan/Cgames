#include "test_include.h"

/* void test_game_not_over(Game *game) {
	printf("Checking to make sure game over is properly set.❓\n");
	ASSERT(game->game_over == 0, "Game over is not false, check code. 😨");
	printf("Game over is properly set. ✅\n");
} */

void test_game_board(Game *game) {
	printf("Checking to make sure game board is properly set.❓\n");
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			ASSERT(game->board[i][j] == 2, "Game board is not initialized properly. 😨");
		}
	}
	printf("Game board is initialized properly. ✅\n");
}
