#include "levelloadertester.h"

int test_game1() {
	FILE *f;
	f = fopen("level_files/game1.lvl", "r");
	int rows = 0;
	int cols = 0;
	rows_cols_read(f, &rows, &cols);
	assert(rows == 11);
	assert(cols == 8);
	return 1;
}