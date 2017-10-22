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
	LevelLoader *ll = levelloader_alloc();
	ll->file = strdup(path);

	// Level aanmaken en inlezen
	Level *l = levelloader_load_level(ll, 1);
	assert(l->width == ncols);
	assert(l->height == nrows);

	return 1;
}

int test_game1() {
	char arr[11][8] = {
	{' ', ' ', ' ', 'E', ' ', ' ', ' ', ' '} ,
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} ,
	{'X', 'X', 'X', '#', 'X', 'X', 'X', 'X'} ,
	{' ', ' ', ' ', '.', ' ', ' ', 'a', ' '} ,
	{'C', '.', '.', '&', ' ', ' ', ' ', ' '} ,
	{' ', ' ', ' ', '.', '.', '.', 'B', ' '} ,
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} ,
	{'X', 'X', '#', 'X', 'X', 'X', 'X', 'X'} ,
	{' ', ' ', '.', ' ', ' ', ' ', ' ', ' '} ,
	{' ', ' ', 'A', ' ', ' ', 'o', ' ', ' '} ,
	{' ', ' ', 'S', ' ', ' ', 'b', ' ', ' '}
	};

	
	// Levelloader aanmaken
	LevelLoader *ll = levelloader_alloc();
	ll->file = strdup("pi_escape/level/level_files/game1.lvl");

	// Level aanmaken en inlezen
	Level *l = levelloader_load_level(ll,1);

	assert(array_compare(l, arr, 11, 8) == 1);

	return 1;
}

int test_few() {

	// Levelloader aanmaken
	LevelLoader *ll = levelloader_alloc();
	ll->file = strdup("pi_escape/level/level_files/game1.lvl");
	
	// Level aanmaken en inlezen
	Level *l = levelloader_load_level(ll, 1);

	assert(l->spel[0][0] == ' ');
    assert(l->spel[0][3] == 'E');

    return 1;
}

int array_compare(Level* a, char b[][8], int rij, int kol) {

	for (int i = 0; i < rij; i++) {
		for (int j = 0; j < kol; j++) {
			if (a->spel[i][j] != b[i][j]) return 0;
		}
	}
	
	return 1;
}