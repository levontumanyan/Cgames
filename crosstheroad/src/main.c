#include "game.h"
#include "level.h"

#include <allegro5/allegro.h>

unsigned char main() {
	Game game;
	initialize_game(&game);

	while(game.game_is_running) {
		// show_main_menu();
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

	// cleanup_game();
	return 0;
}
