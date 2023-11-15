#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Dot {
	float x;
	float y;
	float angle;
};

Dot* dot;
Dot stdDot = { 0, 0, };
int minYIdx = 0;
int numOfDot;

Dot stack[100];
int top = -1;

float getAngle(Dot);
int cmpAngle(const void*, const void*);
float convexHull();
int isCw(Dot, Dot, Dot);
float distance(Dot, Dot);
//stack
void initStack();
int isEmpty();
int isFull();
void push(Dot);
Dot pop();
void main() {
	int testCase;
	float x, y;
	FILE* input;
	input = fopen("input.txt", "r");

	fscanf(input, "%d", &testCase);
	while (testCase--) {
		initStack();

		//input
		fscanf(input, "%d", &numOfDot);
		dot = (Dot*)malloc(sizeof(Dot) * numOfDot);
		for (int i = 0; i < numOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
		}

		//find point with smallest y-coordinate. If dots have same y-coordinate, select the point with smallest x-coordinate
		float minY = dot[0].y;
		float minX = dot[0].x;
		minYIdx = 0;
		for (int i = 0; i < numOfDot; i++) {
			if (minY > dot[i].y) {
				minY = dot[i].y;
				minX = dot[i].x;
				minYIdx = i;
			}
			else if (minY == dot[i].y && minX > dot[i].x) {
				minY = dot[i].y;
				minX = dot[i].x;
				minYIdx = i;
			}
		}
		printf("minYIdx:%d\n", minYIdx);

		//calculate relative angle
		for (int i = 0; i < numOfDot; i++) {
			//if(i == minYIdx){
			//	Dot d = { dot[minYIdx].x + 1, dot[minYIdx].y, 0 };
			//	dot[i].angle = getAngle(d);
			//}
			//else
				dot[i].angle = getAngle(dot[i]);
		}

		qsort(dot, numOfDot, sizeof(Dot), cmpAngle);//sort dot ascending order by angle
 
		//convexHull
		float result = convexHull();

		printf("%0.2f\n", result);

		free(dot);
	}
}

float getAngle(Dot cmpDot) {
	float dx = cmpDot.x - dot[minYIdx].x;
	float dy = cmpDot.y - dot[minYIdx].y;
	float angle;
	
	if (dy == 0 && dx == 0)
		angle = -1;
	else if (dy == 0 && dx > 0)
		angle = 0;
	else {
		angle = fabs(dy) / (fabs(dx) + fabs(dy));
		if (dx < 0 && dy >= 0)
			angle = 2 - angle;
		else if (dx <= 0 && dy < 0)
			angle = 2 + angle;
		else if (dx >= 0 && dy < 0)
			angle = 4 - angle;
	}
	return angle;

}
int cmpAngle(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->angle > d2->angle) return 1;
	else return 0;
}
float convexHull() {
	if (numOfDot == 1)
		return distance(dot[0], stdDot) + 2;
	if (numOfDot == 2) {
		return distance(dot[0], dot[1]) + distance(dot[0], stdDot) + distance(stdDot, dot[1]) + 2;
	}

	push(dot[0]);
	push(dot[1]);
	push(dot[2]);
	for (int i = 3; i < numOfDot; i++) {
		while (isCw(stack[top - 1], stack[top], dot[i])) {
			pop();
		}
		push(dot[i]);
	}

	//find the point connected to dot(0,0)
	float minDis = 2100000000;
	int startDot;
	for (int i = 0; i <= top; i++) {
		float d1 = distance(stdDot, stack[i]);
		float d2 = distance(stdDot, stack[(i + 1) % (top + 1)]);
		float d3 = distance(stack[(i + 1) % (top + 1)], stack[i]);
		float d = d1 + d2 - d3;
		if (minDis > d) {
			minDis = d;
		}
	}

	//calculate whole distance
	float result = 2;
	for (int i = 0; i <= top; i++) {
		result += distance(stack[i], stack[(i + 1) % (top + 1)]);
	}
	result += minDis;
	return result;
}
int isCw(Dot d1, Dot d2, Dot d3){
	float S = (d1.x * d2.y + d2.x * d3.y + d3.x * d1.y) - (d1.x * d3.y + d2.x * d1.y + d3.x * d2.y);
	if (S > 0) //ccw
		return false;
	else //cw or same line
		return true;
}
float distance(Dot d1, Dot d2) {
	float x = d1.x - d2.x;
	float y = d1.y - d2.y;

	return sqrt(x * x + y * y);
}

//stack
void initStack() {
	top = -1;
}
int isEmpty() {
	if (top == -1)
		return true;
	else return false;
}
int isFull() {
	if (top == 100 - 1)
		return true;
	else return false;
}
void push(Dot pushDot) {
	if (isFull())
		printf("stack is full\n");
	else
		stack[++top] = pushDot;
	//printf("[PUSH] (%f, %f) \n", pushDot.x, pushDot.y);

}
Dot pop() {
	if (isEmpty())
		printf("stack is empty\n");
	else
	{
		Dot popDot = stack[top--];
		//printf("[POP] (%f, %f) \n", popDot.x, popDot.y);

		return popDot;
	}
}