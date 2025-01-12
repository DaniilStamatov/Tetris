#include "tetris.h"

game init_game(TetrominoMap* blocks) {
  game game;
  game.state = START;
  game.is_playing = 1;
  game.cleared = 0;
  game.score = 0;
  game.level = 0;
  game.speed = GAME_SPEED;
  game.time = get_time();
  game.current = malloc(sizeof(Tetromino));
  game.field = create_matrix(HEIGHT, WIDTH);
  game.next = malloc(sizeof(Tetromino));
  init_new_block(blocks, rand() % 7, &game);
  FILE *file = fopen("high_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &game.high_score);
    fclose(file);
  }
  return game;
}

TetrominoMap* init_all_block_types() {
  TetrominoMap* blocks = malloc(7 * sizeof(TetrominoMap));
  for (int i = 0; i < 7; i++) {
    init_new_map_block(&blocks[i], i);
  }
  return blocks;
}

void init_new_block(TetrominoMap* blocks, int type, game* game) {
  game->next->type = type;
  int rotation = rand() % 4;
  game->next->orientation = rotation;
  for (int i = 0; i < 4; i++) {
    game->next->state[i] = blocks[type].states[rotation][i];
  }
}

Tetromino* rotate_block_left(Tetromino* block, TetrominoMap* blocks) {
  Tetromino* new_block = malloc(sizeof(Tetromino));
  new_block->type = block->type;
  int new_orientation = (block->orientation + 1) % 4;
  for (int i = 0; i < 4; i++) {
    new_block->state[i] = blocks[block->type].states[new_orientation][i];
  }
  new_block->orientation = new_orientation;
  new_block->location = block->location;
  return new_block;
}

Tetromino* rotate_block_right(Tetromino* block, TetrominoMap* blocks) {
  Tetromino* new_block = malloc(sizeof(Tetromino));
  new_block->type = block->type;
  int new_orientation = (block->orientation + 3) % 4;
  for (int i = 0; i < 4; i++) {
    new_block->state[i] = blocks[block->type].states[new_orientation][i];
  }
  new_block->orientation = new_orientation;
  new_block->location = block->location;
  return new_block;
}

