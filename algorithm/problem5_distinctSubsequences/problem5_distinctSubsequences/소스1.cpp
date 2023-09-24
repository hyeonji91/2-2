//dynamic programming�� �ƴϷ�

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define X_MAXLEN 10000
#define Z_MAXLEN 100

typedef struct {
	char key;//Ÿ�� ��
	int sameKeyIndex[10000];
	int len; //���� �� ����
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
	//int sameCharIndex[Z_MAXLEN][X_MAXLEN];//���������ϰ� -1�� �ʱ�ȭ
	int index = 0;

	
	//z�� x�� ���� �ܾ��� x�� �ε��� ����
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