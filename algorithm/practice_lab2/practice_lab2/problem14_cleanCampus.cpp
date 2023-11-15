#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MAX_DOT_NUM 101

typedef struct Dot {
	float x;
	float y;
	float angle;
};
Dot* dot;
Dot stdDot = Dot{ 0, 0, 0 };
int numberOfDot;
Dot stack[MAX_DOT_NUM];//MAX_DOT_NUM+init
int top = -1;

float getAngle(Dot);//tanθ and θ(angle) are proportional. so we calculate tanθ.
int cmpAngle(const void*, const void*);//compare angle
int getStartDotIdx();
float getDistance(Dot, Dot);
int isCw(Dot, Dot, Dot);
//stack function
int isEmpty();
int isFull();
void push(Dot);
Dot pop();
void initStack();
void main() {
	int testCase;
	float x, y;
	

	FILE* input = fopen("input.txt", "r");
	fscanf(input, "%d", &testCase);

	while (testCase--) {
		//init
		float convexHull = 2;//묶는 길이 2
		initStack();
		fscanf(input, "%d", &numberOfDot);
		dot = (Dot*)malloc(sizeof(Dot) * (numberOfDot));

		for (int i = 0; i < numberOfDot; i++) {
			fscanf(input, "%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
			dot[i].angle = getAngle(dot[i]);//0,0과 angle계산
		}

		//angle기준으로 오름차순 정렬
		qsort(dot, (numberOfDot), sizeof(Dot), cmpAngle);

		//printf("=================================================================\n");
		//for (int i = 0; i < numberOfDot; i++) {
		//	printf("x=%f, y=%f, angle = %f\n", dot[i].x, dot[i].y, dot[i].angle);
		//}
		//printf("\n");

		//convexHull 점 구하기
		if (numberOfDot <= 1) {
			convexHull += 2*getDistance(dot[0], stdDot);
		}
		else if (numberOfDot == 2) {
			convexHull += getDistance(dot[0], stdDot);
			convexHull += getDistance(dot[1], stdDot);
			convexHull += getDistance(dot[1], dot[0]);
		}
		else {

			int startDotIdx = getStartDotIdx();//
			push(dot[startDotIdx]);
			push(dot[(startDotIdx + 1)%numberOfDot]);
			push(dot[(startDotIdx + 2)% numberOfDot]);
			for (int i = 3; i < numberOfDot; i++) {
				while (isCw(stack[top-1], stack[top], dot[(startDotIdx + i) % numberOfDot])) {
					Dot popDot = pop();
				}
				push(dot[(startDotIdx + i)%numberOfDot]);
			}


			convexHull += getDistance(stdDot, stack[top]);
			while(top > 0){
				Dot popDot = pop();
				convexHull += getDistance(popDot, stack[top]);
			}
			convexHull += getDistance(stdDot, stack[top]);
		}
		
		printf("%0.2f\n", convexHull);


		free(dot);
	}
	
}


float getAngle(Dot cmpDot) {
	float relativeAngle;
	float dy = cmpDot.y - stdDot.y;
	float dx = cmpDot.x - stdDot.x;
	if (cmpDot.x > stdDot.x && cmpDot.y == stdDot.y)
		relativeAngle = 0;
	else if (cmpDot.x > stdDot.x && cmpDot.y > stdDot.y)
		relativeAngle = fabs(dy) / (fabs(dx) + fabs(dy));
	if (cmpDot.x == stdDot.x && cmpDot.y > stdDot.y)
		relativeAngle = 1;
	else if (cmpDot.x < stdDot.x && cmpDot.y > stdDot.y)
		relativeAngle = 2 - fabs(dy) / (fabs(dx) + fabs(dy));
	if (cmpDot.x < stdDot.x && cmpDot.y == stdDot.y)
		relativeAngle = 2;
	else if (cmpDot.x < stdDot.x && cmpDot.y < stdDot.y)
		relativeAngle = 2 + fabs(dy) / (fabs(dx) + fabs(dy));
	if (cmpDot.x == stdDot.x && cmpDot.y < stdDot.y)
		relativeAngle = 3;
	else if (cmpDot.x > stdDot.x && cmpDot.y < stdDot.y)
		relativeAngle = 4 - fabs(dy) / (fabs(dx) + fabs(dy));
	 
	return relativeAngle;
}

int cmpAngle(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	//return d1->angle - d2->angle;


	if (d1->angle > d2->angle)return 1;
	else if (d1->angle == d2->angle && d1->y == d2->y)
		return  d1->x - d2->x;
	else if (d1->angle == d2->angle) {
		return d1->y - d2->y;
	}
	else return 0;
}
int getStartDotIdx() {
	float minDistance = 2100000000, cmpDistance, d1, d2, d3;
	int startDotIdx = 0;
	for (int i = 0; i < numberOfDot; i++) {
		d1 = getDistance(stdDot, dot[i]);
		d2 = getDistance(stdDot, dot[(i + 1) % numberOfDot]);
		d3 = getDistance(dot[i], dot[(i + 1) % numberOfDot]);

		cmpDistance = d1 + d2 - d3;
		if (cmpDistance < minDistance) {
			minDistance = cmpDistance;
			startDotIdx = (i + 1) % numberOfDot;
		}
	}
	return startDotIdx;
}
float getDistance(Dot dot1, Dot dot2) {
	int a = dot1.x - dot2.x;
	int b = dot1.y - dot2.y;

	return sqrt((a * a) + (b * b));
}
int isCw(Dot dot1, Dot dot2, Dot dot3) {
	float m1, m2, s;
	s = (dot1.x * dot2.y + dot2.x * dot3.y + dot3.x * dot1.y) - (dot1.x * dot3.y + dot2.x * dot1.y + dot3.x * dot2.y);

	if (s > 0)//ccw
		return false;
	else if (s == 0) //straight line
		return false;
	else//cw
		return true;
}

//stack function
int isEmpty() {
	if (top < 0)
		return true;
	else
		return false;
}
int isFull() {
	if (top >= MAX_DOT_NUM-1)
		return true;
	else
		return false;
}
void push(Dot dot) {
	if (isFull())
		printf("stack is full\n");
	else
		stack[++top] = dot;
	//printf("[PUSH] (%f, %f) \n", dot.x, dot.y);
}
Dot pop() {
	Dot popDot;
	if (isEmpty())
		printf("stack is empty\n");
	else
	{
		popDot = stack[top--];
		//printf("[POP] (%f, %f) \n", popDot.x, popDot.y);

		return popDot;
	}
}
void initStack() {
	top = -1;
}