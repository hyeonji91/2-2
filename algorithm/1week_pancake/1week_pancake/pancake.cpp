#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Index;

int* pancake(int*, int);
int* flip(int[], int);
int findMax(int[], int);
void printData(int[]);

void main() {
	int data[30];
	int* result;
	
	int temp;
	int i = 0;
	printf("enter pancake(end: -1):");
	for (i = 0; i < 30; i++) {
		scanf_s("%d", &temp);
		if (temp == -1)
			break;
		else
			data[i] = temp;
	}
	Index = i;
	printf("============original=============\n");
	printData(data);
	result=pancake(data, i);

	printf("============result=============\n");
	printf("(");
	printData(result);
	printf(")");



}

int* pancake(int* data, int currentIndex) {

	if (currentIndex == 0)
		return data;

	int maxIndex = 0;

	maxIndex= findMax(data, currentIndex);
	
		data = flip(data, maxIndex);
		printf("============flip1=============\n");
		printData(data);
	
	data = flip(data, currentIndex-1);
	printf("============flip2=============\n");
	printData(data);

	pancake(data, currentIndex - 1);
}

int findMax(int data[], int currentIndex) {
	int max =0;
	int maxIndex = 0;
	for (int i = 0; i < currentIndex; i++) {
		if (max < data[i]) {
			max = data[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

int* flip(int data[], int currentIndex) {
	int* filpData = (int*)malloc(sizeof(int)* (Index));//동적할당
	memset(filpData, 0, currentIndex *sizeof(int));//초기화

	for (int i = 0; i <= currentIndex; i++) {
		filpData[i] = data[currentIndex - i];
	}
	//printf("filp1: ");
	//printData(filpData);
	//if (currentIndex != 0) {
		for (int j = currentIndex + 1; j < Index; j++) {
			filpData[j] = data[j];
		}
	//}
	return filpData;
	free(filpData);
}

void printData(int data[]) {
	for (int i = 0; i < Index; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}