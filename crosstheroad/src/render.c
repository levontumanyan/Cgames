#include <allegro5/allegro.h>

#include "render.h"

void initialize_display(ALLEGRO_DISPLAY *display) {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return;
	}

	al_clear_to_color(al_map_rgb(0,0,0));
}

void draw_main_menu(ALLEGRO_BITMAP *main_menu) {

}
