#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//void sortAscending(Elephant[], int*);
//void sortDescending(Elephant[], int*);

int sortAscending(const void*, const void*);
int sortDescending(const void*, const void*);
int** findResult(int, int);
int backTrace(int**, int*, int*, int, int);

int** weight;
int** iq;
int weightMaxCnt = -1;
int iqMaxCnt = -1;

typedef struct Elephant{
	int index;
	int weight;
	int iq;
};

typedef struct DataStruct{
	int index;
	DataStruct* next;

};

void main() {
	FILE* input;
	Elephant* elephant;
	int numOfInput = 0;
	int arrWidth, arrHeight;

	input = fopen("elephant_input.txt", "r");
	int tempW, tempIq;
	while (fscanf(input, "%d %d", &tempW, &tempIq) != EOF) {
		numOfInput++;
	}
	fclose(input);

	input = fopen("elephant_input.txt", "r");
	elephant = (Elephant*)malloc(sizeof(Elephant) * numOfInput);
	numOfInput = 0;
	while (fscanf(input, "%d %d", &elephant[numOfInput].weight, &elephant[numOfInput].iq) != EOF) {
		elephant[numOfInput].index = numOfInput + 1;
		printf("%d %d %d \n", elephant[numOfInput].weight, elephant[numOfInput].iq, elephant[numOfInput].index);
		numOfInput++;
	}
	fclose(input);






	int sameCnt = 1;
	int preWeight = -1;
	qsort(elephant, numOfInput, sizeof(Elephant), sortAscending);
	for (int i = 0; i < numOfInput; i++) {
		if (elephant[i].weight == preWeight) {
			sameCnt++;
		}
		else
			sameCnt = 1;
		if (weightMaxCnt < sameCnt)
			weightMaxCnt = sameCnt;
		preWeight = elephant[i].weight;
	}
	weight = (int**)malloc(sizeof(int*) * numOfInput);//ascending 으로 sort한 weight 저장
	for (int i = 0; i < numOfInput; i++) {
		weight[i] = (int*)malloc(sizeof(int) * weightMaxCnt);
		memset(weight[i], -1, sizeof(int) * weightMaxCnt);
	}
	preWeight = elephant[0].weight;
	int count = 0;
	for (int i = 0; i < numOfInput; i++) {
		for (int j = 0; j < weightMaxCnt; j++) {
			if (count == numOfInput) {
				arrHeight = i+1;//arr개수는 마지막 인덱스 번호+1
				break;
			}
			if (preWeight != elephant[count].weight)
				break;
			else {
				weight[i][j] = elephant[count].index;
				preWeight = elephant[count].weight;
				count++;
			}

		}
		preWeight = elephant[count].weight;
		if (count == numOfInput) {
			break;
		}
	}

	for (int i = 0; i < numOfInput; i++) {
		for (int j = 0; j < weightMaxCnt; j++) {
			printf("%d | ", weight[i][j]);
		}
		printf("\n");
	}




	qsort(elephant, numOfInput, sizeof(Elephant), sortDescending);
	sameCnt = 1;
	int preIQ = -1;
	for (int i = 0; i < numOfInput; i++) {
		if (elephant[i].iq == preIQ) {
			sameCnt++;
		}
		else
			sameCnt = 1;
		if (iqMaxCnt < sameCnt)
			iqMaxCnt = sameCnt;
		preIQ = elephant[i].iq;
	}
	iq = (int**)malloc(sizeof(int*) * numOfInput);//ascending 으로 sort한 weight 저장
	for (int i = 0; i < numOfInput; i++) {
		iq[i] = (int*)malloc(sizeof(int) * iqMaxCnt);
		memset(iq[i], -1, sizeof(iq[i]));
	}

	preIQ = elephant[0].iq;
	count = 0;

	for (int i = 0; i < numOfInput; i++) {
		for (int j = 0; j < iqMaxCnt; j++) {
			if (count == numOfInput) {
				arrWidth = i+1;//arr개수는 마지막 인덱스 번호+1
				break;
			}
			if (preIQ != elephant[count].iq)
				break;
			else {
				iq[i][j] = elephant[count].index;
				preIQ = elephant[count].iq;
				count++;
			}
		}
		preIQ = elephant[count].iq;
		if (count == numOfInput) {
			break;
		}
	}

	printf("\niq\n");
	for (int i = 0; i < numOfInput; i++) {
		for (int j = 0; j < iqMaxCnt; j++) {
			printf("%d |", iq[i][j]);
		}
		printf("\n");
	}




	int** memo= findResult(arrWidth+1, arrHeight+1);

	int* result;
	int resultCnt = 0;
	if(weightMaxCnt<iqMaxCnt)
		result = (int*)malloc(sizeof(int)*weightMaxCnt);
	else
		result = (int*)malloc(sizeof(int) * iqMaxCnt);
	backTrace(memo, result, &resultCnt, arrWidth, arrHeight);

	printf("%d\n", resultCnt);
	for (int i = 0; i < resultCnt; i++) {
		printf("%d\n", result[resultCnt-1-i]);
	}
	



}

