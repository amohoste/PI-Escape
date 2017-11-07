#include <malloc.h>
#include <string.h>
#include "levelloadertester.h"

int test_filesdimensions() {
	// Tutorials
	assert(test_filedimensions(1, 7, 3) == 1);
	assert(test_filedimensions(2, 7, 7) == 1);
	assert(test_filedimensions(3, 9, 8) == 1);
	assert(test_filedimensions(4, 9, 8) == 1);
	assert(test_filedimensions(5, 9, 8) == 1);
	assert(test_filedimensions(6, 9, 8) == 1);
	assert(test_filedimensions(7, 9, 8) == 1);

	// Games
    assert(test_filedimensions(8, 11, 8) == 1);
    assert(test_filedimensions(9, 10, 13) == 1);
    assert(test_filedimensions(10, 13, 14) == 1);

    return 1;
}

int test_filedimensions(int lvl, int nrows, int ncols) {
    
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

    // Level aanmaken en inlezen
    Level *l = load_level(8);

    assert(array_compare(l, arr, 11, 8) == 1);

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