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
Dot convexDot[MAX_DOT_NUM];
Dot stack[MAX_DOT_NUM];
int top;

float getAngle(Dot, Dot);
int findLeftMostDotIdx();
float calcDistance(Dot, Dot);
int cmp(const void*, const void*);
//stack
int isEmpty();
int isFull();
void push(Dot);
Dot pop();
void initStack();
void main() {
	int testCase;
	float x, y;
	FILE* input = NULL;
	input = fopen("input.txt", "r");

	fscanf(input, "%d", &testCase);
	while (testCase--) {
		//init & input
		initStack();
		float result = 2;
		int convexDotNum = 0;
		fscanf(input, "%d", &numOfDot);
		dot = (Dot*)malloc(sizeof(dot) * numOfDot);
		for (int i = 0; i < numOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
			dot[i].angle = 0;
		}

		int startIdx = findLeftMostDotIdx();
		if (numOfDot == 1) {
			result += 2*calcDistance(dot[0], stdDot);
		}
		else {
			convexDot[0] = dot[startIdx];
			Dot curDot = dot[startIdx];

			for (int i = 0; i < numOfDot; i++) {
				for (int j = 0; j < numOfDot - i; j++) {
					dot[j].angle = getAngle(curDot, dot[j]);//get relative angle
				}
				qsort(dot, numOfDot-i, sizeof(Dot), cmp);//각도기준으로 오름차순
				printf("=================\n");
				for (int k = 0; k < numOfDot; k++) {
					printf("(%f, %f) : angle = %f\n", dot[k].x, dot[k].y, dot[k].angle);
				}
				if (dot[numOfDot - i].x == convexDot[0].x && dot[numOfDot - i].y == convexDot[0].y)
					break;
				convexDot[i+1] = dot[numOfDot-i];
				curDot = convexDot[i+1]; 
				convexDotNum ++;
			}

			for (int i = 0; i < convexDotNum; i++) {
				printf("convexDot[%d] : (%f, %f)\n", i, convexDot[i].x, convexDot[i].y);
			}
		}



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
float getAngle(Dot stdDot, Dot cmpDot) {
	float relativeAngle = -10;
	float dy = cmpDot.y - stdDot.y;
	float dx = cmpDot.x - stdDot.x;
	float angle = fabs(dy) / (fabs(dx) + fabs(dy));
	if (cmpDot.x > stdDot.x && cmpDot.y == stdDot.y)
		relativeAngle = 0;
	else if (cmpDot.x >= stdDot.x && cmpDot.y > stdDot.y)
		relativeAngle = angle;
	//else if (cmpDot.x == stdDot.x && cmpDot.y > stdDot.y)
	//	relativeAngle = 1;
	else if (cmpDot.x < stdDot.x && cmpDot.y >= stdDot.y)
		relativeAngle = 2 - angle;
	//else if (cmpDot.x < stdDot.x && cmpDot.y == stdDot.y)
	//	relativeAngle = 2;
	else if (cmpDot.x <= stdDot.x && cmpDot.y < stdDot.y)
		relativeAngle = 2 + angle;
	//else if (cmpDot.x == stdDot.x && cmpDot.y < stdDot.y)
	//	relativeAngle = 3;
	else if(cmpDot.x > stdDot.x && cmpDot.y < stdDot.y)
		relativeAngle = 4 - angle;

	//printf("stdDot(%f, %f) cmpDot(%f %f) angle = %f\n", stdDot.x, stdDot.y, cmpDot.x, cmpDot.y, relativeAngle);
	return relativeAngle;
}
int cmp(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->angle > d2->angle)
		return 1;
	return 0;
}
//stack
int isEmpty() {
	if (top < 0)
		return true;
	return false;
}
int isFull() {
	if (top == MAX_DOT_NUM - 1)
		return true;
	return false;
}
void push(Dot dot) {
	if (isFull())
		printf("stack is full\n");
	else
		stack[++top] = dot;
}
Dot pop() {
	if (isEmpty())
		printf("stack is empty\n");
	else
		return stack[top--];
}
void initStack() {
	top = -1;
}