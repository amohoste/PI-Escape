//
// Created by aggoetey on 10/10/17.
//
#include "stdio.h"
#include "levelloader.h"


void test_level_read();

int main(){
    test_level_read();
    return 0;
}

void test_level_read() {
    FILE *file = fopen("level_files/game1.lvl", "r");
    int rows =0;
    int cols =0;
    rows_cols_read(file,&rows, &cols);
    printf("rijen %d, kolommen %d", rows, cols);
}

