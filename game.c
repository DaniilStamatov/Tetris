#include "brick_game/tetris/tetris.h"
#include "gui/cli/renderer.h"


int main() {
  init_ncurses();
  srand(get_time());
  WINDOW*  win = newwin(HEIGHT + 2 ,2 *  WIDTH + 2, 0,0);
  WINDOW*  score = newwin(HEIGHT + 2 ,WIDTH + 2, 0, 2 *  WIDTH + 4);
  TetrominoMap* blocks = init_all_block_types();
  game game = init_game(blocks);
  UserAction action = -1;
  while (game.is_playing) {
    game.level = game.score / 600 + 1;
    if(game.level > 10) game.level = 10;
    print_field(&game, win);
    display_score(score, &game);
    int c = getch();
    timeout(100);
    process_input(&action, c);
    state_machine(&game, action, blocks);
    action = -1;
  }
  clear_ncurses();
  delwin(win);
  delwin(score);
  return 0;
}