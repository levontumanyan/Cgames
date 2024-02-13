#ifndef UTILS_H
#define UTILS_H

#define WINDOW_HEIGHT 20
#define WINDOW_LENGTH 40

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "game.h"

WINDOW* initialize_screen();
Coordinate get_random_coordinates(WINDOW* win);

#endif
