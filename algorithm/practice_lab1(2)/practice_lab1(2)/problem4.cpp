#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Elephant {
	int index;
	int iq;
	int weight;
};

Elephant elephant[10000] = { 0, };
int lengthOfresult[10000] = { 0, };
int indexForBackTrace[10000] = { -1, };
int longestLen = -1;
int lastIndex = 0;

int ascending(const void* a, const void* b) {
	Elephant* e1 = (Elephant*)a;
	Elephant* e2 = (Elephant*)b;

	if (e1->weight == e2->weight)
		return e1->iq - e2->iq;
	return e1->weight - e2->weight;
}
void backTrace(int* result) {
	
	int temp = lastIndex;
	for (int i = 0; i < longestLen; i++) {
		result[longestLen - 1 - i] = elephant[temp].index;
		temp = indexForBackTrace[temp];
		printf("temp[i] = %d\n", temp);
	}

}
void main() {
	int weight, iq, numOfElephant = 0;
	while (scanf("%d %d", &weight, &iq) != EOF) {
		elephant[numOfElephant].weight = weight;
		elephant[numOfElephant].iq = iq;
		elephant[numOfElephant].index = numOfElephant+1;
		numOfElephant++;
	}

	qsort(elephant, numOfElephant, sizeof(Elephant), ascending);

	for (int i = 0; i < numOfElephant; i++) {
		lengthOfresult[i] = 1;
		for (int j = 0; j < i; j++) {
			if (elephant[i].weight > elephant[j].weight
				&& elephant[i].iq < elephant[j].iq
				&& lengthOfresult[i] < lengthOfresult[j] + 1) {
				lengthOfresult[i] = lengthOfresult[j] + 1;
				indexForBackTrace[i] = j;
				if (lengthOfresult[i] > longestLen) {
					longestLen = lengthOfresult[i];
					lastIndex = i;
				}
			}
		}
	}

	printf("%d\n", longestLen);
	int* result = (int*)malloc(sizeof(int) * longestLen);
	backTrace(result);
	for (int i = 0; i < longestLen; i++) {
		printf("%d\n", result[i]);
	}

	free(result);
	
}