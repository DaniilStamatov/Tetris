#ifndef TETRIS_H
#define TETRIS_H

#define WIDTH 10
#define HEIGHT 20
#define MAX_LEVEL 10
#define GAME_SPEED 500
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include <time.h>
typedef enum state {
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAME_OVER,
  PAUSE
} state;

typedef struct position {
    int x, y;
} position;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction;

typedef enum TetrisType { I, L, J, O, S, T, Z } TetrisType;

typedef struct TetrominoMap {
  TetrisType type;
  position states[4][4];
} TetrominoMap;

typedef struct Tetromino {
  TetrisType type;
  int orientation;
  position location;
  position state[4];
} Tetromino;

typedef struct game {
  int is_playing;
  int high_score;
  int score;
  int level;
  long long time;
  int gravity_time;
  int speed;
  int** field;
  int cleared;
  Tetromino* next;
  Tetromino* current;
  state state;
} game;


game init_game(TetrominoMap* blocks);
void check_lines_full(game* game);
void process_rotation(game* game, TetrominoMap* blocks);
void move_right_or_left(game* game, int direction);
void move_block_down(game* game, TetrominoMap* blocks);
int create_new_falling(game* game, TetrominoMap* blocks);
void fill_current_from_next(game* game);
int** create_matrix(int rows, int columns);
void put_block(game* game, Tetromino* block);
void remove_block(game* game, Tetromino* block);
void state_machine(game* game, UserAction action, TetrominoMap* blocks);
void move_figure(game *game, UserAction action, TetrominoMap* blocks);
void finish_game(game* game, TetrominoMap* blocks);
void move_to_bottom(game* game, TetrominoMap* blocks);
void process_input(UserAction* action, int c);
int timer(game *gs, int delay);
long long get_time();

Tetromino*  rotate_block_left(Tetromino* block, TetrominoMap* blocks);
Tetromino* rotate_block_right(Tetromino* block, TetrominoMap* blocks);
int check_block_fits(game* game, Tetromino* block);
void init_new_map_block(TetrominoMap* blocks, int type);
TetrominoMap* init_all_block_types();
void init_new_block(TetrominoMap* blocks, int type, game* game);
void init_block_I(TetrominoMap* tetris);
void init_block_L(TetrominoMap* tetris);
void init_block_J(TetrominoMap* tetris);
void init_block_O(TetrominoMap* tetris);
void init_block_S(TetrominoMap* tetris);
void init_block_T(TetrominoMap* tetris);
void init_block_Z(TetrominoMap* tetris);
void fill_block_matrix(TetrominoMap* tetris, position states[4][4]);

#endif