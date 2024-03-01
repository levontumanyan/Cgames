#include "user_interface.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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

void draw_x(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap, unsigned char row, unsigned char col) {
	// set bitmap as the target for drawing
	al_set_target_bitmap(bitmap);

	int cell_start_x = START_X + col * CELL_WIDTH;
	int cell_start_y = START_Y + row * CELL_HEIGHT;
	
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

	int cell_center_x = START_X + col * CELL_WIDTH + CELL_WIDTH / 2;
	int cell_center_y = START_Y + row * CELL_HEIGHT + CELL_HEIGHT / 2;

	al_draw_circle(cell_center_x, cell_center_y, (CELL_HEIGHT / 2), al_map_rgb(255, 255, 0), 1);
	
	// Reset the target back to the display
	al_set_target_backbuffer(display);

	al_draw_bitmap(bitmap, 0, 0, 0);
	al_flip_display();
}

void display_winner_banner(ALLEGRO_DISPLAY *display){
	// required for the fonts
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *winner_font = al_load_font("fonts/NewYork.ttf", 24, 0);
	if (!winner_font) {
        printf("Error: Could not load font\n");
        return;
    }

	// dynamically determine the size of the text and create the bitmap accordingly
	char *winner_text = "Winner is you bitch";
	int bbx, bby, bbw, bbh;
	al_get_text_dimensions(winner_font, winner_text, &bbx, &bby, &bbw, &bbh);

	ALLEGRO_BITMAP *winner_text_bitmap = al_create_bitmap(bbw, bbh);

	// set bitmap as the target for drawing
	al_set_target_bitmap(winner_text_bitmap);

	ALLEGRO_COLOR yellow = al_map_rgb(255, 156, 0);
	// different approach here. Instead of drawing to the bitmap as the whole screen, we will draw into it as a separate entity then decide where on the screen to place it
	al_draw_text(winner_font, yellow, 0, 0, 0, winner_text);

	// Reset the target back to the display
	al_set_target_backbuffer(display);

	al_draw_bitmap(winner_text_bitmap, END_X + 50, END_Y + 50, 0);
	al_flip_display();
}
