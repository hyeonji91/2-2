#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct Elephant {
	int index;
	int weight;
	int iq;
}Elephant;

Elephant elephant[10000] = { 0, };
int dp[10000] = { 0, };
int backTraceIndex[10000] = { -1, };
int resultlen =0, lastIndex;

int ascending(const void* a, const void* b) {
	Elephant* e1 = (Elephant*)a;
	Elephant* e2 = (Elephant*)b;

	if (e1->weight == e2->weight)//if weight same, sort by iq
		return e1->iq - e2->iq;
	return e1->weight - e2->weight;
}
void main() {
	int elephantCnt = 0;
	int weight;
	int iq;
	while (scanf("%d %d", &weight, &iq) != EOF) {
		elephant[elephantCnt].weight = weight;
		elephant[elephantCnt].iq = iq;
		elephant[elephantCnt].index = elephantCnt + 1;
		elephantCnt++;
	}

	qsort(elephant, elephantCnt, sizeof(Elephant), ascending);

	for (int i = 0; i < elephantCnt; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (elephant[i].weight > elephant[j].weight && elephant[i].iq < elephant[j].iq && dp[i] < dp[j] + 1) {
				dp[i] = dp[j] + 1;
				backTraceIndex[i] = j;
				if (resultlen < dp[i]) {
					lastIndex = i;
					resultlen = dp[i];
				}
			}
		}
	}

	
	printf("%d\n", resultlen);
	int* resultIndex = (int*)malloc(sizeof(int) * resultlen);
	int curIndex = lastIndex;
	for (int i = 0; i < resultlen; i++) {
		resultIndex[resultlen-i-1] = elephant[curIndex].index;
		curIndex = backTraceIndex[curIndex];
	}
	for (int i = 0; i < resultlen; i++) {
		printf("%d\n", resultIndex[i]);
	}
	}