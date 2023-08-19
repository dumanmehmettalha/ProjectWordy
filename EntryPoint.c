#include <stdio.h>

int main() {
	FILE* fp = fopen("vocab.txt", "a+");
	fprintf(fp, "Bu bir Deneme yazisidir.");
	fclose(fp);
	return 0;
}