Level start_new_level(Game* game);

typedef struct Level {
	unsigned char car_lanes; // number of car lanes in this level
	unsigned char safe_lanes; // number of safe lanes in this level (minimum two)
	unsigned char time_limit; // amount of time to complete the level
	unsigned char level_is_running; // 0 means level over, 1 means level still running
} Level;
