#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Dot {
	float x;
	float y;
};

Dot* dot;
Dot* convexHullDot;
int head = 0;
int numOfDot;
int minXIdx;
Dot stdDot = { 0, 0, };

int isCCW(Dot, Dot, Dot);
float distance(Dot, Dot);
float convexHull();
void main() {
	int testCase;
	float x, y;
	FILE* input;
	input = fopen("input.txt", "r");

	fscanf(input, "%d", &testCase);
	while (testCase--) {
		numOfDot;
		fscanf(input, "%d", &numOfDot);
		dot = (Dot*)malloc(sizeof(Dot) * numOfDot);
		convexHullDot = (Dot*)malloc(sizeof(Dot) * numOfDot);
		head = 0;
		for (int i = 0; i < numOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
		}

		//find left most dot
		float minX = dot[0].x;
		float minY = dot[0].y;
		minXIdx = 0;
		for (int i = 1; i < numOfDot; i++) {
			if (minX > dot[i].x){
				minX = dot[i].x;
				minY = dot[i].y;
				minXIdx = i;
			}
			else if (minX == dot[i].x && minY > dot[i].y) {
				minX = dot[i].x;
				minY = dot[i].y;
				minXIdx = i;
			}
		}

		//convexHull
		float result = convexHull();

		printf("%0.2f\n", result);

		free(dot);
		free(convexHullDot);
	}
}
int isCCW(Dot d1, Dot d2, Dot d3) {
	float S = (d1.x * d2.y + d2.x * d3.y + d3.x * d1.y) - (d1.x * d3.y + d2.x * d1.y + d3.x * d2.y);
	if (S > 0) //ccw
		return true;
	else //cw or same line
		return false;
}
float distance(Dot d1, Dot d2) {
	float x = d1.x - d2.x;
	float y = d1.y - d2.y;

	return sqrt(x * x + y * y);
}

float convexHull() {
	if (numOfDot == 1)
		return 2;
	else if (numOfDot == 2) {
		return distance(dot[0], dot[1])*2+2;
	}
	int cur, std;
	cur = minXIdx;
	while (true) {
		convexHullDot[head++] = dot[cur];
		std = (cur + 1) % numOfDot;

		for (int i = 0; i < numOfDot; i++) {
			while (isCCW(dot[cur], dot[i], dot[std])) {
				std = i;
			}
		}

		cur = std;
		if (cur == minXIdx)
			break;
	}

	//find the point connected to dot(0,0)
	float minDis = 2100000000;
	int startDot;
	for (int i = 0; i < head; i++) {
		float d1 = distance(stdDot, convexHullDot[i]);
		float d2 = distance(stdDot, convexHullDot[(i + 1) % head]);
		float d3 = distance(convexHullDot[(i + 1) % head], convexHullDot[i]);
		float d = d1 + d2 - d3;
		if (minDis > d) {
			minDis = d;
		}
	}

	//calculate whole distance
	float result = 2;
	for (int i = 0; i < head; i++) {
		result += distance(convexHullDot[i], convexHullDot[(i + 1) % head]);
	}
	result += minDis;
	return result;
}