int sortAscending(const void* a, const void* b) {
	Elephant e1 = *(Elephant*)a;
	Elephant e2 = *(Elephant*)b;

	if (e1.weight < e2.weight)
		return -1;//안바꾸기
	else if (e1.weight > e2.weight)
		return 1;//바꾸기
	else 
		return 0;
}

int sortDescending(const void* a, const void* b) {
	Elephant e1 = *(Elephant*)a;
	Elephant e2 = *(Elephant*)b;

	if (e1.iq < e2.iq)
		return 1;
	else if (e1.iq > e2.iq)
		return -1;
	else
		return 0;
}

int** findResult(int dpWidth, int dpHeight) {

	int** memo = (int**)malloc(sizeof(int*) * dpHeight);
	for (int i = 0; i < dpHeight; i++) {
		memo[i] = (int*)malloc(sizeof(int) * dpWidth);
	}
	
	//초기화
	for (int j = 0; j < dpWidth; j++)
		memo[0][j] = 0;

	for (int i = 1; i < dpHeight; i++)
		memo[i][0] = 0;
	
	int wCount;
	int sCount;
	int same = true;
	for (int i = 1; i < dpHeight; i++) {
		for (int j = 1; j < dpWidth; j++) {
			wCount = 0;
			sCount = 0;
			same = false;
			while (wCount<weightMaxCnt && weight[i-1][wCount] != -1) {
				while (sCount < iqMaxCnt && iq[j-1][sCount] != -1) {
					if (weight[i-1][wCount] == iq[j-1][sCount]) {
						same = true;
					}
					sCount++;
				}
				wCount++;
				sCount = 0;
			}

			if (same == true) {
				memo[i][j] = memo[i - 1][j - 1] + 1;
			}
			else if (memo[i - 1][j] > memo[i][j - 1]) {
				memo[i][j] = memo[i - 1][j];
			}
			else {
				memo[i][j] = memo[i][j - 1];
			}
		}
	}

	for (int i = 1; i < dpHeight; i++) {
		for (int j = 1; j < dpWidth; j++) {
			printf("%d |", memo[i][j]);
		}
		printf("\n");
	}

	return memo;
}

int backTrace(int** memo, int* result, int* index, int arrWidth, int arrHeight) {

	if (arrHeight == 0 || arrWidth == 0)
		return 1;

	if (memo[arrHeight - 1][arrWidth] == memo[arrHeight][arrWidth]) {
		arrHeight --;
	}
	else if (memo[arrHeight][arrWidth - 1] == memo[arrHeight][arrWidth])
		arrWidth --;
	else {
		for (int i = 0; i < weightMaxCnt; i++) {
			for (int j = 0; j < iqMaxCnt; j++) {
				if (weight[arrHeight - 1][i] != -1 && weight[arrHeight-1][i] == iq[arrWidth-1][j])
					result[*index] = weight[arrHeight-1][i];
			}
		}
		(*index)++;
		arrWidth --;
		arrHeight --;
	}


	backTrace(memo, result, index, arrWidth, arrHeight);
}