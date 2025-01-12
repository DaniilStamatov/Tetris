#include "renderer.h"

void init_colors() {
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_CYAN);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);  
  init_pair(3, COLOR_WHITE, COLOR_YELLOW); 
  init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(5, COLOR_WHITE, COLOR_GREEN);  
  init_pair(6, COLOR_WHITE, COLOR_RED);    
  init_pair(7, COLOR_WHITE, COLOR_BLUE);   
  init_pair(8, COLOR_WHITE, COLOR_WHITE);  
}

void print_field(game* g, WINDOW* win) {
  wclear(win);
  box(win, 0, 0);
  for (int i = 0; i < HEIGHT; i++) {
    wmove(win,i + 1, 1);
    for (int j = 0; j < WIDTH; j++) {
      if(g->field[i][j] == 0) {
        ADD_EMPTY(win);
      } else {
        ADD_BLOCK(win, g->field[i][j]);
      }
    }
  }
  wrefresh(win);
}

void display_score(WINDOW *win, game *game)
{
  wclear(win);
  wmove(win, 2, 0);
  wprintw(win, "SCORE:\n%d\n", game->score );
  wmove(win, 6, 0);
  wprintw(win, "LINES:\n%d\n", game->cleared);
  wmove(win, 10, 0);
  wprintw(win, "LEVEL:\n%d\n", game->level);
  wmove(win, 13, 0);
  wprintw(win, "NEXT:");
  wmove(win, 16, 0);
  wprintw(win, "HIGH SCORE:\n%d\n", game->high_score);
  wmove(win, 19, 0);
  for(int i = 0; i < 4; ++i) {
    wmove(win, 13 + game->next->state[i].y + 1, game->next->state[i].x * 2 + 1);
    ADD_BLOCK(win, game->next->type + 1);
  }


  wrefresh(win);
}

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  scrollok(stdscr, 1);
  curs_set(0);
  mouseinterval(1);
  keypad(stdscr, TRUE);
  init_colors();
}

void clear_ncurses() {
  wclear(stdscr);
  endwin();
}
  