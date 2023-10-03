#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int matrix[10][100] = { 0, };
int cost[10][100] = { 0, };
int index[10][100] = { 0, };

int min(int row1, int row2, int row3, int col, int* minRowNumber) {

	int min = cost[row1][col];
	*minRowNumber = row1;

	if (min > cost[row2][col]) {
		min = cost[row2][col];
		*minRowNumber = row2;
	}
	if (min > cost[row3][col]) {
		min = cost[row3][col];
		*minRowNumber = row3;
	}

	return min;
}

void main() {
	FILE* inputFile;
	int row, col, minRowNumber = 0; 

	inputFile = fopen("cheapestWay_input.txt", "r");

	while (fscanf(inputFile, "%d %d", &row, &col) != EOF) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				fscanf(inputFile, "%d", &matrix[i][j]);
			}
		}

		for (int i = 0; i < row; i++) {
			cost[i][0] = matrix[i][0];
		}
		for (int j = 1; j < col; j++) {
			for (int i = 0; i < row; i++) {
				if(i==0)
					cost[i][j] = min(row - 1, i,i + 1, j-1, &minRowNumber) + matrix[i][j];
				else if(i == row-1)
					cost[i][j] = min(i - 1, i, 0, j - 1, &minRowNumber) + matrix[i][j];
				else
					cost[i][j] = min(i - 1, i, i + 1, j - 1, &minRowNumber) + matrix[i][j];

				index[i][j] = minRowNumber;
			}
		}





		int minCost = cost[0][col - 1];
		int lastMinRowNumber = 0;
		for (int i = 0; i < row; i++) {
			if (minCost > cost[i][col - 1])
			{
				minCost = cost[i][col - 1];
				lastMinRowNumber = i;
			}
		}
		int* result = (int*)malloc(sizeof(int) * col);
		for (int i = col-1; i >= 0; i--) {
			result[i] = matrix[lastMinRowNumber][i];
			lastMinRowNumber = index[lastMinRowNumber][i];
		}

		for (int i = 0; i < col; i++) {
			printf("%d ", result[i]);
		}
		printf("\n%d\n", minCost);
		free(result);
		
	}


}