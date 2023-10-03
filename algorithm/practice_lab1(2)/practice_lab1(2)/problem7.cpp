#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int pearlNum;


void calCost(int smallN, int bigN) {
	int tempPearlNum = pearlNum;
	while (tempPearlNum >= 0)
	{
		if (tempPearlNum % smallN == 0) {
			printf("%d %d\n", tempPearlNum / smallN, (pearlNum - tempPearlNum) / bigN);
			break;
		}
		else
			tempPearlNum -= bigN;
	}
	if (tempPearlNum < 0)
		printf("faild\n");
}
void result(int c1, int n1, int c2, int n2) {
	float v1 = (float)c1 / n1;
	float v2 = (float)c2 / n2;
	int tempPearlNum = pearlNum;


	if (v1 < v2) {
		calCost(n1, n2);
	}
	else {
		calCost(n2, n1);
	}
}

void main() {
	int c1, n1, c2, n2;

	while (1) {
		scanf("%d", &pearlNum);
		if (pearlNum == 0)
			break;
		scanf("%d %d", &c1, &n1);
		scanf("%d %d", &c2, &n2);

		result(c1, n1, c2, n2);
	}


}