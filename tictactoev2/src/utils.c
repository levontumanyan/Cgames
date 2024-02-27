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
