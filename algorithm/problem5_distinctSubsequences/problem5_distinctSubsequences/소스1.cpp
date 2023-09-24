//dynamic programming이 아니래

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define X_MAXLEN 10000
#define Z_MAXLEN 100

typedef struct {
	char key;//타겟 값
	int sameKeyIndex[10000];
	int len; //값은 값 개수
}cell;

cell m[Z_MAXLEN];
int compare_string(char[], char[]);
int cal(int, int, char[]);
int count;

void main() {
	int num;
	char x[X_MAXLEN];
	char z[Z_MAXLEN];

	scanf("%d", &num);
	int* output = (int*)malloc(sizeof(int) * num);
	memset(output, 0, sizeof(int) * num);


	for (int i = 0; i < num; i++) {
		scanf("%s", &x);
		scanf("%s", &z);
		output[i] = compare_string(x, z);
		count = 0;
	}

	for (int i = 0; i < num; i++) {
		printf("%d ", output[i]);
	}

	free(output);
}

int compare_string(char x[], char z[]) {
	//int sameCharIndex[Z_MAXLEN][X_MAXLEN];//동적으로하고 -1로 초기화
	int index = 0;

	
	//z와 x가 같은 단어인 x의 인덱스 저장
	for (int j = 0; j < strlen(z); j++) {
		for (int i = 0; i < strlen(x); i++) {
			if (z[j] == x[i])
				m[j].sameKeyIndex[index++] = i;
		}
		m[j].key = z[j];
		m[j].len = index;
		index = 0;
	}
	
	 
	for (int i = 0; i < m[0].len; i++) {
		cal(0, i, z);
	}

	return count;
}
int cal(int keyIndex, int i, char z[]) {//count <=result, i:sameKeyIndex
	if (keyIndex == strlen(z)-1)
		return count = count + 1;
	

	int curCount = 0;

	for (int j = 0; j < m[keyIndex + 1].len; j++) {
		if (m[keyIndex].sameKeyIndex[i] < m[keyIndex + 1].sameKeyIndex[j])
			cal(keyIndex + 1, j, z);
	}
}