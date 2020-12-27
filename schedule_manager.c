// file: schedule_manager.c

#define _CRT_SECURE_NO_WARNINGS		//scanf() 오류 방지
#include <stdio.h>		//표준 입출력 작업을 위한 헤더파일
#include <string.h>		//문자열을 다루기 위한 헤더파일

#define MAX_NUM 100		//일정 최대 100개까지 저장 가능

struct when		//날짜를 나타내는 변수를 멤버로 나타내는 구조체
{
	char year[80];
	char month[80];
	char date[80];
};

struct time		//시간을 나타내는 변수를 멤버로 나타내는 구조체
{
	char hour[80];
	char minute[80];
};

struct memo		//장소와 할 일을 나타내는 변수를 멤버로 가지는 구조체
{
	char place[80];
	char todo[80];
};

struct schedule		// [1] 구조체를 멤버로 가지는 구조체
{
	struct when w;
	struct time t;
	struct memo m;
};
typedef struct schedule sche;

int saveFile(sche* ptr, int* num);
int openFile(sche* ptr, int* num);
void insert(sche* ptr, int* num);
int adjust(sche* ptr, int* num);
int search(sche* ptr, int* num);
int deleted(sche* ptr, int* num);
void printAll(sche* ptr, int* num);

int main(void) {
	int input;
	sche schedule[MAX_NUM]; // [2] 구조체 배열
	static int cnt = 0; // [4] 정적 변수 선언

	openFile(schedule, &cnt);

	while (1) {

		// [5] 사용자 친화적 인터페이스
		printf("|-------------------------------------------------------|\n");
		printf("|  SUN  |  MON  |  TUE  |  WED  |  THU  |  FRI  |  SAT  |\n");
		printf("|-------------------------------------------------------|\n\n");
		printf("|  ① 일정 추가\n				 \t\t\t|\n");
		printf("|  ② 일정 수정\n				 \t\t\t|\n");
		printf("|  ③ 일정 검색\n				 \t\t\t|\n");
		printf("|  ④ 일정 삭제\n				 \t\t\t|\n");
		printf("|  ⑤ 일정 출력\n				 \t\t\t|\n");
		printf("|  ⑥저장 및 종료\n				 \t\t\t|\n");
		printf("|-------------------------------------------------------|\n\n");

		printf("원하시는 기능의 번호를 입력하세요: ");
		scanf("%d", &input);

		if (input == 1) {
			printf("\n[ 일정 추가 ] \n");
			insert(schedule, &cnt);
		}

		else if (input == 2) {
			printf("\n[ 일정 수정 ] \n");
			adjust(schedule, &cnt);
		}

		else if (input == 3) {
			printf("\n[ 일정 검색 ] \n");
			search(schedule, &cnt);
		}

		else if (input == 4) {
			printf("\n[ 일정 삭제 ] \n");
			deleted(schedule, &cnt);
		}

		else if (input == 5) {
			printf("\n[ 일정 모두 출력 ] \n");
			printAll(schedule, &cnt);
		}
		else if (input == 6) {
			saveFile(schedule, &cnt);
			return 0;
		}
		else
			printf("\n해당되는 번호를 입력하세요.(1~6) \n\n");
	}

	return 0;
}


