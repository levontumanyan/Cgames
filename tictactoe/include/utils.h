#ifndef UTILS_H
#define UTILS_H

#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024

ALLEGRO_DISPLAY* initialize_display();
unsigned char random_zero_or_one();
void destroy_all(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP *bitmap);

#endif
