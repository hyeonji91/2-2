#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int pearlNum;
int* dp;


void result(int c1, int n1, int c2, int n2) {
	int minNum, maxNum;
	dp[n1] = c1;
	dp[n2] = c2;
	if (n1 > n2)
	{
		minNum = n2;
		maxNum = n1;
	} 
	else
	{
		minNum = n1;
		maxNum = n2;
	}

	for (int i = minNum; i < pearlNum; i++) {
		if (dp[i - n1] != -1 && dp[i - n2] != -1 && i > maxNum) {
			dp[i] = min(dp[i - n1] + c1, dp[i - n2] + c2);
		}
	}
}
void main() {
	int c1, n1, c2, n2;

	while (1) {
		scanf("%d", &pearlNum);
		if (pearlNum == 0)
			break;
		dp = (int*)malloc(sizeof(int) * pearlNum);
		memset(dp, -1, sizeof(int));
		scanf("%d %d", &c1, &n1);
		scanf("%d %d", &c2, &n2);

		result(c1, n1, c2, n2);
	}
}