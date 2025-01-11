#include "tetris.h"

tetromino_map* init_all_block_types() {
  tetromino_map* blocks = malloc(7 * sizeof(tetromino_map));
  for (int i = 0; i < 7; i++) {
    init_new_map_block(&blocks[i], i);
  }
  return blocks;
}

void init_new_block(tetromino_map* blocks, int type, game* game) {
  game->next->type = type;
  int rotation = rand() % 4;
  game->next->orientation = rotation;
  for (int i = 0; i < 4; i++) {
    game->next->state[i] = blocks[type].states[rotation][i];
  }
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
  if(game->current == NULL) {
    game->current = malloc(sizeof(tetromino));
    game->current = NULL;
  }
  fill_current_from_next(game);
  game->current->location = (position){3, 0};
  init_new_block(blocks, rand() % 7, game);
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

game init_game(tetromino_map* blocks) {
  game game;
  game.state = start;
  game.cleared = 0;
  game.score = 0;
  game.level = 0;
  game.current = malloc(sizeof(tetromino));
  game.field = create_matrix(HEIGHT, WIDTH);
  game.next = malloc(sizeof(tetromino));
  init_new_block(blocks, rand() % 7, &game);
  return game;
}

