#include <malloc.h>
#include <string.h>
#include "levelloadertester.h"

int test_game1() {
    return test_file("pi_escape/level/level_files/game1.lvl", 11, 8);
}

int test_game2() {
    return test_file("pi_escape/level/level_files/game2.lvl", 10, 13);
}

int test_game3() {
    return test_file("pi_escape/level/level_files/game3.lvl", 13, 14);
}

int test_tutorial1() {
    return test_file("pi_escape/level/level_files/tutorial1.lvl", 7, 3);
}

int test_tutorial2() {
    return test_file("pi_escape/level/level_files/tutorial2.lvl", 7, 7);
}

int test_tutorial3() {
    return test_file("pi_escape/level/level_files/tutorial3.lvl", 9, 8);
}

int test_tutorial4() {
    return test_file("pi_escape/level/level_files/tutorial4.lvl", 9, 8);
}

int test_tutorial5() {
    return test_file("pi_escape/level/level_files/tutorial5.lvl", 9, 8);
}

int test_tutorial6() {
    return test_file("pi_escape/level/level_files/tutorial6.lvl", 9, 8);
}

int test_tutorial7() {
    return test_file("pi_escape/level/level_files/tutorial7.lvl", 9, 8);
}

int test_file(char *path, int nrows, int ncols) {
    LevelLoader *ll = malloc(sizeof(LevelLoader));
    ll->file = strdup(path);
    FILE *f;
    f = fopen(path, "r");
    int rows = 0;
    int cols = 0;
    rows_cols_read(ll, &rows, &cols);
    assert(rows == nrows);
    assert(cols == ncols);
    fclose(f);
    return 1;
}

int test_array() {
    LevelLoader *ll = malloc(sizeof(LevelLoader));
    ll->file = strdup("pi_escape/level/level_files/game1.lvl");
    FILE *f;
    f = fopen(ll->file, "r");
    struct Level *l = malloc(sizeof(Level));

    level_init(l, 11, 8, 1);

    read_level(l, ll);

    assert(l->spel[0][0] == ' ');

    return 1;
}

int test_complete() {
    LevelLoader *ll = malloc(sizeof(LevelLoader));

    ll->file = strdup("pi_escape/level/level_files/game1.lvl");

    Level *l = levelloader_load_level(ll, 1);

    assert(l->rij == 11);

    free(ll);
    return 1;
}