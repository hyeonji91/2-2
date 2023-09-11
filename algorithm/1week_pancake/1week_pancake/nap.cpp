#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
	int scheduleNum; //일정 개수
	//char startAt[100][6];//
	//char endAt[100][6];
	char scheduleTitle[100][256] = { "", };//일정 이름


	int startAtSplit[100][2];//시작 시각 index: 0 = hour, 1 = minutes
	int endAtSplit[100][2];//종료 시각 index: 0 = hour, 1 = minutes

	//계산을 위해 분으로 포맷
	int startFormatTime[100];
	int endFormatTime[100];

	int napTime;//낮잠시간
	int maxNapTime = 0;//최대 낮잠 시간
	int maxNapHour;//최대 낮잠 시간을 hour, minutes으로 분리
	int maxNapMin;
	int maxNapIndex = 0;

	//스케줄 개수 입력받기
	do {
		printf("Enter your schedule number(<100) : \n");
		scanf("%d", &scheduleNum);

	} while (scheduleNum >= 100 || scheduleNum <= 0); //스케줄 개수가 조건에 맞을때만 다음으로 넘어가기

	for (int i = 0; i < scheduleNum; i++) {//스케줄 입력받기
		do {
			printf("schedule #%d (All times will be greater than or equal 10:00 and less than or equal to 18:00:\n", i);
			scanf("%d:%d %d:%d ", &startAtSplit[i][0], &startAtSplit[i][1], &endAtSplit[i][0], &endAtSplit[i][1]);
			gets_s(scheduleTitle[i]);
		//계산을 위해 분으로 포맷
		startFormatTime[i] = startAtSplit[i][0] * 60 + startAtSplit[i][1];
		endFormatTime[i] = endAtSplit[i][0] * 60 + endAtSplit[i][1];
		} while (startFormatTime[i] < 600 || (endFormatTime[i] > 1800));//입력 시간이 10:00 ~ 18:00
	}

	for (int i = 1; i < scheduleNum; i++) {//최대 낮잠 시간&그때의 index 구하기
		napTime = startFormatTime[i] - endFormatTime[i - 1];
		if (maxNapTime < napTime)
		{
			maxNapTime = napTime;
			maxNapIndex = i;
		}
	}

	maxNapHour = maxNapTime / 60;
	maxNapMin = maxNapTime % 60;

	if(maxNapTime >= 60)//maxNapTime이 1시간 넘어갈때
		printf("the longest nap starts at %02d:%02d and will last for %d hours and %d minutes", endAtSplit[maxNapIndex - 1][0], endAtSplit[maxNapIndex - 1][1], maxNapHour, maxNapMin);
	else
		printf("the longest nap starts at %02d:%02d and will last for %d minutes", endAtSplit[maxNapIndex - 1][0], endAtSplit[maxNapIndex - 1][1], maxNapMin);

}