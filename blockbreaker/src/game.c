#include <stdlib.h>

#include "game.h"
#include "utils.h"

#define NUM_OF_BLOCKS(x) ((x) + 3)


void initialize_game() {
	WINDOW *win = initialize_screen();
	game_loop(win);
}

void construct_level(WINDOW *window, unsigned char level) {
	// how many blocks to display
	for(unsigned char i = 0; i < NUM_OF_BLOCKS(level); i++ ) {
		Block *block = generate_block(window);
		display_block(window, block);
	}
}

Block* generate_block(WINDOW *window) {
	Block* block = malloc(sizeof(Block));
	block->length = 3;
	block->body = malloc(block->length * sizeof(Coordinate));
	block->health = 1;
	unsigned char* coordinates = get_random_coordinates(window);
	for (unsigned char i = 0; i < block->length; i++) {
		block->body[i].x = coordinates[0] + i;
		block->body[i].y = coordinates[1];
	}
	return block;
}

void display_block(WINDOW *window, Block *block) {
	// Display the block
	for (unsigned char i = 0; i < block->length; i++) {
		mvwaddch(window, block->body[i].y, block->body[i].x, ACS_CKBOARD);
	}
	wrefresh(window);
}

void monitor_level(WINDOW *window, Bar *bottom_bar, unsigned char level) {
	unsigned char blocks_left = NUM_OF_BLOCKS(level);

	while (blocks_left > 0) {
		handle_user_input(window, bottom_bar);
	}
}

Bar *generate_bottom_bar(WINDOW *window) {
	Bar *bar = malloc(sizeof(Bar));
	bar->length = 5;
	bar->body = malloc(bar->length * sizeof(Coordinate));
	
	for (unsigned char i = 0; i < bar->length; i++) {
		bar->body[i].x = getmaxx(window)/2 - 2 + i;
		bar->body[i].y = getmaxy(window) - 2;
	}
	return bar;
}

void display_bottom_bar(WINDOW *window, Bar* bottom_bar) {
	// Display the block
	for (unsigned char i = 0; i < bottom_bar->length; i++) {
		mvwaddch(window, bottom_bar->body[i].y, bottom_bar->body[i].x, ACS_CKBOARD);
	}
	wrefresh(window);
}

void handle_user_input(WINDOW *window, Bar *bottom_bar) {
	int ch = getch();
	// If there's no input, ch will be ERR
	if (ch != ERR) {
		// Handle user input
		switch (ch) {
			case KEY_RIGHT:
				// check if the bottom bar is moving out of the window’s boundaries
				if (bottom_bar->body[bottom_bar->length - 1].x >= getmaxx(window) - 2) {
					break;
				}
				// erase one block to make it seem moving
				mvwaddch(window, bottom_bar->body[0].y, bottom_bar->body[0].x, ' ');
				// move the entire bar right
				for (unsigned char i = 0; i < bottom_bar->length; i++) {
					bottom_bar->body[i].x++;
				}
				break;
			case KEY_LEFT:
				// check if the bottom bar is moving out of the window’s boundaries
				if (bottom_bar->body[0].x <= 1) {
					break;
				}
				// erase one block to make it seem moving
				mvwaddch(window, bottom_bar->body[bottom_bar->length - 1].y, bottom_bar->body[bottom_bar->length - 1].x, ' ');
				// move the entire bar left
				for (unsigned char i = 0; i < bottom_bar->length; i++) {
					bottom_bar->body[i].x--;
				}
				break;
			default:
				break;
		}
	}
	display_bottom_bar(window, bottom_bar);
}

void game_loop(WINDOW* window) {
	unsigned char current_level = 1;
	unsigned char level_over = 0;
	Bar *bottom_bar = generate_bottom_bar(window);
	display_bottom_bar(window, bottom_bar);

	while (1) {
		current_level++;
		construct_level(window, current_level);
		monitor_level(window, bottom_bar, current_level);
	}
	// Clean up and close
	endwin();
}
