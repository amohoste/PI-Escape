#include "levelloader.h"

#include <assert.h>

int test_filesdimensions();
int test_filedimensions(char *path, int nrows, int ncols);
int test_game1();
int test_few();
int array_compare(Level* a, char b[][8], int rij, int kol);