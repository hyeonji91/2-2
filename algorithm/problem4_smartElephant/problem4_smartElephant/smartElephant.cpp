#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void main() {
	FILE* inputFile;
	char buf[1024];

	if (inputFile = fopen("smartElephantInput.txt", "r")) {
		while(feof(inputFile) == 0)
		{
			fscanf( )
			//fgets(buf, sizeof(buf), inputFile);
			printf("%s", buf);

		}
		fclose(inputFile);

	}
}