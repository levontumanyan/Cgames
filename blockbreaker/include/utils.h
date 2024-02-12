#ifndef UTILS_H
#define UTILS_H

#define WINDOW_HEIGHT 20
#define WINDOW_LENGTH 40

#include <ncurses.h>

WINDOW* initialize_screen();
unsigned char* get_random_coordinates(WINDOW* win);

#endif
