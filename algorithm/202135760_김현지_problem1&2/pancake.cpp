#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pancakeCnt; //�Է°� ����
int flipIndex[60]; //flip�� ��ġ index�� ������� ����
int flipCnt = 0;//flip Ƚ��

int* pancake(int*, int);//������ũ �˰���
int* flip(int[], int);//flip
int findMax(int[], int);//max�� ã�Ƽ� �� index�� ��ȯ
void printData(int[]);//��ü ����Ʈ

void main() {
	int data[30];//�Է°�
	int* result;//�����
	
	int temp;//�Է°� �ӽ� ����
	int i = 0;

	//�Է�
	printf("enter pancake(end: -1):");
	for (i = 0; i < 30; i++) {
		scanf_s("%d", &temp);
		if (temp == -1)
			break;
		else
			data[i] = temp;
	}

	pancakeCnt = i;

	result=pancake(data, i-1);

	//���� ��
	printData(data);

	//�����
	printf("( ");
	printData(result);
	printf(")\n");

	//flip��ġ
	int j = -1;
	do{
		printf("%d ", flipIndex[++j]);
	} while (flipIndex[j] != 0);



}

int* pancake(int* data, int currentIndex) {//������ũ �˰���: data = �Է°�, currentIndex = ���� ������ ��ġ
	

	if (currentIndex <= 0)//���� ����
		return data;

	int maxIndex= findMax(data, currentIndex);//0-currentIndex���� max�� ã��
	
	if (maxIndex != currentIndex) {//max�� �̹� �� �ڿ� ������ �� �� �ѱ��
		if (maxIndex != 0) {//max�� ó���� ��ġ�Ѵٸ� ù��° flip �ѱ��
			data = flip(data, maxIndex);//0-maxIndex���� flip => max�� ó������ �̵�

			flipIndex[flipCnt++] = pancakeCnt - maxIndex;
			//printf("============flip1=============\n");
			//printData(data);
		}

		data = flip(data, currentIndex);//0-currentIndex���� flip => max�� ���������� �̵�
		flipIndex[flipCnt++] = pancakeCnt - currentIndex;
		//printf("============flip2=============\n");
		//printData(data);
	}
	else
		currentIndex = currentIndex - 1;

	pancake(data, currentIndex - 1); //currentIndex-1: �̹� ���ĵ� max�����ϰ� �ٽ� �ݺ� 
}

int findMax(int data[], int currentIndex) {
	int max =0;
	int maxIndex = 0;
	for (int i = 0; i <= currentIndex; i++) {
		if (max < data[i]) {
			max = data[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

int* flip(int data[], int currentIndex) {
	int* filpData = (int*)malloc(sizeof(int) * pancakeCnt);//�����Ҵ�
	memset(filpData, 0, currentIndex * sizeof(int));//�ʱ�ȭ

	for (int i = 0; i <= currentIndex; i++) {//flip
		filpData[i] = data[currentIndex - i];
	}
	for (int j = currentIndex + 1; j < pancakeCnt; j++) {//�̹� ���ĵ� �κ� �״�� �����ֱ�
		filpData[j] = data[j];
	}

	return filpData;
	free(filpData);
}

void printData(int data[]) {
	for (int i = 0; i < pancakeCnt; i++) {
		printf("%d ", data[i]);
	}
	//printf("\n");
}