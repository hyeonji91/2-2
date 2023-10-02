#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int pearlNum;

void calCost(int smallC, int smallN, int bigC, int bigN) {
	int tempPearlNum = pearlNum;
	int i;
	for (i = 0; tempPearlNum > 0; i++) {
		if (tempPearlNum % smallN == 0)
			break;
		tempPearlNum = tempPearlNum - bigN;
	}
	if (tempPearlNum <= 0)
		printf("failed\n");
	else {
		printf("%d %d\n", tempPearlNum / smallN, i);
	}
}

void result(int c1, int n1, int c2, int n2) {
	float v1 = (float)c1 / n1;//one pearl per cost
	float v2 = (float)c2 / n2;

	if (v1 < v2) {
		calCost(c1, n1, c2, n2);
	}
	else {
		calCost(c2, n2, c1, n1);
	}
}

void main() {
	int c1, n1, c2, n2;

	while(1) {
		scanf("%d", &pearlNum);
		if (pearlNum == 0)
			break;
		scanf("%d %d", &c1, &n1);
		scanf("%d %d", &c2, &n2);

		result(c1, n1, c2, n2);
	}


}