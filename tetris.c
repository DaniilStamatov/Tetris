#include "tetris.h"
#define ADD_BLOCK(w,x) waddch((w),' '|COLOR_PAIR(x));     \
                       waddch((w),' '|COLOR_PAIR(x))
#define ADD_EMPTY(w) waddch((w), ' '|COLOR_PAIR(0)); waddch((w), ' '|COLOR_PAIR(0))

tetromino_map* init_all_block_types() {
  tetromino_map* blocks = malloc(7 * sizeof(tetromino_map));
  for (int i = 0; i < 7; i++) {
    init_new_map_block(&blocks[i], i);
  }
  return blocks;
}

tetromino* init_new_block(tetromino_map* blocks, int type) {
  tetromino* block = malloc(sizeof(tetromino));
  block->type = type;
  int rotation = rand() % 4;
  block->orientation = rotation;
  for (int i = 0; i < 4; i++) {
    block->state[i] = blocks[type].states[rotation][i];
  }
  return block;
}

tetromino* rotate_block_left(tetromino* block, tetromino_map* blocks) {
  tetromino* new_block = malloc(sizeof(tetromino));
  new_block->type = block->type;
  int new_orientation = (block->orientation + 1) % 4;
  for (int i = 0; i < 4; i++) {
    new_block->state[i] = blocks[block->type].states[new_orientation][i];
  }
  new_block->orientation = new_orientation;
  new_block->location = block->location;
  return new_block;
}

tetromino* rotate_block_right(tetromino* block, tetromino_map* blocks) {
  tetromino* new_block = malloc(sizeof(tetromino));
  new_block->type = block->type;
  int new_orientation = (block->orientation + 3) % 4;
  for (int i = 0; i < 4; i++) {
    new_block->state[i] = blocks[block->type].states[new_orientation][i];
  }
  new_block->orientation = new_orientation;
  new_block->location = block->location;
  return new_block;
}

void init_new_map_block(tetromino_map* blocks, int type) {
  if (type == I) {
    init_block_I(blocks);
  } else if (type == L) {
    init_block_L(blocks);
  } else if (type == J) {
    init_block_J(blocks);
  } else if (type == O) {
    init_block_O(blocks);
  } else if (type == S) {
    init_block_S(blocks);
  } else if (type == T) {
    init_block_T(blocks);
  } else if (type == Z) {
    init_block_Z(blocks);
  }
}

