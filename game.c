#include "brick_game/tetris/tetris.h"
#include "gui/cli/renderer.h"


int main() {
  init_ncurses();
  srand(time(NULL));
  WINDOW*  win = newwin(HEIGHT + 2 ,2 *  WIDTH + 2, 0,0);
  WINDOW*  score = newwin(HEIGHT + 2 ,WIDTH + 2, 0, 2 *  WIDTH + 4);
  tetromino_map* blocks = init_all_block_types();
  game game = init_game(blocks);
  create_new_falling(&game, blocks);
  put_block(&game, game.current);
  while (1) {
    int ch = getch();
    if (ch == KEY_LEFT) {
      move_right_or_left(&game, -1);
    } else if (ch == KEY_RIGHT) {
      move_right_or_left(&game, 1);
    } else if (ch == ' ') {
      process_rotation(&game, blocks);
    } else if (ch == 'q') {
      break;
    }
    if(!move_block_down(&game, blocks)) {
      put_block(&game, game.current);
      break;
    }
    timeout(500 * pow(0.8, game.level));
    game.level = game.score / 600 + 1;
    if(game.level > 10) game.level = 10;
    print_field(&game, win);
    display_score(score, &game);
  }
  clear_ncurses();
  delwin(win);
  delwin(score);

  for (int i = 0; i < HEIGHT; ++i) {
    free(game.field[i]);
  }
  free(game.field);
  free(game.next);
  free(game.current);
  free(blocks);
 
  return 0;
}