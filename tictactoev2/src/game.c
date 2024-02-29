#include "game.h"
#include "utils.h"

void game_loop() {
	ALLEGRO_DISPLAY *display = initialize_display();
	ALLEGRO_BITMAP *bitmap = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_install_mouse();

	while(1) {
		Game *new_game = start_game();
		if (new_game == NULL) {
			continue;
		}
		monitor_game(display, bitmap, event_queue, new_game);
		destroy_game(new_game);
	}
	destroy_all(event_queue, display, bitmap);
}

Game *start_game() {
	Game *game = malloc(sizeof(Game));
	if (game == NULL) {
		return NULL;
	}
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

ALLEGRO_MOUSE_EVENT get_mouse_click_event(ALLEGRO_EVENT_QUEUE *event_queue) {
	ALLEGRO_EVENT ev;
	al_register_event_source(event_queue, al_get_mouse_event_source());
	while (1) {
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			return ev.mouse;
		}
	}
}

// return 1 if out ouf bounds and 0 otherwise
unsigned char check_click_out_of_bounds(ALLEGRO_DISPLAY *display, ALLEGRO_MOUSE_EVENT click_event) {
	if (click_event.x > START_X && click_event.x < END_X && click_event.y > START_Y && click_event.y < END_Y) {
		return 0;
	}
	return 1;
}

Cell get_cell_from_click_event(ALLEGRO_DISPLAY *display, ALLEGRO_MOUSE_EVENT click_event) {
	Cell cell = { 255, 255 };
	
	// check if click is out of bounds
	if (check_click_out_of_bounds(display, click_event) == 1) {
		return cell;
	}
	
	// get the row first - depends on the y coordinate
	unsigned char row = ((click_event.y - START_Y) / CELL_HEIGHT);
	unsigned char col = ((click_event.x - START_X) / CELL_WIDTH);
	cell = (Cell) { row, col };

	return cell;
}

void monitor_game(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, ALLEGRO_EVENT_QUEUE *event_queue, Game *game) {
	draw_board(display, bitmap);
	ALLEGRO_MOUSE_EVENT click_event;
	while(1) {
		click_event = get_mouse_click_event(event_queue);
		unsigned short mouse_click_x = click_event.x; 
		unsigned short mouse_click_y = click_event.y;
		Cell clicked_cell = get_cell_from_click_event(display, click_event);
		printf("Time: %f, The mouse is at: (%d, %d)\n", click_event.timestamp, mouse_click_x, mouse_click_y);
		printf("Time: %f, The cell position is: (%d, %d)\n", click_event.timestamp, clicked_cell.row, clicked_cell.col );
		
		//draw_x(display, bitmap, 1, 1);
		//draw_x(display, bitmap, 0, 1);
		//draw_o(display, bitmap, 2, 2);
		/* if (check_winning_condition(game) == 1) {
			break;
		} */
	}
}

void draw_board(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap) {
	// set bitmap as the target for drawing
	al_set_target_bitmap(bitmap);

	// Clear the bitmap
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (unsigned char i = 0; i <= SQUARE_DIMENSION; i++) {
		// draw the horizontal lines
		al_draw_line(START_X, START_Y + i*CELL_HEIGHT, END_X, START_Y + i*CELL_HEIGHT, al_map_rgb(255, 255 ,0), 1);

		// draw the horizontal lines
		al_draw_line(START_X + i*CELL_WIDTH, START_Y, START_X + i*CELL_WIDTH, END_Y, al_map_rgb(255, 255 ,0), 1);
	}
	
	// Reset the target back to the display
	al_set_target_backbuffer(display);

	al_draw_bitmap(bitmap, 0, 0, 0);
	al_flip_display();
}

void draw_x(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap,unsigned char row, unsigned char col) {
	// set bitmap as the target for drawing
	al_set_target_bitmap(bitmap);

	// Calculate the size of each cell
	int width = al_get_display_width(display);
	int height = al_get_display_height(display);

	int start_x = width / 2 - SQUARE_DIMENSION * CELL_WIDTH;
	int start_y = height / 2 - SQUARE_DIMENSION * CELL_HEIGHT;

	int cell_start_x = start_x + col * CELL_WIDTH;
	int cell_start_y = start_y + row * CELL_HEIGHT;
	
	al_draw_line(cell_start_x, cell_start_y, cell_start_x + CELL_WIDTH, cell_start_y + CELL_HEIGHT, al_map_rgb(255, 255, 0), 1);
	al_draw_line(cell_start_x, cell_start_y + CELL_HEIGHT, cell_start_x + CELL_WIDTH, cell_start_y, al_map_rgb(255, 255, 0), 1);

	// Reset the target back to the display
	al_set_target_backbuffer(display);

	al_draw_bitmap(bitmap, 0, 0, 0);
	al_flip_display();
}

void draw_o(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, unsigned char row, unsigned char col) {
	// set bitmap as the target for drawing
	al_set_target_bitmap(bitmap);

	// Calculate the size of each cell
	int width = al_get_display_width(display);
	int height = al_get_display_height(display);

	int start_x = width / 2 - SQUARE_DIMENSION * CELL_WIDTH;
	int start_y = height / 2 - SQUARE_DIMENSION * CELL_HEIGHT;

	int cell_center_x = start_x + col * CELL_WIDTH + CELL_WIDTH / 2;
	int cell_center_y = start_y + row * CELL_HEIGHT + CELL_HEIGHT / 2;

	al_draw_circle(cell_center_x, cell_center_y, (CELL_HEIGHT / 2), al_map_rgb(255, 255, 0), 1);
	
	// Reset the target back to the display
	al_set_target_backbuffer(display);

	al_draw_bitmap(bitmap, 0, 0, 0);
	al_flip_display();
}

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
	unsigned char row_sum = 0;
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			row_sum += game->board[i][j];
		}
		if (row_sum == SQUARE_DIMENSION || row_sum == 0) {
			return 1;
		}
	}
	return 0;
}

unsigned char check_winning_condition_column(Game *game) {
	unsigned char col_sum = 0;
	for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
		for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
			col_sum += game->board[i][j];
		}
		if (col_sum == SQUARE_DIMENSION || col_sum == 0) {
			return 1;
		}
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

void destroy_game(Game *game) {
	free(game);
}

void destroy_all(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP *bitmap) {
	al_unregister_event_source(event_queue, al_get_mouse_event_source());
	al_destroy_display(display);
	al_destroy_bitmap(bitmap);
}
