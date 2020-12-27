// file: schedule_manager.c

#define _CRT_SECURE_NO_WARNINGS		//scanf() ���� ����
#include <stdio.h>		//ǥ�� ����� �۾��� ���� �������
#include <string.h>		//���ڿ��� �ٷ�� ���� �������

#define MAX_NUM 100		//���� �ִ� 100������ ���� ����

struct when		//��¥�� ��Ÿ���� ������ ����� ��Ÿ���� ����ü
{
	char year[80];
	char month[80];
	char date[80];
};

struct time		//�ð��� ��Ÿ���� ������ ����� ��Ÿ���� ����ü
{
	char hour[80];
	char minute[80];
};

struct memo		//��ҿ� �� ���� ��Ÿ���� ������ ����� ������ ����ü
{
	char place[80];
	char todo[80];
};

struct schedule		// [1] ����ü�� ����� ������ ����ü
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
	sche schedule[MAX_NUM]; // [2] ����ü �迭
	static int cnt = 0; // [4] ���� ���� ����

	openFile(schedule, &cnt);

	while (1) {

		// [5] ����� ģȭ�� �������̽�
		printf("|-------------------------------------------------------|\n");
		printf("|  SUN  |  MON  |  TUE  |  WED  |  THU  |  FRI  |  SAT  |\n");
		printf("|-------------------------------------------------------|\n\n");
		printf("|  �� ���� �߰�\n				 \t\t\t|\n");
		printf("|  �� ���� ����\n				 \t\t\t|\n");
		printf("|  �� ���� �˻�\n				 \t\t\t|\n");
		printf("|  �� ���� ����\n				 \t\t\t|\n");
		printf("|  �� ���� ���\n				 \t\t\t|\n");
		printf("|  ������ �� ����\n				 \t\t\t|\n");
		printf("|-------------------------------------------------------|\n\n");

		printf("���Ͻô� ����� ��ȣ�� �Է��ϼ���: ");
		scanf("%d", &input);

		if (input == 1) {
			printf("\n[ ���� �߰� ] \n");
			insert(schedule, &cnt);
		}

		else if (input == 2) {
			printf("\n[ ���� ���� ] \n");
			adjust(schedule, &cnt);
		}

		else if (input == 3) {
			printf("\n[ ���� �˻� ] \n");
			search(schedule, &cnt);
		}

		else if (input == 4) {
			printf("\n[ ���� ���� ] \n");
			deleted(schedule, &cnt);
		}

		else if (input == 5) {
			printf("\n[ ���� ��� ��� ] \n");
			printAll(schedule, &cnt);
		}
		else if (input == 6) {
			saveFile(schedule, &cnt);
			return 0;
		}
		else
			printf("\n�ش�Ǵ� ��ȣ�� �Է��ϼ���.(1~6) \n\n");
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
			fprintf(fp, " %s�� %s�� %s��\n %s�� %s�� \n ���: %s\n �� ��: %s\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date, ptr[i].t.hour, ptr[i].t.minute, ptr[i].m.place, ptr[i].m.todo);
			fputc('\n', fp);
		}

		state = fclose(fp);
		if (state != 0) {
			printf("File Close Error!\n");
			return 1;
		}
		printf("\n  ������ ����Ǿ����ϴ�. \n");
		return 0;
	}

	else {
		printf("\n  �����մϴ�. \n");
		return 0;
	}
}

int openFile(sche* ptr, int* num) {
	int state;
	FILE* fp = fopen("schedule.txt", "rt");

	if (fp == NULL) {
		printf("\n��ϵ� ������ �����ϴ� >> \n\n");
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

		printf("\n��¥�� �Է��ϼ���.(YYYY MM DD): ");
		scanf(" %s %s %s", ptr[*num].w.year, ptr[*num].w.month, ptr[*num].w.date);
		printf("�ð��� �Է��ϼ���.(HH MM): ");
		scanf(" %s %s", ptr[*num].t.hour, ptr[*num].t.minute);
		printf("��Ҹ� �Է��ϼ���.(���� X): ");
		scanf(" %s", ptr[*num].m.place);
		printf("������ �Է��ϼ���.(���� X): ");
		scanf(" %s", ptr[*num].m.todo);

		(*num)++;
		printf("\n������ �߰��Ǿ����ϴ�.\n\n");
	}

	else
		printf("\n������ �� �̻� �߰��� �� �����ϴ�.\n\n");
}

