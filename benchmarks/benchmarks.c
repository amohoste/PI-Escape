#include "benchmarks.h"

#include <stdio.h>

void register_get(int param) {
	FILE *fp = fopen("./benchmarks.txt", "a");
	fprintf(fp, "%i %i\n", GET_COMPONENT, param);
	fclose(fp);
}

void benchmark() {
	FILE * fp = fopen("./benchmarks.txt", "r");
	char * line = NULL;
	size_t len = 0;
	size_t read;

	//if (fp == NULL)
	//	exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		//Functions function =
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
		//switch (function)
		//{
		//default:
		//	break;
		//}
	}
}