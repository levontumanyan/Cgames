#include "game_logic.h"

// change later to announce which person won!
unsigned char check_winning_condition(Game *game) {
	// idea will be take the board and check for a column, row or diagonal full of 1s or 2s
	// return 1 if there is a winner, 0 otherwise
	// check rows for the sum is my idea
	if (check_winning_condition_row(game) == 1 || check_winning_condition_column(game) == 1 || check_winning_condition_diagonal_left_right(game) == 1 || check_winning_condition_diagonal_right_left(game) == 1) {
		return 1;
	}
	return 0;
}

unsigned char check_winning_condition_row(Game *game) {
	unsigned char first_item;
	unsigned char all_same;
	for (unsigned char row = 0; row < SQUARE_DIMENSION; row++) {
		first_item = game->board[row][0];
		all_same = 1;
		for (unsigned char col = 0; col < SQUARE_DIMENSION; col++) {
			// printf("(%u, %u) is %u\n", row, col, game->board[row][col]);
			if (game->board[row][col] == 2 || game->board[row][col] != first_item) {
				all_same = 0;
				break;
			}
		}
		if (all_same) {
			return 1; // return 1 if all items in this row are equal
		}
	}
	return 0;
}

unsigned char check_winning_condition_column(Game *game) {
	unsigned char first_item;
	unsigned char all_same;
	for (unsigned char col = 0; col < SQUARE_DIMENSION; col++) {
		first_item = game->board[0][col];
		all_same = 1;
		for (unsigned char row = 0; row < SQUARE_DIMENSION; row++) {
			// printf("(%u, %u) is %u\n", row, col, game->board[row][col]);
			if (game->board[row][col] == 2 || game->board[row][col] != first_item) {
				all_same = 0;
				break;
			}
		}
		if (all_same) {
			return 1; // return 1 if all items in this row are equal
		}
	}
	return 0;
}

// check diagonal from left top to right bottom
unsigned char check_winning_condition_diagonal_left_right(Game *game) {
	unsigned char first_item = game->board[0][0];
	unsigned char all_same = 1;
	unsigned char rowcol = 0;

	while(rowcol < SQUARE_DIMENSION) {
		// printf("(%u, %u) is %u\n", rowcol, rowcol, game->board[rowcol][rowcol]);
		if (game->board[rowcol][rowcol] == 2 || game->board[rowcol][rowcol] != first_item) {
			all_same = 0;
			break;
		}
		rowcol += 1;
	}

	if (all_same) {
		return 1; // return 1 if all items in this row are equal
	}

	return 0;
}

// check the diagonal from right top to bottom left
unsigned char check_winning_condition_diagonal_right_left(Game *game) {
	unsigned char first_item = game->board[0][SQUARE_DIMENSION - 1];
	unsigned char all_same = 1;
	unsigned char row = 0;
	unsigned char col = SQUARE_DIMENSION - 1;

	while(row < SQUARE_DIMENSION) {
		// printf("(%u, %u) is %u\n", row, col, game->board[row][col]);
		if (game->board[row][col] == 2 || game->board[row][col] != first_item) {
			all_same = 0;
			break;
		}
		row += 1;
		col -= 1;
	}

	if (all_same) {
		return 1; // return 1 if all items in this row are equal
	}

	return 0;
}

// check if the game is over as a draw - when all the boxes are filled and no winner has been determined, returns 0 if no draw, 1 if draw
unsigned char check_for_draw(Game *game) {
	for (unsigned char row = 0; row < SQUARE_DIMENSION; row++) {
		for (unsigned char col = 0; col < SQUARE_DIMENSION; col++) {
			if (game->board[row][col] == 2) {
				return 0;
			}
		}
	}
	return 1; // draw
}
