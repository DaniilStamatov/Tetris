#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"
#define ADD_BLOCK(w,x) waddch((w),' '|COLOR_PAIR(x));     \
                       waddch((w),' '|COLOR_PAIR(x))
#define ADD_EMPTY(w) waddch((w), ' '|COLOR_PAIR(0)); waddch((w), ' '|COLOR_PAIR(0))

void init_colors();
void print_field(game* g, WINDOW* win);
void display_score(WINDOW *win, game *game);
void init_ncurses();
void clear_ncurses();

#endif