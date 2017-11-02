#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#define TO_IMPLEMENT_STRUCT char c

#include "../../libraries/glmc/include/glmc.h"
#include <stdio.h>
#include "../es/game_util.h"

typedef enum ItemType {
    KEY
} ItemType;
typedef enum ItemColor {
    O, A, B, C
} ItemColor;

typedef struct Level {
    char **spel;
    int width;
    int height;
    int nr;
} Level;

typedef struct LevelLoader {
    char *file;
} LevelLoader;


LevelLoader *levelloader_alloc();


char* create_level_name(int new_level_number);

Level *load_level(int level_nr);

void rows_cols_read(char* level_name, int *rows, int *cols);

char **init_array_of_size(int width, int height);

void fill_empty_places(char *string, int lenght);

void level_init(Level *level, int width, int height, int nr);

void read_level(Level *level, char* level_name);

#endif //LEVELLOADER_H
