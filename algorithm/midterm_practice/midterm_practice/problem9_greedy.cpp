#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Order {
	int time;
	int penalty;

	int index;
};
Order order[1000];

void main() {
	int testCase, numOfOrder, penalty, time, countTest = 0;

	scanf("%d, &testCase");
	printf("\n");
	while(countTest < testCase){
		scanf("%d", &numOfOrder);
		for (int j = 0; j < numOfOrder; j++) {
			scanf("%d %d", &time, &penalty);
			order[j].time = time;
			order[j].penalty = penalty;
			order[j].index = j + 1;
		}



		countTest++;
	}
}