#include <allegro5/allegro.h>

#include "game.h"
#include "level.h"
#include "render.h"

unsigned char main() {
	Game game;
	ALLEGRO_DISPLAY *display = NULL;

	initialize_game(&game);
	initialize_display(display);

	while(game.game_is_running) {
		ALLEGRO_BITMAP *main_menu = NULL;

		draw_main_menu(main_menu);
		//show_main_menu();
		// below should go into show main menu
		unsigned char menu_not_active = 0;

		while(menu_not_active) {
			Level new_level;
			start_new_level(&game, &new_level);

			while (new_level.level_is_running) {
				//process_input();
				//update_game_state();
				//render_graphics();
			}

			// check_level_results();
		}
	}

	cleanup_game(display);
	return 0;
}
