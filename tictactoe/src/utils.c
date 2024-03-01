#include "utils.h"

ALLEGRO_DISPLAY* initialize_display() {
	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return NULL;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return NULL;
	}

	al_clear_to_color(al_map_rgb(0,0,0));

	return display;
}

unsigned char random_zero_or_one() {
	srand(time(0)); // Use current time as seed for random generator
	return rand() % 2; // Modulo operation to get either 0 or 1
}

void destroy_all(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP *bitmap) {
	al_unregister_event_source(event_queue, al_get_mouse_event_source());
	al_destroy_display(display);
	al_destroy_bitmap(bitmap);
}
