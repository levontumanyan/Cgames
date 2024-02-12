#include "game.h"
#include "utils.h"

#define NUM_OF_BLOCKS(x) ((x) + 3)

unsigned char game_area[WINDOW_LENGTH][WINDOW_HEIGHT];

void initialize_game() {
	// Seed the random number generator
	srand(time(NULL));
	WINDOW *win = initialize_screen();
	game_loop(win);
}

Ball *generate_ball(WINDOW *window) {
	Ball *ball = malloc(sizeof(Ball));
	ball->body.x = getmaxx(window)/2 - 2;
	ball->body.y = getmaxy(window) - 5;
	ball->direction = 0;
	return ball;
}

void display_ball(WINDOW *window, Ball *ball) {
	mvwaddch(window, ball->body.y, ball->body.x, 'O');
	wrefresh(window);
}

void move_ball(WINDOW *window, Ball *ball) {
	switch (ball->direction) {
		// up direction
		case 0:
			if (ball->body.y <= 1) {
				ball->direction = 1;
				break;
			}
			mvwaddch(window, ball->body.y, ball->body.x, ' ');	
			ball->body.y--;
			display_ball(window, ball);
			break;
		// down direction
		case 1:
			mvwaddch(window, ball->body.y, ball->body.x, ' ');	
			ball->body.y++;
			display_ball(window, ball);
			break;
		default:
			break;
	}
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
	unsigned char* coordinates;
	do {
		coordinates = get_random_coordinates(window);
	} while (is_overlap(coordinates, block->length));
	for (unsigned char i = 0; i < block->length; i++) {
		block->body[i].x = coordinates[0] + i;
		block->body[i].y = coordinates[1];
		game_area[block->body[i].x][block->body[i].y] = 1;  // Mark this coordinate as occupied
	}
	return block;
}

void check_for_collision(Ball *ball) {


}

unsigned char is_overlap(unsigned char* coordinates, unsigned char length) {
	for (unsigned char i = 0; i < length; i++) {
		if (game_area[coordinates[0] + i][coordinates[1]] == 1) {
			return 1;  // There is an overlap
		}
	}
	return 0;  // No overlap
}

void display_block(WINDOW *window, Block *block) {
	// Display the block
	for (unsigned char i = 0; i < block->length; i++) {
		mvwaddch(window, block->body[i].y, block->body[i].x, ACS_CKBOARD);
	}
	wrefresh(window);
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

pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	pthread_mutex_lock(&ncurses_mutex);
	display_bottom_bar(window, bottom_bar);
	pthread_mutex_unlock(&ncurses_mutex);
}

void *handle_user_input_thread(void *args) {
	// Unpack the arguments
	struct handle_user_input_thread_args *targs = (struct handle_user_input_thread_args *)args;
	WINDOW *window = targs->window;
	Bar *bottom_bar = targs->bottom_bar;

	while (1) {
		handle_user_input(window, bottom_bar);
	}
	return NULL;
}

void monitor_level(WINDOW *window, Bar *bottom_bar, unsigned char level, Ball *ball) {
	unsigned char blocks_left = NUM_OF_BLOCKS(level);

	// Create a struct to hold the arguments for the new thread
	struct handle_user_input_thread_args targs;
	targs.window = window;
	targs.bottom_bar = bottom_bar;

	// Create the new thread
	pthread_t input_thread;
	pthread_create(&input_thread, NULL, handle_user_input_thread, &targs);

	while (blocks_left > 0) {
		pthread_mutex_lock(&ncurses_mutex);
		move_ball(window, ball);
		pthread_mutex_unlock(&ncurses_mutex);
		usleep(300000);
	}
}

void game_loop(WINDOW* window) {
	unsigned char current_level = 1;
	unsigned char level_over = 0;
	Bar *bottom_bar = generate_bottom_bar(window);
	display_bottom_bar(window, bottom_bar);
	Ball *ball = generate_ball(window);
	display_ball(window, ball);

	while (1) {
		construct_level(window, current_level);
		monitor_level(window, bottom_bar, current_level, ball);
		current_level++;
	}
	// Clean up and close
	endwin();
}
