#include "game.h"

void initialize_game(Game* game) {
	game->game_is_running = 1;
	game->current_level = 1;
}

/* void show_main_menu() {
	// Get user input
	char user_input = get_user_input();

	// Check user input
	if (user_input == '1') {
		start_new_game();
	} else if (user_input == '2') {
		load_saved_game();
	} else if (user_input == '3') {
		show_options_screen();
	} else if (user_input == '4') {
		game_is_running = 0;
	}
} */

unsigned char get_user_input() {

}
