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
    int width = level->kol;
    char kar = (char) getc(file);

    int i = 0;
    int j = 0;

    /* eerste lijnen skippen */
    while (kar == '\n' || kar == '\r') {
        kar = (char) getc(file);
    }

    while (i < height) {
        j = 0;
        while (kar != '\n' && kar != '\r') {
            a[i][j] = kar;
            j++;
            kar = (char) getc(file);
        };
        fill_empty_places(a[i], width);
        kar = (char) getc(file);
        i++;
    }

}




void fill_empty_places(char *rij, int length) {
    for (int i = 0; i < length; i++) {
        if (rij[i] == '\0') {
            rij[i] = ' ';
        }
    }

}


/* Leest het aantal kolommen en rijen in een bestand */
void rows_cols_read(FILE *file, int *rows, int *cols) {
    char c = 'a';
    int max_col = 0;
    int rowsize = 0;
    int kol = 0;

    /*bijhouden van rijen die misschien in het midden liggen*/
    int stack = 0;

    if (file) {
        while (c != EOF) {
            c = (char) getc(file);
            /* eerste regels */
            while (c == '\n' || c == '\r') {
                c = (char) getc(file);
            }

            while (c != EOF) {
                rowsize += stack;
                stack = 0;
                kol++;
                if (c == '\n' || c == '\r') {
                    /*newline is ingelezen*/
                    kol--;
                    if (kol != 0) {
                        rowsize++;
                        max_col = kol > max_col ? kol : max_col;
                        kol = 0;
                    } else {
                        stack++;
                    }
                }
                c = (char) getc(file);
            }
            if (kol != 0) {
                rowsize++;
            }
        }
    }
    *rows = rowsize;
    *cols = max_col;
}
