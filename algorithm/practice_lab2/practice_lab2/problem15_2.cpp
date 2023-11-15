#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_DOT_NUM 100

typedef struct Dot {
	float x;
	float y;
	float angle;
};

Dot stdDot = { 0,0,0 };
Dot* dot;
int numOfDot;
Dot convexHull[MAX_DOT_NUM];
int convexDotNum = 0;

int findLeftMostDotIdx();
float calcDistance(Dot, Dot);
void add(Dot);
int isCCW(Dot, Dot, Dot);
void main() {
	int testCase;
	float x, y;
	FILE* input = NULL;
	input = fopen("input.txt", "r");

	fscanf(input, "%d", &testCase);
	while (testCase--) {
		//init & input
		int resultNum = 0;
		float result = 2;
		convexDotNum = 0;
		fscanf(input, "%d", &numOfDot);
		dot = (Dot*)malloc(sizeof(dot) * numOfDot);
		for (int i = 0; i < numOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
			dot[i].angle = 0;
		}

		int minXIdx = findLeftMostDotIdx();


		int p, s;//p:convexhull에 포함 s는 미포함
		p = minXIdx;
		
		while (true) {
			//printf("\n===========================\n");
			//printf("[p:%d]", p);
			add(dot[p]);
			s = (p + 1) % numOfDot;
			for (int i = 0; i < numOfDot; i++) {
				//printf("[s:%d]", s);
				if (isCCW(dot[p], dot[i], dot[s]))
					s = i;
			}
			p = s;
			if (p == minXIdx) {
				//printf("[BREAK]\n");
				break;

			}
		}

		//0,0과 묶을 convexhull에 포함된 dot : shortest length로 선택
		float minDistance = 2100000000;
		int startIndex;
		for (int i = 0; i < convexDotNum; i++) {
			float d1 = calcDistance(stdDot, convexHull[i]);
			float d2 = calcDistance(stdDot, convexHull[(i + 1) % convexDotNum]);
			float d3 = calcDistance(convexHull[i], convexHull[(i + 1) % convexDotNum]);
			float d = d1 + d2 - d3;
			if (minDistance > d) {
				minDistance = d;
				startIndex = (i + 1) % convexDotNum;
			}
		}

		for (int i = 0; i < convexDotNum; i++) {
			result += calcDistance(convexHull[i], convexHull[(i + 1) % convexDotNum]);
		}
		result += minDistance;

		printf("\n================result : %0.2f====================\n", result);

	}
}

int findLeftMostDotIdx() {
	float minX = dot[0].x, minY = dot[0].y;
	int minIdx;

	for (int i = 0; i < numOfDot; i++) {
		if (minX > dot[i].x) {
			minX = dot[i].x;
			minY = dot[i].y;
			minIdx = i;
		}
		else if (minX == dot[i].x && minY > dot[i].y) {
			minX = dot[i].x;
			minY = dot[i].y;
			minIdx = i;
		}
	}
	return minIdx;
}
float calcDistance(Dot d1, Dot d2) {
	float a = d1.x - d2.x;
	float b = d1.y - d2.y;

	return sqrt(a * a + b * b);
}
void add(Dot d) {
	convexHull[convexDotNum++] = d;
	
	//for (int i = 0; i < convexDotNum; i++) {
	//	printf("(%0.2f, %0.2f)\n", convexHull[i].x, convexHull[i].y);
	//}
}
int isCCW(Dot d1, Dot d2, Dot d3) {
	float S = (d1.x * d2.y + d2.x * d3.y + d3.x * d1.y) - (d1.x * d3.y + d2.x * d1.y + d3.x * d2.y);

	if (S > 0)
		return true;
	else return false;
}