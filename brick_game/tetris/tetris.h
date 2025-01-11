#ifndef TETRIS_H
#define TETRIS_H

#define WIDTH 10
#define HEIGHT 20
#define MAX_LEVEL 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum state {
  start,
  spawn,
  moving,
  shifting,
  attaching,
  game_over
} state;

typedef struct position {
    int x, y;
} position;

typedef enum tetris_type { I, L, J, O, S, T, Z } tetris_type;

typedef struct tetromino_map {
  tetris_type type;
  position states[4][4];
} tetromino_map;

typedef struct tetromino {
  tetris_type type;
  int orientation;
  position location;
  position state[4];
} tetromino;

typedef struct game {
  int score;
  int level;
  int** field;
  int cleared;
  tetromino* next;
  tetromino* current;
  state state;
} game;

game init_game(tetromino_map* blocks);
void check_lines_full(game* game);
void process_rotation(game* game, tetromino_map* blocks);
void move_right_or_left(game* game, int direction);
int move_block_down(game* game, tetromino_map* blocks);
int create_new_falling(game* game, tetromino_map* blocks);
void fill_current_from_next(game* game);
int** create_matrix(int rows, int columns);
void put_block(game* game, tetromino* block);
void remove_block(game* game, tetromino* block);

tetromino*  rotate_block_left(tetromino* block, tetromino_map* blocks);
tetromino* rotate_block_right(tetromino* block, tetromino_map* blocks);
int check_block_fits(game* game, tetromino* block);
void init_new_map_block(tetromino_map* blocks, int type);
tetromino_map* init_all_block_types();
void init_new_block(tetromino_map* blocks, int type, game* game);
void init_block_I(tetromino_map* tetris);
void init_block_L(tetromino_map* tetris);
void init_block_J(tetromino_map* tetris);
void init_block_O(tetromino_map* tetris);
void init_block_S(tetromino_map* tetris);
void init_block_T(tetromino_map* tetris);
void init_block_Z(tetromino_map* tetris);
void fill_block_matrix(tetromino_map* tetris, position states[4][4]);

#endif