#include "game.h"
#include "level.h"

int main() {
	Game game;
	initialize_game(&game);

	while(game.game_is_running) {
		// show_main_menu();

		while(player_has_not_quit) {
			Level new_level = start_new_level(&game);

			while (new_level.level_is_running) {
				process_input();
				//update_game_state();
				//render_graphics();
			}
			
			check_level_results();
		}
	}

	cleanup_game();
}