int adjust(sche* ptr, int* num) {

	char todo[80];
	int i, j;

	if (*num > 0) {
		printf("\n������ ������ �Է��ϼ���: ");
		scanf(" %s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (strcmp(todo, ptr[i].m.todo) == 0) {

				(*num)--;
				printf("\n�ش� ������ ��ü ������ �����Ǿ����ϴ�.\n\n<< ���� �߰��� ������ �Է��ϼ��� >>\n\n");

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
				printf(" ��¥�� �Է��ϼ���.(YYYY MM DD) : ");
				scanf(" %s %s %s", ptr[*num].w.year, ptr[*num].w.month, ptr[*num].w.date);
				printf(" �ð��� �Է��ϼ���.(HH MM) : ");
				scanf(" %s %s", ptr[*num].t.hour, ptr[*num].t.minute);
				printf(" ��Ҹ� �Է��ϼ���.(����X) : ");
				scanf(" %s", ptr[*num].m.place);
				printf(" ������ �Է��ϼ���.(����X) : ");
				scanf(" %s", ptr[*num].m.todo);

				(*num)++;
				printf("\n ������ �����Ǿ����ϴ�. \n\n");
				return 0;
			}
		}
		printf("\n\n �ش� ������ �������� �ʽ��ϴ�. \n\n");
		return 0;
	}

	else {
		printf("\n������ �����ϴ�. \n\n");
		return 0;
	}
}

int search(sche* ptr, int* num) {
	char todo[80];
	int i;

	if (*num > 0) {
		printf("\n������ �Է��ϼ���: ");
		scanf(" %s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (!strcmp(todo, ptr[i].m.todo)) {

				printf("\n��¥ : %s�� %s�� %s��\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date);
				printf("�ð� : %s�� %s��\n", ptr[i].t.hour, ptr[i].t.minute);
				printf("��� : %s\n", ptr[i].m.place);
				printf("���� : %s\n", ptr[i].m.todo);

				printf("\n������ �˻��Ǿ����ϴ�.\n\n");
				return 0;
			}
		}
		printf("\n�������� �ʴ� �����Դϴ�.\n\n");
		return 0;
	}

	else {
		printf("\n������ �����ϴ�.\n\n");
		return 0;
	}
}

int deleted(sche* ptr, int* num) {
	char todo[80];
	int i, j;

	if (*num > 0) {
		printf("\n������ �Է��ϼ���: ");
		scanf("%s", todo);

		for (i = 0; i < MAX_NUM; i++) {

			if (strcmp(todo, ptr[i].m.todo) == 0) {

				(*num)--;
				printf("\n������ �����Ǿ����ϴ�.\n\n");

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
		printf("\n�ش��ϴ� ������ �����ϴ�. \n\n");
		return 0;
	}

	else {
		printf("\n������ �����ϴ�. \n\n");
		return 0;
	}
}

void printAll(sche* ptr, int* num) {
	int i = 0;

	if (*num > 0) {
		for (i = 0; i < *num; i++) {
			// [5] ����� ģȭ�� �������̽�
			printf("\n��¥ : %s�� %s�� %s��\n", ptr[i].w.year, ptr[i].w.month, ptr[i].w.date);
			printf("�ð� : %s�� %s��\n", ptr[i].t.hour, ptr[i].t.minute);
			printf("��� : %s\n", ptr[i].m.place);
			printf("���� : %s\n", ptr[i].m.todo);
		}
		printf("\n������ ��µǾ����ϴ�.\n\n");
	}
	else
		printf("\n������ �����ϴ�.\n\n");
}