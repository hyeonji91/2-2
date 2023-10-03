#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


int compare(const void* a, const void* b) {
	int n1 = *(int*)a;
	int n2 = *(int*)b;

	return n1 - n2;//ascending
}
int result(int *money, int numOfStudent, int sum) {
	int result =0;
	int avg = sum / numOfStudent;
	int temp;
	qsort(money, numOfStudent, sizeof(int), compare);

	for (int i = 0; i < numOfStudent/2; i++) {
		temp = avg - money[i];
		result += temp - temp % 10;
		

	}
	return result;
}
void main() {
	int numOfstudent;
	int sum=0;

	while (1) {
		sum = 0;
		scanf("%d", &numOfstudent);
		if (numOfstudent == 0)
			break;
		else if (numOfstudent >= 100) {
			printf("please enter number no more than 100\n");
			continue;
		}
		int* money = (int*)malloc(sizeof(int) * numOfstudent);
		for (int i = 0; i < numOfstudent; i++) {
			printf("[#%d] ", i);
			scanf("%d", &money[i]);
			if (money[i] >= 100000) {
				printf("please enter money no more then 100000 won\n");
				i--;
				continue;
			}
			sum += money[i];
		}

		printf("\\%d\n", result(money, numOfstudent, sum));

		free(money);
	}
}