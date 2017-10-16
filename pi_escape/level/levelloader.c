#include "levelloader.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


void read_level(Level *pLevel, FILE *file);

/*Krijgt een pointer mee naar een level, de rijen, kolommen en het levelnr worden toegevoegd*/
void level_init(Level *level, int width, int height, int nr) {
    level->kol = width;
    level->rij = height;
    level->nr = nr;
    level->spel = init_array_of_size(width, height);
}

char **init_array_of_size(int width, int height) {
    char **a;
    int i;

    a = (char **) calloc(height, sizeof(char *));
    for (i = 0; i < height; i++) {
        a[i] = (char *) calloc(width, sizeof(char));
    }

    return a;
}

Level *level_alloc(int width, int height, int nr) {
    Level *res = malloc(sizeof(Level));
    level_init(res, width, height, nr);
    return res;
}

void levelloader_free_level(Level *l) {
    free(l->spel);
}


LevelLoader *levelloader_alloc() {
    LevelLoader *res = malloc(sizeof(LevelLoader));
    return res;
}

void levelloader_free(LevelLoader *ll) {
    //TODO
}


Level *levelloader_load_level(LevelLoader *ll, int level_nr) {
    int *rows = 0;
    int *cols = 0;
    FILE *file = fopen("game1.lvl", "r");

    /* inlezen hoeveel rijen en kolommen moeten wroden vrijgemaakt */
    rows_cols_read(file, rows, cols);

    Level *level = level_alloc(*rows, *cols, level_nr);

    read_level(level, file);

    //TODO

    return level;
}

void read_level(Level *level, FILE *file) {
    char **a = level->spel;
    int height = level->rij;
    int widht = level->kol;

}


/* Leest het aantal kolommen en rijen in een bestand */
void rows_cols_read(FILE *file, int *rows, int *cols) {
    char c = 'a';
    int max_col = 0;
    int rowsize = 0;
    if (file) {
        int kol = 0;
        while (c != EOF) {
            c = (char) getc(file);
            if (c == '\r') {
                getc(file);
            } else if (c == '\n') {
                max_col = max_col > kol ? max_col : kol;
                rowsize++;
                kol = 0;
            } else {
                kol++;
            }
        }
    }
    /*eerste lijn mag niet ingelezen worden*/
    *rows = rowsize - 1;
    *cols = max_col;
}
