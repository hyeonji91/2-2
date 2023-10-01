#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int** matrix;
int rowCnt, colCnt;
int* result();
int min(int, int, int, int, int*);

void main() {
	FILE* input;
	int cost;

	//입력
	input = fopen("cheapestWay_input.txt", "r");

	while (fscanf(input, "%d %d", &rowCnt, &colCnt) != EOF) {

		//input
		matrix = (int**)malloc(sizeof(int*) * rowCnt);
		for (int i = 0; i < rowCnt; i++) 
			matrix[i] = (int*)malloc(sizeof(int) * colCnt);
		
		for (int i = 0; i < rowCnt; i++) {
			for (int j = 0; j < colCnt; j++) 
				fscanf(input, "%d", &matrix[i][j]);
		}

		//결과 계산
		int* cost = result();
		int sumCost = 0;
		//output
		for (int i = 0; i < colCnt; i++) {
			printf("%d ", cost[i]);
			sumCost += cost[i];
		}
		printf("\n%d\n", sumCost);

		//free
		for (int i = 0; i < rowCnt; i++) {
			free(matrix[i]);
		}
		free(matrix);
	}





	fclose(input);
}

int* result() {
	int** costMatrix;
	int** indexMatrix;
	int minRowIndex = 0;

	costMatrix = (int**)malloc(sizeof(int*) * rowCnt);
	for (int i = 0; i < rowCnt; i++)
	{
		costMatrix[i] = (int*)malloc(sizeof(int) * colCnt);
		costMatrix[i][0] = matrix[i][0];
	}

	indexMatrix = (int**)malloc(sizeof(int*) * rowCnt);
	for (int i = 0; i < rowCnt; i++) {
		indexMatrix[i] = (int*)malloc(sizeof(int) * colCnt);
		memset(indexMatrix[i], -1, sizeof(indexMatrix[i]));
	}

	
	for (int j = 1; j < colCnt; j++) {
		for (int i = 0; i < rowCnt; i++) {
			if(i==0)
			{
				costMatrix[i][j] = min(costMatrix[rowCnt - 1][j - 1], costMatrix[i][j - 1], costMatrix[i + 1][j - 1], i, &minRowIndex) + matrix[i][j];
			}
			else if(i == rowCnt-1)
			{
				costMatrix[i][j] = min(costMatrix[i - 1][j - 1], costMatrix[i][j - 1], costMatrix[0][j - 1], i, &minRowIndex) + matrix[i][j];
			}
			else
			{
				costMatrix[i][j] = min(costMatrix[i - 1][j - 1], costMatrix[i][j - 1], costMatrix[i + 1][j - 1], i, &minRowIndex) + matrix[i][j];
			}
			indexMatrix[i][j] = minRowIndex;
		}
	}

	//printf("costMatrix");
	//for (int i = 0; i < rowCnt; i++) {
	//	for (int j = 0; j < colCnt; j++)
	//		printf("%d ", costMatrix[i][j]);
	//	printf("\n\n");
	//}
	//printf("indexMatrix");
	//for (int i = 0; i < rowCnt; i++) {
	//	for (int j = 0; j < colCnt; j++)
	//		printf("%d ", indexMatrix[i][j]);
	//	printf("\n\n");
	//}



	//결과 찾기
	int min = costMatrix[0][colCnt-1];
	int minIndex =0;
	
	for (int i = 0; i < rowCnt; i++) {
		if (min > costMatrix[i][colCnt - 1])
		{
			min = costMatrix[i][colCnt - 1];
			minIndex = i;
		}
	}

	int* cost = (int*)malloc(sizeof(int)*colCnt);
	for (int j = colCnt - 1; j >= 0; j--) {
		cost[j] = matrix[minIndex][j];
		minIndex = indexMatrix[minIndex][j];
	}

	return cost;
}

int min(int a, int b, int c, int i, int* minIndex) {

	int min = a;
	if (i == 0)
		*minIndex = rowCnt - 1;
	else
		*minIndex = i - 1;

	if (b < min){
		min = b;
		*minIndex = i;
	}
	if (c < min){
		min = c;
		if (i == rowCnt - 1)
			*minIndex = 0;
		else
			*minIndex = i + 1;
	}

	return min;
}