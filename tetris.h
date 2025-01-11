#define WIDTH 10
#define HEIGHT 20
#define MAX_LEVEL 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

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
  int** field;
  int cleared;
  tetromino* next;
  tetromino* current;
} game;

tetromino*  rotate_block_left(tetromino* block, tetromino_map* blocks);
tetromino* rotate_block_right(tetromino* block, tetromino_map* blocks);
int check_block_fits(game* game, tetromino* block);
void init_new_map_block(tetromino_map* blocks, int type);
tetromino* init_new_block(tetromino_map* blocks, int type);
void init_block_I(tetromino_map* tetris);
void init_block_L(tetromino_map* tetris);
void init_block_J(tetromino_map* tetris);
void init_block_O(tetromino_map* tetris);
void init_block_S(tetromino_map* tetris);
void init_block_T(tetromino_map* tetris);
void init_block_Z(tetromino_map* tetris);
void fill_block_matrix(tetromino_map* tetris, position states[4][4]);
void check_lines_full(game* game);