void init_block_I(tetromino_map* tetris) {
  position states[4][4] = {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
                           {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
                           {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
                           {{0, 1}, {1, 1}, {2, 1}, {3, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_L(tetromino_map* tetris) {
  position states[4][4] = {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
                           {{0, 0}, {0, 1}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_J(tetromino_map* tetris) {
  position states[4][4] = {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
                           {{0, 1}, {1, 1}, {2, 0}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_O(tetromino_map* tetris) {
  position states[4][4] = {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}}};
  fill_block_matrix(tetris, states);
}

void init_block_S(tetromino_map* tetris) {
  position states[4][4] = {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
                           {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
                           {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
                           {{0, 0}, {1, 0}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_T(tetromino_map* tetris) {
  position states[4][4] = {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
                           {{0, 1}, {1, 0}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_Z(tetromino_map* tetris) {
  position states[4][4] = {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                           {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
                           {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
                           {{0, 1}, {1, 0}, {1, 1}, {2, 0}}};
  fill_block_matrix(tetris, states);
}

void set_cell(game* game, int row, int col, int value) {
  game->field[row][col] = value;
}

void remove_block(game* game, tetromino* block) {
  for (int i = 0; i < 4; i++) {
    int row = block->location.y + block->state[i].y;
    int col = block->location.x + block->state[i].x;

    set_cell(game, row, col, 0);
  }
}

int is_in_range(int row, int column) {
  return 0 <= row && row < HEIGHT && 0 <= column && column < WIDTH;
}

int check_block_fits(game* game, tetromino* block) {
  int result = 1;
  for (int i = 0; i < 4; ++i) {
    int column = block->location.x + block->state[i].x;
    int row = block->location.y + block->state[i].y;

    if (!is_in_range(row, column) || game->field[row][column] != 0) {
      result = 0;
    }
  }
  return result;
}

void fill_block_matrix(tetromino_map* tetris, position states[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris->states[i][j] = states[i][j];
    }
  }
}

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

void put_block(game* game, tetromino* block) {
  for (int i = 0; i < 4; ++i) {
    int x = block->location.x + block->state[i].x;
    int y = block->location.y + block->state[i].y;
    game->field[y][x] = block->type + 1;
  }
}

int** create_matrix(int rows, int columns) {
  int** matrix = (int**)calloc(rows, sizeof(int*));
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)calloc(columns, sizeof(int));
  }
  return matrix;
}

void fill_current_from_next(game* game) {
  tetromino* temp = game->next;
  game->current->orientation = temp->orientation;
  game->current->type = temp->type;
  for(int i = 0; i < 4; ++i) {
    game->current->state[i] = temp->state[i];
  }
}

int create_new_falling(game* game, tetromino_map* blocks) {
  game->current = malloc(sizeof(tetromino));
  fill_current_from_next(game);
  game->current->location = (position){3, 0};
  game->next = init_new_block(blocks, rand() % 7);
  return check_block_fits(game, game->current);
}

int move_block_down(game* game, tetromino_map* blocks) {
  remove_block(game, game->current);
  game->current->location.y++;
  int result = 1;
  if (check_block_fits(game, game->current)) {
  } else {
    game->current->location.y--;
    put_block(game, game->current);
    check_lines_full(game);
    free(game->current);
    result = create_new_falling(game, blocks);
  }
  put_block(game, game->current);
  return result;
}

void move_right_or_left(game* game, int direction) {
  remove_block(game, game->current);
  if (direction == 1) {
    game->current->location.x += 1;
    if (!check_block_fits(game, game->current)) {
      game->current->location.x -= 1;
    }
  } else if (direction == -1) {
    game->current->location.x -= 1;
    if (!check_block_fits(game, game->current)) {
      game->current->location.x += 1;
    }
  }
  put_block(game, game->current);
}

void process_rotation(game* game, tetromino_map* blocks) {
  remove_block(game, game->current);
  tetromino* temp = rotate_block_right(game->current, blocks);
  if (check_block_fits(game, temp)) {
    game->current = temp;
  } else { 
    free(temp);
  }
  put_block(game, game->current);
}

void check_lines_full(game* game) {
  int full_line_count = 0;
  for (int i = 0; i < HEIGHT; ++i) {
    int full_line = 1;
    for (int j = 0; j < WIDTH; ++j) {
      if (game->field[i][j] == 0) {
        full_line = 0;
      }
    }

    if (full_line) {
      full_line_count += 1;
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < WIDTH; j++) {
          game->field[k][j] = game->field[k - 1][j];
        }
      }
      for (int j = 0; j < WIDTH; j++) {
        game->field[0][j] = 0;
      }
      game->cleared += 1;
      i--;
    }
  }
  if(full_line_count == 1) {
    game->score += 100;
  } else if (full_line_count == 2) {
    game->score += 300;
  } else if (full_line_count == 3) {
    game->score += 500;
  } else if (full_line_count == 4) {
    game->score += 700;
  }
}

void display_score(WINDOW *win, game *game, tetromino_map* blocks)
{
  wclear(win);
  wmove(win, 2, 0);
  wprintw(win, "Score\n%d\n", game->score);
  wmove(win, 6, 0);
  wprintw(win, "Lines\n%d\n", game->cleared);
  wmove(win, 10, 0);

  for(int i = 0; i < 4; ++i) {
    wmove(win, 10 + game->next->state[i].x + 1, game->next->state[i].y * 2 + 1);
    ADD_BLOCK(win, game->next->type + 1);
  }
  wrefresh(win);
}

int main() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  srand(time(NULL));
  init_colors();
  WINDOW*  win = newwin(HEIGHT + 2 ,2 *  WIDTH + 2, 0,0);
  WINDOW*  score = newwin(HEIGHT + 2 ,WIDTH + 2, 0, 2 *  WIDTH + 4);
  tetromino_map* blocks = init_all_block_types();
  game* game = malloc(sizeof(game));
  game->cleared = 0;
  game->current = malloc(sizeof(tetromino));
  game->field = create_matrix(HEIGHT, WIDTH);
  game->next = init_new_block(blocks, rand() % 7);
  create_new_falling(game, blocks);
  put_block(game, game->current);
 // print_field(game, win);
  while (1) {
    int ch = getch();
    if (ch == KEY_LEFT) {
      move_right_or_left(game, -1);
    } else if (ch == KEY_RIGHT) {
      move_right_or_left(game, 1);
    } else if (ch == ' ') {
      process_rotation(game, blocks);
    } else if (ch == 'q') {
      break;
    }
    if(!move_block_down(game, blocks)) {
      put_block(game, game->current);
      break;
    }
    print_field(game, win);
    display_score(score, game, blocks);
  }
  getch();
  endwin();
  for (int i = 0; i < HEIGHT; ++i) {
    free(game->field[i]);
  }
  free(game->field);
  free(game->current);
  free(game);
  free(blocks);
  return 0;
}