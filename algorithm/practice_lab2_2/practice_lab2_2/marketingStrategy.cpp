#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Dot {
	float x;
	float y;
};

Dot dot[30];

int cmpX(const void*, const void*);
int cmpY(const void*, const void*);
float closestPair(Dot*, int, int);
float distance(Dot, Dot);
float min(float, float);
void main() {
	int numOfDot;
	float x, y;

	while (true) {
		//input
		scanf("%d", &numOfDot);
		if (numOfDot <= 0 || numOfDot > 30)
			return;
		for (int i = 0; i < numOfDot; i++) {
			scanf("%f %f", &x, &y);
			dot[i].x = x;
			dot[i].y = y;
		}

		qsort(dot, numOfDot, sizeof(Dot), cmpX);//sort ascending order by X

		float minDis = closestPair(dot, 0, numOfDot - 1);
		if (minDis > 10000)
			printf("infinity\n");
		else
			printf("%0.2f\n", minDis);
	}
}
int cmpX(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->x > d2->x)
		return 1;
	else return -1;
}
int cmpY(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->y > d2->y)
		return 1;
	else return -1;
}
float closestPair(Dot* dot, int start, int end) {
	if (end - start == 0) {//one dot
		return 0;
	}
	else if (end - start == 1) {
		return distance(dot[start], dot[end]);
	}
	else if (end - start == 2) {
		float minDis = min(distance(dot[start], dot[start + 1]), distance(dot[start], dot[start + 2]));
		return min(minDis, distance(dot[start + 1], dot[start + 2]));
	}

	int midIdx = (start + end) / 2;
	float ds = closestPair(dot, start, midIdx);
	float dl = closestPair(dot, midIdx + 1, end);
	float minDis = min(ds, dl);

	Dot S[15];
	int s_head = 0;
	for (int i = start; i <= end; i++) {
		if (dot[midIdx].x - minDis <= dot[i].x && dot[i].x <= dot[midIdx].x + minDis)
			S[s_head++] = dot[i];
	}
	qsort(S, s_head, sizeof(Dot), cmpY);
	for (int i = 0; i < s_head; i++) {
		for (int j = 1; j <= 7; j++) {
			if (i + j >= s_head)
				break;
			float d = distance(S[i], S[i + j]);
			if (d < minDis)
				minDis = d;
		}
	}
	return minDis;
}
float distance(Dot d1, Dot d2) {
	float x = d1.x - d2.x;
	float y = d1.y - d2.y;

	return sqrt(x * x + y * y);
}
float min(float a, float b) {
	if (a > b)
		return b;
	else return a;
}