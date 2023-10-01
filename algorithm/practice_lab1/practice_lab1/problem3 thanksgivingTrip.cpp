#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int divideAndConquer(int, int*, int);
int compare(const void*, const void*);

void main() {
	int tripCnt = 0;
	int studentNum;
	int output[100];

	do {
		printf("Enter number of students(<100): ");
		scanf("%d", &studentNum);
		if (studentNum == 0)
			break;
		int* spent = (int*)malloc(sizeof(int) * studentNum);
		int sum = 0;
		printf("Enter the amount spent by a student in 10 won units(<100000): \n");
		for (int i = 0; i < studentNum; i++) {
			scanf("%d", &spent[i]);
			sum += spent[i];
		}
		output[tripCnt] = divideAndConquer(studentNum, spent, sum);

		free(spent);
		tripCnt++;
	} while (studentNum != 0);

	for (int i = 0; i < tripCnt; i++) {
		printf("\\%d\n", output[i]);
	}


}

int divideAndConquer(int studentNum, int spent[], int sum) {
	int avg = sum / studentNum;
	int exchange = 0;
	int temp;


	qsort(spent, studentNum, sizeof(int), compare);//오름차순 정렬


	for (int i = 0; i < (studentNum / 2); i++) {
		temp = spent[i] - avg;
		exchange += temp - temp % 10;
	}


	return exchange;

}

int compare(const void* a, const void* b) {
	int n1 = *(int*)a;
	int n2 = *(int*)b;
	
	return n2 - n1;
}