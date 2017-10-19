#include "levelloader.h"

#include <assert.h>

int test_filesdimensions();
int test_filedimensions(char *path, int nrows, int ncols);
int test_few();
int test_complete();
int array_compare(Level* a, char b[][8], int rij, int kol);
int test_game1();
