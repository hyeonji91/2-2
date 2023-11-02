#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Vertex {
	float x;
	float y;
};
typedef struct DataSet {
	Vertex v;
	Vertex w;
	float weight;
};


void main() {
	int numOfData;
	Vertex vertex[30];
	int visit[30] = { 0, };
	float x, y;
	int numOfDataSet, dataSetCount = 0;
	int vIdx, wIdx;

	do {
		printf("Enter num of data (0<n<30): ");
		scanf("%d", &numOfData);
	} while (numOfData <= 0 || numOfData >= 30);

	printf("Enter data x, y\n");
	for (int i = 0; i < numOfData; i++) {
		printf("[%d] ", i);
		scanf("%d %d", &x, &y);
		vertex[i].x = x;
		vertex[i].y = y;
		visit[i] = i;
	}

	numOfDataSet = (numOfData * (numOfData - 1)) / 2;
	DataSet* dataSet = (DataSet*)malloc(sizeof(DataSet) * numOfDataSet);
	for (int vIdx = 0; vIdx < numOfData-1; vIdx++) {
		for (int wIdx = vIdx + 1; wIdx < numOfData; wIdx++) {
			dataSet[dataSetCount].v = vertex[vIdx];
			dataSet[dataSetCount].w = vertex[wIdx];
			dataSet[dataSetCount].weight = sqrt(pow(vertex[vIdx].x - vertex[wIdx].x, 2) + pow(vertex[vIdx].y - vertex[wIdx].y, 2));
			dataSetCount++;
		}
	}



}