#include <malloc.h>
#include <string.h>
#include "levelloadertester.h"

int test_filesdimensions() {
	assert(test_filedimensions("pi_escape/level/level_files/game1.lvl", 11, 8) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/game2.lvl", 10, 13) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/game3.lvl", 13, 14) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial1.lvl", 7, 3) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial2.lvl", 7, 7) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial3.lvl", 9, 8) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial4.lvl", 9, 8) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial5.lvl", 9, 8) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial6.lvl", 9, 8) == 0);
	assert(test_filedimensions("pi_escape/level/level_files/tutorial7.lvl", 9, 8) == 0);
	return 1;
}

int test_filedimensions(char *path, int nrows, int ncols) {
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
    return 0;
}

int test_game1() {
	char cmp[11][8] = {
	{' ', ' ', ' ', 'E', ' ', ' ', ' ', ' '} ,
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} ,
	{'X', 'X', 'X', '#', 'X', 'X', 'X', 'X'} ,
	{' ', ' ', ' ', '.', ' ', ' ', 'a', ' '} ,
	{'C', '.', '.', '&', ' ', ' ', ' ', ' '} ,
	{' ', ' ', ' ', '.', '.', '.', 'B', ' '} ,
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} ,
	{'X', 'X', '#', 'X', 'X', 'X', 'X', 'X'} ,
	{' ', ' ', '.', ' ', ' ', ' ', ' ', ' '} ,
	{' ', ' ', 'A', ' ', 'o', ' ', ' ', ' '} ,
	{' ', ' ', 'S', ' ', 'b', ' ', ' ', ' '} 
	};

	LevelLoader *ll = malloc(sizeof(LevelLoader));
	ll->file = strdup("pi_escape/level/level_files/game1.lvl");
	FILE *f;
	f = fopen(ll->file, "r");
	struct Level *l = malloc(sizeof(Level));

	level_init(l, 11, 8, 1);

	read_level(l, ll);

	assert(array_compare(l->spel, cmp, 11, 8) == 1);

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
    assert(l->spel[0][3] == 'E');

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


int array_compare(char **a, char **b, int rij, int kol) {
	for (int i = 0; i < rij; i++) {
		for (int j = 0; j < kol; j++) {
			if (a[i][j] != b[i][j]) return 0;
		}
	}
	return 1;
}