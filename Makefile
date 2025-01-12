CC = gcc
CFLAGS = -Wall -Wextra -lm

# Определяем целевой исполняемый файл
TARGET = tetris.exe

# Определяем исходные файлы
SRCS = game.c brick_game/tetris/tetris.c gui/cli/renderer.c # Добавьте сюда все ваши исходные файлы
OBJS = $(SRCS:.c=.o)

# Правило по умолчанию
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lncurses -lm

%.o: %.c
	$(CC) $(CFLAGS)   -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean