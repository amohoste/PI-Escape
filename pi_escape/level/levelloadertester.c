#include <malloc.h>
#include <string.h>
#include "levelloadertester.h"

int test_filesdimensions() {
    assert(test_filedimensions(1, 11, 8) == 0);
    assert(test_filedimensions(2, 10, 13) == 0);
    assert(test_filedimensions(3, 13, 14) == 0);
    assert(test_filedimensions(4, 7, 3) == 0);
    assert(test_filedimensions(5, 7, 7) == 0);
    assert(test_filedimensions(6, 9, 8) == 0);
    assert(test_filedimensions(7, 9, 8) == 0);
    assert(test_filedimensions(8, 9, 8) == 0);
    assert(test_filedimensions(9, 9, 8) == 0);
    assert(test_filedimensions(10, 9, 8) == 0);
    return 1;
}

int test_filedimensions(int lvl, int nrows, int ncols) {
    LevelLoader *ll = levelloader_alloc();

    // Level aanmaken en inlezen
    Level *l = load_level(lvl);
    assert(l->width == ncols);
    assert(l->height == nrows);

    return 1;
}

int test_game1() {
    char arr[11][8] = {
            {' ', ' ', ' ', 'E', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'X', 'X', 'X', '#', 'X', 'X', 'X', 'X'},
            {' ', ' ', ' ', '.', ' ', ' ', 'a', ' '},
            {'C', '.', '.', '&', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', '.', '.', '.', 'B', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'X', 'X', '#', 'X', 'X', 'X', 'X', 'X'},
            {' ', ' ', '.', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', 'A', ' ', ' ', 'o', ' ', ' '},
            {' ', ' ', 'S', ' ', ' ', 'b', ' ', ' '}
    };


    // Levelloader aanmaken
    LevelLoader *ll = levelloader_alloc();
    ll->file = strdup("pi_escape/level/level_files/game1.lvl");

    // Level aanmaken en inlezen
    Level *l = load_level(1);

    assert(array_compare(l, arr, 11, 8) == 1);

    return 1;
}

int test_few() {

    // Levelloader aanmaken
    LevelLoader *ll = levelloader_alloc();
    ll->file = strdup("pi_escape/level/level_files/game1.lvl");

    // Level aanmaken en inlezen
    Level *l = load_level(1);

    assert(l->spel[0][0] == ' ');
    assert(l->spel[0][3] == 'E');

    return 1;
}

int array_compare(Level *a, char b[][8], int rij, int kol) {

    for (int i = 0; i < rij; i++) {
        for (int j = 0; j < kol; j++) {
            if (a->spel[i][j] != b[i][j]) return 0;
        }
    }

    return 1;
}