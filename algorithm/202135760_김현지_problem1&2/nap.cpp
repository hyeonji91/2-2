#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
	int scheduleNum; //���� ����
	//char startAt[100][6];//
	//char endAt[100][6];
	char scheduleTitle[100][256] = { "", };//���� �̸�


	int startAtSplit[100][2];//���� �ð� index: 0 = hour, 1 = minutes
	int endAtSplit[100][2];//���� �ð� index: 0 = hour, 1 = minutes

	//����� ���� ������ ����
	int startFormatTime[100];
	int endFormatTime[100];

	int napTime;//����ð�
	int maxNapTime = 0;//�ִ� ���� �ð�
	int maxNapHour;//�ִ� ���� �ð��� hour, minutes���� �и�
	int maxNapMin;
	int maxNapIndex = 0;

	//������ ���� �Է¹ޱ�
	do {
		printf("Enter your schedule number(<100) : \n");
		scanf("%d", &scheduleNum);

	} while (scheduleNum >= 100 || scheduleNum <= 0); //������ ������ ���ǿ� �������� �������� �Ѿ��

	for (int i = 0; i < scheduleNum; i++) {//������ �Է¹ޱ�
		do {
			printf("schedule #%d (All times will be greater than or equal 10:00 and less than or equal to 18:00:\n", i);
			scanf("%d:%d %d:%d ", &startAtSplit[i][0], &startAtSplit[i][1], &endAtSplit[i][0], &endAtSplit[i][1]);
			gets_s(scheduleTitle[i]);
		//����� ���� ������ ����
		startFormatTime[i] = startAtSplit[i][0] * 60 + startAtSplit[i][1];
		endFormatTime[i] = endAtSplit[i][0] * 60 + endAtSplit[i][1];
		} while (startFormatTime[i] < 600 || (endFormatTime[i] > 1800));//�Է� �ð��� 10:00 ~ 18:00
	}

	for (int i = 1; i < scheduleNum; i++) {//�ִ� ���� �ð�&�׶��� index ���ϱ�
		napTime = startFormatTime[i] - endFormatTime[i - 1];
		if (maxNapTime < napTime)
		{
			maxNapTime = napTime;
			maxNapIndex = i;
		}
	}

	maxNapHour = maxNapTime / 60;
	maxNapMin = maxNapTime % 60;

	if(maxNapTime >= 60)//maxNapTime�� 1�ð� �Ѿ��
		printf("the longest nap starts at %02d:%02d and will last for %d hours and %d minutes", endAtSplit[maxNapIndex - 1][0], endAtSplit[maxNapIndex - 1][1], maxNapHour, maxNapMin);
	else
		printf("the longest nap starts at %02d:%02d and will last for %d minutes", endAtSplit[maxNapIndex - 1][0], endAtSplit[maxNapIndex - 1][1], maxNapMin);

}