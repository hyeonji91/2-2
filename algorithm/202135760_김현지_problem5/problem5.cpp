#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define X_MAXLEN 10001 //�ִ� 10000��
#define Z_MAXLEN 101 //�ִ� 100��

int dynamic_programming(char[], char[]);

void main() {
	int num;
	char x[X_MAXLEN];
	char z[Z_MAXLEN];

	scanf("%d", &num);
	int* output = (int*)malloc(sizeof(int*) * num); //�����
	memset(output, 0, sizeof(int) * num); //����� �ʱ�ȭ

	int xIsLower = true; //x�� lowercase�� �̷���� ������ true, �ƴϸ� false
	int zIsLower = true; //z�� lowercase�� �̷���� ������ true, �ƴϸ� false
	for (int i = 0; i < num; i++) {
		do {
			printf("[#%d] Enter lowercase alpahbetic characters: \n", i);
			scanf("%s", &x);
			scanf("%s", &z);
			xIsLower = true;
			zIsLower = true;
			for (int stringIndex = 0; stringIndex < strlen(x); stringIndex++) {
				if (isupper(x[stringIndex]))//x�� uppercase�� ������ xIsLower�� false�Ҵ�
					xIsLower = false;
			}
			for (int stringIndex = 0; stringIndex < strlen(z); stringIndex++) {
				if (isupper(z[stringIndex]))//z�� uppercase�� ������ zIsLower�� false�Ҵ�
					zIsLower = false;
			}
		} while (!(xIsLower && zIsLower));//z, x�� upppercase�� �ִٸ� �ٽ� �Է¹ޱ�
		output[i] = dynamic_programming(x, z);
	}


	//���
	for (int i = 0; i < num; i++) {
		printf("%d\n", output[i]);
	}

}

int dynamic_programming(char x[], char z[]) {
	int width = strlen(x) + 1; //x ���ڼ� ��ŭ table �� ����� + ù��°�� �� �� �߰�
	int height = strlen(z) + 1; //z ���ڼ� ��ŭ table �� ����� + ù��°�� �� �� �߰�

	int** table = (int**)malloc(sizeof(int*) * height);//table �� �����
	for (int index = 0; index < strlen(z) + 1; index++) {
		table[index] = (int*)malloc(sizeof(int) * width);//table �� �����
	}

	int i = 0;
	int j = 0;
	//ù��° �� 1�� �ʱ�ȭ, ù��° �� 0���� �ʱ�ȭ
	for (j = 0; j < width; j++) {
		table[0][j] = 1;
	}
	for (i = 1; i < height; i++)
		table[i][0] = 0;

	
	for (i = 1; i < height; i++) {
		for (j = 1; j < width; j++) {
			if (x[j - 1] == z[i - 1]) {//������ ǥ [����+���� �밢�� ��] �� ��������
				table[i][j] = table[i][j - 1] + table[i - 1][j - 1];
			}
			else//Ʋ���� ǥ ���ʿ��� �� ��������
				table[i][j] = table[i][j - 1];
		}
	}

	int result = table[height - 1][width - 1];

	//�����Ҵ� ����
	for (int index = 0; index < height; index++) {
		free(table[index]);
	}
	free(table);

	return result;


}