#include "game_logic.h"

// change later to announce which person won!
unsigned char check_winning_condition(Game *game) {
	// idea will be take the board and check for a column, row or diagonal full of 1s or 2s
	// return 1 if there is a winner, 0 otherwise
	// check rows for the sum is my idea
	if (check_winning_condition_row(game) == 1 || check_winning_condition_column(game) == 1 || check_winning_condition_diagonal(game) == 1) {
		return 1;
	}
	return 0;
}

unsigned char check_winning_condition_row(Game *game) {
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		unsigned char first_item = game->board[i][0];
		for (unsigned char j = 1; j < SQUARE_DIMENSION; j++) {
			printf("(%u, %u) is %u\n", i, j, game->board[i][j]);
			if (game->board[i][j] == 2) {
				return 0;
			}
			if (game->board[i][j] != first_item) {
				return 0;
			} 
		}
	}
	printf("All items are equal.\n");
	return 1;
}

unsigned char check_winning_condition_column(Game *game) {
	unsigned char col_sum = 0;
	for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
		for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
			printf("(%u, %u) is %u\n", i, j, game->board[i][j]);
			col_sum += game->board[i][j];
		}
		printf("Column sum is: %u\n", col_sum);
		if (col_sum == SQUARE_DIMENSION || col_sum == 0) {
			return 1;
		}
		col_sum = 0;
	}
	return 0;
}

unsigned char check_winning_condition_diagonal(Game *game) {
	unsigned char diag_sum = 0;
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			if (i == j) {
				diag_sum += game->board[i][j];
			}
		}
	}
	if (diag_sum == SQUARE_DIMENSION || diag_sum == 0) {
		return 1;
	}
	// now let's check for the bottom to top left to right diagonal sum
	diag_sum = 0;
	for (unsigned char i = SQUARE_DIMENSION - 1; i >= 0; i++) {
		for (unsigned char j = SQUARE_DIMENSION - 1; j >= 0; j++) {
			if (i == j) {
				diag_sum += game->board[i][j];
			}
		}
	}
	if (diag_sum == SQUARE_DIMENSION || diag_sum == 0) {
		return 1;
	}
	return 0;
}
