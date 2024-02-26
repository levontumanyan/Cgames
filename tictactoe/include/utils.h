#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <allegro5/allegro.h>

#include "game.h"

#define WINDOW_HEIGHT 30
#define WINDOW_LENGTH 50


WINDOW* initialize_screen();
void draw_board(WINDOW *win);
void draw_x(WINDOW *win, unsigned char row, unsigned char col, unsigned char START_X, unsigned char START_Y);

void print_click(WINDOW *win, int x, int y);
void get_mouse_event(WINDOW *win);

#endif
