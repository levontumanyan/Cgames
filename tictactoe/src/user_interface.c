#include "user_interface.h"

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
