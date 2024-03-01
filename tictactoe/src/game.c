#include "game.h"
#include "game_logic.h"
#include "utils.h"
#include "user_interface.h"

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
	for (unsigned char row = 0; row < SQUARE_DIMENSION; row++) {
		for (unsigned char col = 0; col < SQUARE_DIMENSION; col++) {
			game->board[row][col] = 2;
		}
	}
	return game;
}

void monitor_game(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, ALLEGRO_EVENT_QUEUE *event_queue, Game *game) {
	draw_board(display, bitmap);
	ALLEGRO_MOUSE_EVENT click_event;
	unsigned short mouse_click_x;
	unsigned short mouse_click_y;
	while(1) {
		click_event = get_mouse_click_event(event_queue);
		mouse_click_x = click_event.x; 
		mouse_click_y = click_event.y;
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

		printf("Check winning condition returned: %u\n", check_winning_condition(game));
		if (check_winning_condition(game) == 1) {
			printf("Winner is: player: %u\n", game->turn);
			//display_winner_banner(display);
			get_mouse_click_event(event_queue);
			break;
		}
		if (check_for_draw(game) == 1) {
			printf("Game ended in a draw...\n");
			//display_winner_banner(display);
			get_mouse_click_event(event_queue);
			break;
		}
		// Flip the turn
		game->turn ^= 1;
	}
}

void destroy_game(Game *game) {
	free(game);
}
