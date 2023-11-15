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
Dot stdDot = { 0,0,0 };
int minYIdx;
int numOfDot;

Dot stack[100];
int top = -1;

float getAngle(Dot, Dot);
int cmpAngle(const void*, const void*);
float convexHull();
int isCw(Dot d1, Dot d2, Dot d3) {
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
	printf("[PUSH] (%f, %f) \n", pushDot.x, pushDot.y);

}
Dot pop() {
	if (isEmpty())
		printf("stack is empty\n");
	else
	{
		Dot popDot = stack[top--];
		printf("[POP] (%f, %f) \n", popDot.x, popDot.y);

		return popDot;
	}
}
void main() {
	int testCase;
	float x, y;
	FILE* input;
	input = fopen("input.txt", "r");

	fscanf(input, "%d", &testCase);
	while (testCase--) {
		fscanf(input, "%d", &numOfDot);
		dot = (Dot*)malloc(sizeof(Dot) * numOfDot);
		for (int i = 0; i < numOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
		}

		//find start point(smallest y-coordinate. if points have same y-coordinate than choose point with smaller x-coordinate
		float minY = dot[0].y;
		float minX = dot[0].x;
		minYIdx = 0;
		for (int i = 0; i < numOfDot; i++) {
			if (minY > dot[i].y) {
				float minY = dot[i].y;
				float minX = dot[i].x;
				int minYIdx = i;
			}
			else if (minY == dot[i].y && minX > dot[i].x) {
				float minY = dot[i].y;
				float minX = dot[i].x;
				int minYIdx = i;
			}
		}

		//get relative anlge(standard point is dot[minYIdx]
		for (int i = 0; i < numOfDot; i++) {
			dot[i].angle = getAngle(dot[minYIdx], dot[i]);
		}

		//sort dot ascending order based on angle
		qsort(dot, numOfDot, sizeof(Dot), cmpAngle);

		float result = convexHull();
		printf("%f\n", result);
	}


}

float getAngle(Dot dot1, Dot dot2) {
	float m = (dot2.y - dot1.y) / (dot2.x - dot1.x);

	float angle_radian = atan(m);
	return angle_radian * (180 / 3.14);
}
int cmpAngle(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->angle > d2->angle) return 1;
	else return -1;
}
float convexHull() {
	if (numOfDot == 0)
		return 0;
	if (numOfDot == 1)
		return distance(dot[0], stdDot)*2;
	if (numOfDot == 2) {
		return distance(dot[0], dot[1]) + distance(dot[0], stdDot) + distance(stdDot, dot[1]);
	}
	push(dot[0]);
	push(dot[1]);
	push(dot[2]);
	for (int i = 3; i < numOfDot; i++) {
		if (isCw(dot[top - 1], dot[top], dot[i]))
			pop();
		push(dot[i]);
	}

	//calculate whole distance
	float result = 0;
	for (int i = 0; i <= top; i++) {
		result += distance(stack[i], stack[(i + 1) % (top + 1)]);
	}
	result += distance(stdDot, dot[minYIdx])*2;
	return result;

}
