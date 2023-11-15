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
float closetPair(Dot*, int, int);
float distance(Dot, Dot);
float min(float, float);
void main() {
	int numOfDot;
	float x, y;
	while (true) {
		//input
		printf("Enter number of dot N(0<=N<=30): ");
		scanf("%d", &numOfDot);
		if (numOfDot <= 0 || numOfDot > 30)
			return;
		printf("Enter dot [format : x y] (0<=x,y<=40000)\n");
		for (int i = 0; i < numOfDot; i++) {
			scanf("%f %f", &x, &y);
			if (x < 0 || x>40000 || y < 0 || y>40000)
				return;
			dot[i].x = x;
			dot[i].y = y;
 		}

		qsort(dot, numOfDot, sizeof(Dot), cmpX);//ascending order by x

		float minDis = closetPair(dot, 0, numOfDot-1);
		if (minDis > 10000)
			printf("Infinity\n");
		else
			printf("%0.2f\n", minDis);
	}
	
}
int cmpY(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->x > d2->x) return 1;
	return -1;
}
int cmpX(const void* a, const void* b) {
	Dot* d1 = (Dot*)a;
	Dot* d2 = (Dot*)b;

	if (d1->y > d2->y) return 1;
	return -1;
}
float closetPair(Dot* dot, int s, int l) {
	printf("==============[s:%d][l:%d]==============\n", s, l);
	if (l-s == 0) {//one dot
		printf("s - l == 0\n");
		return 0;
	}
	else if (l - s == 1) {//two dot
		printf("s - l == 1 : distance = %f\n", distance(dot[s], dot[s+1]));
		return distance(dot[s], dot[s+1]);
	}
	else if (l-s== 2) {//three dot
		
		float minDis = min(distance(dot[s], dot[s+1]), distance(dot[s], dot[s+2]));
		printf("s - l == 2  : distance = %f\n", min(minDis, distance(dot[s], dot[s+2])));
		return min(minDis, distance(dot[s], dot[s+2]));
	}
	//four~
	int mid = (s+l) / 2;
	float ds = closetPair(dot, s, mid);
	float dl = closetPair(dot, mid+1, l);
	float d = min(ds, dl);
	
	Dot S[15];
	int s_head = 0;
	for (int i = s; i <= l; i++) {
		if (dot[mid].x - d <= dot[i].x && dot[i].x <= dot[mid].x + d)
			S[s_head++] = dot[i];
	}
	qsort(S, s_head, sizeof(Dot), cmpY);//ascending order by Y
	float minDis = d;
	for (int i = 0; i < s_head; i++) {
		for (int k = 1; k <= 7; k++) {
			if (i + k >= s_head)
				break;
			float d = distance(S[i], S[i + k]);
			if (minDis > d)
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
	return a;
}