int saveFile(sche* ptr, int* num) {

	if (*num > 0) {
		int i, state;
		FILE* fp = fopen("schedule.txt", "wt");

		if (fp == NULL) {
			printf("File Open Error!\n");
			return 1;
		}

		for (i = 0; i < *num; i++) {
			fprintf(fp, " %s년 %s월 %s일\n %s시 %s분 \n 장소: %s\n 할 일: %s\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date, ptr[i].t.hour, ptr[i].t.minute, ptr[i].m.place, ptr[i].m.todo);
			fputc('\n', fp);
		}

		state = fclose(fp);
		if (state != 0) {
			printf("File Close Error!\n");
			return 1;
		}
		printf("\n  일정이 저장되었습니다. \n");
		return 0;
	}

	else {
		printf("\n  종료합니다. \n");
		return 0;
	}
}

int openFile(sche* ptr, int* num) {
	int state;
	FILE* fp = fopen("schedule.txt", "rt");

	if (fp == NULL) {
		printf("\n등록된 일정이 없습니다 >> \n\n");
		return 1;
	}

	while (1) {
		fscanf(fp, " %s %s %s %s %s %s %s", ptr[*num].w.year, ptr[*num].w.month, ptr[*num].w.date, ptr[*num].t.hour, ptr[*num].t.minute, ptr[*num].m.place, ptr[*num].m.todo);
		if (feof(fp) != 0)
			break;
		(*num)++;
	}

	state = fclose(fp);
	if (state != 0) {
		printf("File Close Error!\n");
		return 1;
	}

	return 0;
}

void insert(sche* ptr, int* num) {

	if (*num < MAX_NUM) {

		printf("\n날짜를 입력하세요.(YYYY MM DD): ");
		scanf(" %s %s %s", ptr[*num].w.year, ptr[*num].w.month, ptr[*num].w.date);
		printf("시간을 입력하세요.(HH MM): ");
		scanf(" %s %s", ptr[*num].t.hour, ptr[*num].t.minute);
		printf("장소를 입력하세요.(띄어쓰기 X): ");
		scanf(" %s", ptr[*num].m.place);
		printf("일정을 입력하세요.(띄어쓰기 X): ");
		scanf(" %s", ptr[*num].m.todo);

		(*num)++;
		printf("\n일정이 추가되었습니다.\n\n");
	}

	else
		printf("\n일정을 더 이상 추가할 수 없습니다.\n\n");
}

int adjust(sche* ptr, int* num) {

	char todo[80];
	int i, j;

	if (*num > 0) {
		printf("\n수정할 일정을 입력하세요: ");
		scanf(" %s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (strcmp(todo, ptr[i].m.todo) == 0) {

				(*num)--;
				printf("\n해당 일정의 전체 내용이 삭제되었습니다.\n\n<< 새로 추가할 내용을 입력하세요 >>\n\n");

				if (i != MAX_NUM - 1) {
					for (j = i; j < MAX_NUM; j++) {

						strcpy(ptr[j].w.year, ptr[j + 1].w.year);
						strcpy(ptr[j].w.month, ptr[j + 1].w.month);
						strcpy(ptr[j].w.date, ptr[j + 1].w.date);
						strcpy(ptr[j].t.hour, ptr[j + 1].t.hour);
						strcpy(ptr[j].t.minute, ptr[j + 1].t.minute);
						strcpy(ptr[j].m.place, ptr[j + 1].m.place);
						strcpy(ptr[j].m.todo, ptr[j + 1].m.todo);
					}

					*ptr[MAX_NUM - 1].w.year = NULL;
					*ptr[MAX_NUM - 1].w.month = NULL;
					*ptr[MAX_NUM - 1].w.date = NULL;
					*ptr[MAX_NUM - 1].t.hour = NULL;
					*ptr[MAX_NUM - 1].t.minute = NULL;
					*ptr[MAX_NUM - 1].m.place = NULL;
					*ptr[MAX_NUM - 1].m.todo = NULL;
				}

				else {

					*ptr[MAX_NUM - 1].w.year = NULL;
					*ptr[MAX_NUM - 1].w.month = NULL;
					*ptr[MAX_NUM - 1].w.date = NULL;
					*ptr[MAX_NUM - 1].t.hour = NULL;
					*ptr[MAX_NUM - 1].t.minute = NULL;
					*ptr[MAX_NUM - 1].m.place = NULL;
					*ptr[MAX_NUM - 1].m.todo = NULL;
				}
				printf(" 날짜를 입력하세요.(YYYY MM DD) : ");
				scanf(" %s %s %s", ptr[*num].w.year, ptr[*num].w.month, ptr[*num].w.date);
				printf(" 시간을 입력하세요.(HH MM) : ");
				scanf(" %s %s", ptr[*num].t.hour, ptr[*num].t.minute);
				printf(" 장소를 입력하세요.(띄어쓰기X) : ");
				scanf(" %s", ptr[*num].m.place);
				printf(" 일정을 입력하세요.(띄어쓰기X) : ");
				scanf(" %s", ptr[*num].m.todo);

				(*num)++;
				printf("\n 일정이 수정되었습니다. \n\n");
				return 0;
			}
		}
		printf("\n\n 해당 일정이 존재하지 않습니다. \n\n");
		return 0;
	}

	else {
		printf("\n정보가 없습니다. \n\n");
		return 0;
	}
}

int search(sche* ptr, int* num) {
	char todo[80];
	int i;

	if (*num > 0) {
		printf("\n일정을 입력하세요: ");
		scanf(" %s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (!strcmp(todo, ptr[i].m.todo)) {

				printf("\n날짜 : %s년 %s월 %s일\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date);
				printf("시간 : %s시 %s분\n", ptr[i].t.hour, ptr[i].t.minute);
				printf("장소 : %s\n", ptr[i].m.place);
				printf("일정 : %s\n", ptr[i].m.todo);

				printf("\n일정이 검색되었습니다.\n\n");
				return 0;
			}
		}
		printf("\n존재하지 않는 일정입니다.\n\n");
		return 0;
	}

	else {
		printf("\n일정이 없습니다.\n\n");
		return 0;
	}
}

int deleted(sche* ptr, int* num) {
	char todo[80];
	int i, j;

	if (*num > 0) {
		printf("\n일정을 입력하세요: ");
		scanf("%s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (strcmp(todo, ptr[i].m.todo) == 0) {

				(*num)--;
				printf("\n일정이 삭제되었습니다.\n\n");

				if (i != MAX_NUM - 1) {

					for (j = i; j < MAX_NUM; j++) {

						strcpy(ptr[j].m.todo, ptr[j + 1].m.todo);
						strcpy(ptr[j].m.todo, ptr[j + 1].m.todo);
					}

					*ptr[MAX_NUM - 1].m.todo = NULL;
					*ptr[MAX_NUM - 1].m.todo = NULL;
				}

				else {

					*ptr[MAX_NUM - 1].m.todo = NULL;
					*ptr[MAX_NUM - 1].m.todo = NULL;
				}
				return 0;
			}
		}
		printf("\n해당하는 일정이 없습니다. \n\n");
		return 0;
	}

	else {
		printf("\n정보가 없습니다. \n\n");
		return 0;
	}
}

void printAll(sche* ptr, int* num) {
	int i = 0;

	if (*num > 0) {
		for (i = 0; i < *num; i++) {
			// [5] 사용자 친화적 인터페이스
			printf("\n날짜 : %s년 %s월 %s일\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date);
			printf("시간 : %s시 %s분\n", ptr[i].t.hour, ptr[i].t.minute);
			printf("장소 : %s\n", ptr[i].m.place);
			printf("일정 : %s\n", ptr[i].m.todo);
		}
		printf("\n일정이 출력되었습니다.\n\n");
	}
	else
		printf("\n일정이 없습니다.\n\n");
}