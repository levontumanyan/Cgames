#include "utils.h"

// Constants for the grid size
const int GRID_ROWS = 3;
const int GRID_COLS = 3;
const int CELL_SIZE = 5;

WINDOW* initialize_screen() {
	ALLEGRO_DISPLAY *display = NULL;

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(640, 480);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_rest(5.0);

	return display;
}

/* 
void get_mouse_event(WINDOW *win) {
	int c;
	MEVENT event;

	c = wgetch(win);
	switch(c)
	{	
		case KEY_MOUSE:
		if (getmouse(&event) == OK) {	
			// When the user clicks left mouse button
			if(event.bstate & BUTTON1_PRESSED)
			{	
				print_click(event.x, event.y);	
			}
		}
	}
} 
*/

void get_mouse_event(WINDOW *win) {
	int ch;
	MEVENT event;

	while ((ch = getch()) != 'q') {
		if (ch == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					mvprintw(0, 0, "Left-clicked at coordinates: (%d, %d)", event.x, event.y);
				} else if (event.bstate & BUTTON2_PRESSED) {
					mvprintw(0, 0, "Right-clicked at coordinates: (%d, %d)", event.x, event.y);
				} else if (event.bstate & BUTTON3_PRESSED) {
					mvprintw(0, 0, "Middle-clicked at coordinates: (%d, %d)", event.x, event.y);
				}
				refresh();
			}
		}
	}
}

void print_click(WINDOW *win, int x, int y) {
	// move(getmaxy(win) - 1, 0);
	// printw("Mouse clicked at x: %d, y: %d", x, y);
	mvwprintw(win, 1, 1, "Mouse clicked at x: %d, y: %d", x, y);
}

void draw_x(WINDOW *win, unsigned char row, unsigned char col, unsigned char START_X, unsigned char START_Y) {
	for (unsigned char i = 0; i <= GRID_COLS; i++) {
		mvwaddch(win, START_Y + CELL_SIZE*(row - 1) + i + 1, START_X + (col - 1)*CELL_SIZE + i, '\\');
	}

	for (unsigned char i = 0; i <= GRID_ROWS; i++) {
		mvwaddch(win, START_Y + CELL_SIZE*(row - 1) + i + 1, START_X - 2 + (col)*CELL_SIZE - i, '/');
	}
}

void draw_o(WINDOW *win, unsigned char row, unsigned char col, unsigned char START_X, unsigned char START_Y) {
	for (unsigned char i = 0; i <= GRID_COLS; i++) {
		mvwaddch(win, START_Y + CELL_SIZE*(row - 1) + i + 1, START_X + (col - 1)*CELL_SIZE, '[');
		mvwaddch(win, START_Y + CELL_SIZE*(row - 1) + i + 1, START_X - 2 + (col)*CELL_SIZE, ']');
	}
}

void draw_board(WINDOW *win) {
	unsigned char START_X = (getmaxx(win) - GRID_COLS * CELL_SIZE) / 2;
	unsigned char START_Y = (getmaxy(win) - GRID_ROWS * CELL_SIZE) / 2;

	for (unsigned char i = 0; i <= GRID_ROWS; i++) {
		wmove(win, START_Y + i*CELL_SIZE, START_X);
		whline(win, ACS_HLINE, CELL_SIZE*GRID_COLS);
	}

	for (unsigned char i = 1; i < CELL_SIZE*GRID_ROWS; i++) {
		for (unsigned char j = 0; j <= GRID_COLS; j++) {
			wmove(win, START_Y + i, START_X + j*CELL_SIZE - 1);
			whline(win, ACS_VLINE, 1);
		}
	}
	draw_x(win, 2, 2, START_X, START_Y);
	draw_o(win, 1, 1, START_X, START_Y);
	wrefresh(win);
}


