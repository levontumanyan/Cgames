#include "game.h"
#include "game_logic.h"

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
	game->turn = random_zero_or_one();

	// fill up the game board with 2s each time a user clicks on a box that cell's value in the board will become either 0 or 1. 0 for O, 1 for X
	for (unsigned char i = 0; i < SQUARE_DIMENSION; i++) {
		for (unsigned char j = 0; j < SQUARE_DIMENSION; j++) {
			game->board[i][j] = 2;
		}
	}
	return game;
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
		
		// here check if the cell is already filled up and don't draw over it
		if (game->board[clicked_cell.row][clicked_cell.col] != 2) {
			continue;
		}
		// this checks is to ignore the out of bounds clicks
		if (clicked_cell.row == 255 && clicked_cell.col == 255) {
			continue;
		}
		
		printf("Time: %f, The mouse is at: (%d, %d)\n", click_event.timestamp, mouse_click_x, mouse_click_y);
		printf("Time: %f, The cell position is: (%d, %d)\n", click_event.timestamp, clicked_cell.row, clicked_cell.col );

		// depending on whose turn it is take the click and draw corresponding symbol
		// check if that cell is already filled, if so do nothing
		if (game->turn == 0) {
			game->board[clicked_cell.row][clicked_cell.col] = 0;
			draw_o(display, bitmap, clicked_cell.row, clicked_cell.col);
		}
		else if (game->turn == 1) {
			game->board[clicked_cell.row][clicked_cell.col] = 1;
			draw_x(display, bitmap, clicked_cell.row, clicked_cell.col);
		}
		printf("Check winning condition row returned: %c\n", check_winning_condition_row(game));
		//printf("Check winning condition column returned: %c", check_winning_condition_column(game));
		//printf("Check winning condition diagonal returned: %c", check_winning_condition(game));
		/* if (check_winning_condition(game) == 1) {
			printf("Winner is: player: %c", game->turn);
			break;
		} */
		// Flip the turn
		game->turn ^= 1;
	}
}

void destroy_game(Game *game) {
	free(game);
}