void init_new_map_block(TetrominoMap* blocks, int type) {
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

void init_block_I(TetrominoMap* tetris) {
  position states[4][4] = {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
                           {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
                           {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
                           {{0, 1}, {1, 1}, {2, 1}, {3, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_L(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
                           {{0, 0}, {0, 1}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_J(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
                           {{0, 1}, {1, 1}, {2, 0}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_O(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
                           {{0, 1}, {0, 2}, {1, 1}, {1, 2}}};
  fill_block_matrix(tetris, states);
}

void init_block_S(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
                           {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
                           {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
                           {{0, 0}, {1, 0}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_T(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
                           {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
                           {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
                           {{0, 1}, {1, 0}, {1, 1}, {2, 1}}};
  fill_block_matrix(tetris, states);
}

void init_block_Z(TetrominoMap* tetris) {
  position states[4][4] = {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                           {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
                           {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
                           {{0, 1}, {1, 0}, {1, 1}, {2, 0}}};
  fill_block_matrix(tetris, states);
}

void set_cell(game* game, int row, int col, int value) {
  game->field[row][col] = value;
}

void remove_block(game* game, Tetromino* block) {
  for (int i = 0; i < 4; i++) {
    int row = block->location.y + block->state[i].y;
    int col = block->location.x + block->state[i].x;

    set_cell(game, row, col, 0);
  }
}

int is_in_range(int row, int column) {
  return 0 <= row && row < HEIGHT && 0 <= column && column < WIDTH;
}

int check_block_fits(game* game, Tetromino* block) {
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

void fill_block_matrix(TetrominoMap* tetris, position states[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris->states[i][j] = states[i][j];
    }
  }
}

void put_block(game* game, Tetromino* block) {
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
  Tetromino* temp = game->next;
  game->current->orientation = temp->orientation;
  game->current->type = temp->type;
  for(int i = 0; i < 4; ++i) {
    game->current->state[i] = temp->state[i];
  }
}

int create_new_falling(game* game, TetrominoMap* blocks) {
  if(game->current == NULL) {
    game->current = malloc(sizeof(Tetromino));
    game->current = NULL;
  }
  fill_current_from_next(game);
  game->current->location = (position){3, 0};
  init_new_block(blocks, rand() % 7, game);
  game->time = get_time();
  game->state = check_block_fits(game, game->current) ? MOVING : GAME_OVER;
}

void move_block_down(game* game, TetrominoMap* blocks) {
  remove_block(game, game->current);
  game->current->location.y++;
  if (check_block_fits(game, game->current)) {
    game->state = MOVING;
  } else {
    game->current->location.y--;
    check_lines_full(game);
    game->state = SPAWN;
  }
    put_block(game, game->current);

}

void move_right_or_left(game* game, int direction) {
  remove_block(game, game->current);
  game->current->location.x += direction;
  if (!check_block_fits(game, game->current)) {
    game->current->location.x -= direction;
  }
  put_block(game, game->current);
  game->state = MOVING;
}

void move_to_bottom(game* game, TetrominoMap* blocks) {
    remove_block(game, game->current);
    while(check_block_fits(game, game->current)) {
      game->current->location.y++;
    }
    game->current->location.y--;
    put_block(game, game->current);
    check_lines_full(game);
    game->state = SPAWN;
}

void process_rotation(game* game, TetrominoMap* blocks) {
  remove_block(game, game->current);
  Tetromino* temp = rotate_block_right(game->current, blocks);
  if (check_block_fits(game, temp)) {
    free(game->current);
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
  game->speed = GAME_SPEED * pow(0.8, game->level);  
}

void process_input(UserAction* action, int c) {
  if(c == 'r') {
    *action = Start;
  } else if(c == 'p') {
    *action = Pause;
  } else if(c == 'q') {
    *action = Terminate;
  } else if(c == KEY_LEFT) {
    *action = Left;
  } else if(c == KEY_RIGHT) {
    *action = Right;
  } else if(c == KEY_UP) {
    *action = Up;
  } else if(c == KEY_DOWN) {
    *action = Down;
  } else if(c == ' ') {
    *action = Action;
  }
}


long long get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts); // Получаем текущее время
    return (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000; // Возвращаем время в миллисекундах
}

int timer(game *game, int delay) {
    int result = 0;
    long long time = get_time();

    if (time - game->time >= delay) {
        game->time = time;
        result = 1;
    }

    return result;
}


void move_figure(game *game, UserAction action, TetrominoMap* blocks) {
  if(action == Terminate) {
    finish_game(game, blocks);
  } else if(action == Pause) {
    game->state = game->state == PAUSE ? MOVING : PAUSE;
  } else if(game->state != PAUSE) {
    if (action == Left)
      move_right_or_left(game, -1);
    else if (action == Right)
      move_right_or_left(game, 1);
    else if (action == Down)
      move_to_bottom(game, blocks);
    else if ((action == Action || action == Up))
      process_rotation(game, blocks);
  }
  
  if (timer(game, game->speed)) game->state = SHIFTING;
}

void state_machine(game* game, UserAction action, TetrominoMap* blocks) {
  if (game->state == START) {
    if (action == Terminate)
      finish_game(game, blocks);
    else if (action == Start)
      game->state = SPAWN;
  }
  if(game->state == SPAWN) {
    create_new_falling(game, blocks);
  } else if (game->state == SHIFTING) {
    move_block_down(game, blocks);
  } else if (game->state == MOVING) {
    move_figure(game, action, blocks);
  } else if (game->state == GAME_OVER) {
    finish_game(game, blocks);
  }
}

void finish_game(game* game, TetrominoMap* blocks) {
  if (game->score > game->high_score) {
    FILE *file = fopen("high_score.txt", "w");

    if (file) {
      fprintf(file, "%d", game->score);
      fclose(file);
    }
  }
  for (int i = 0; i < HEIGHT; ++i) {
    free(game->field[i]);
  }
  free(game->field);
  free(game->next);
  free(game->current);
  free(blocks);
  game->is_playing = 0;
}