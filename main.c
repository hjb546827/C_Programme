#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include"list.h"

#define N 2	//�ؿ���Ŀ
#define M N*50	//��ͼ��С	M*M
int level = 0;//��Ϸ����
int map[M + 1][M + 1] = { 0 };
//int 25;//��ͼ��С
int my_x, my_y;//�ҵ�λ��
int step = 0;
int time_test = 0;
char c;
char line[1024] = { 0 };
char str[2 * (M + 1) * (M + 1)] = { '\0' };
//
int score_time1 = 0;
int score_time2 = 0;
//�Ʒ�
FILE* fp;

void Initialize();//��ʼ����ͼ
void printmap();//��ӡ����
void find();//�ҵ��Լ�
int move();//�����ƶ�
int Up();//����
int Down();//����
int Right();//����
int Left();//����
void menu();//�˵���ѡ���ѶȺʹ�С
int IsHaveNeighbor(int X_index, int Y_index);//�жϵ�ǰ���鴦�Ƿ����ھ�
void Creat_02_Change(int X_index, int Y_index);
void Creat_02(int X_index, int Y_index);//
void gotoxy(int x, int y);
void HideCursor();
void M_SetCursor(int x, int y);
void phb();
void start();
int comp2(const void* i, const void* j);
void read_txt();

list* list_p = NULL;
int main(void)
{
	HideCursor();	
	fp = fopen("score.txt", "a+");
	system("color 0A");
	menu();
	//fprintf(fp, "\n");
	//fputs("\n", fp);
	fclose(fp);
	return 0;
}
int IsHaveNeighbor(int X_index, int Y_index)
{
	int i, j, flag = 0;

	for (i = 0;i < 25;i++)
	{
		for (j = 0;j < 25;j++)
		{
			if (map[i][j] == 6)//��������ɫ����
			{
				flag++;
			}

		}
	}
	return flag;

}

void Creat_02_Change(int X_index, int Y_index)
{
	if (X_index > 1 && map[X_index - 1][Y_index] == 0)
		map[X_index - 1][Y_index] = 6;
	if (Y_index > 1 && map[X_index][Y_index - 1] == 0)
		map[X_index][Y_index - 1] = 6;
	if (X_index < 25 - 2 && map[X_index + 1][Y_index] == 0)
		map[X_index + 1][Y_index] = 6;
	if (Y_index < 25 - 2 && map[X_index][Y_index + 1] == 0)
		map[X_index][Y_index + 1] = 6;

}
void Creat_02(int X_index, int Y_index)
{
	int rand_point, x = 1, y = 2, flag = 0, i, j;
	while (1)
	{
		flag = IsHaveNeighbor(X_index, Y_index);
		if (flag == 0)
			return;
		else
		{
			while (1)
			{
				//���Ŀǰʣ��1����ɫ����
				if (flag == 1)
					rand_point = 0;
				else
					rand_point = rand() % flag;//2��   0  1	���һ��С��flag�������������ѡȡ��ɫ����
											   //printmap();
				for (i = 0;i < 25;i++)
				{
					for (j = 0;j < 25;j++)
					{
						if (map[i][j] == 6 && rand_point == 0)
						{
							x = i;
							y = j;
							break;
						}
						else if (map[i][j] == 6)
							rand_point--;
					}
					if (map[i][j] == 6 && rand_point == 0)
						break;
				}
				if (map[x + 1][y] == 5)//����
				{
					if (map[x - 1][y] == 1)
					{
						map[x - 1][y] = 5;
						map[x][y] = 5;
						x = x - 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x - 1][y] == 5)//����
				{
					if (map[x + 1][y] == 1)
					{
						map[x + 1][y] = 5;
						map[x][y] = 5;
						x = x + 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x][y + 1] == 5)//����
				{
					if (map[x][y - 1] == 1)
					{
						map[x][y - 1] = 5;
						map[x][y] = 5;
						y = y - 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x][y - 1] == 5)//����
				{
					if (map[x][y + 1] == 1)
					{
						map[x][y + 1] = 5;
						map[x][y] = 5;
						y = y + 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				Creat_02_Change(x, y);
				X_index = x;
				Y_index = y;
				break;
			}
		}
	}
}
void Initialize()
{
	int i, j;
	for (i = 0;i < 25;i++)	//ͨ���󽫵�ͼ��ʼ����ȫ0��
		for (j = 0;j < 25;j++)
			map[i][j] = 0;
	//�������ͼ����ĳ�ʼ��Ϊ�հ�,����յغ�ǽ�ڼ��
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			if (i >= 25 || j >= 25)
				map[i][j] = -1;
			else if (i != 0 && j != 0 && i != 24 && j != 24)
			{
				if (i % 2 != 0)
					if (j % 2 == 1)
						map[i][j] = 1;
			}
		}
	}
	map[1][1] = 5;
	map[1][2] = 6;
	map[2][1] = 6;
	Creat_02(1, 1);
	for (i = 0;i < 25;i++)
	{
		for (j = 0;j < 25;j++)
			if (map[i][j] == 5)
				map[i][j] = 1;
	}
	map[1][1] = 3;
	map[23][23] = 4;
}
//��ӡ����
void printmap()
{
	gotoxy(0, 0);//����
	int i = 0, j = 0;
	str[0] = '\0';
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			if (map[i][j] == 0)
			{
				strcat(str, "��");
			}
			//printf("��");
			else if (map[i][j] == -1)
				break;
			else if (map[i][j] == 1)
			{
				strcat(str, "  ");
			}
			//printf("  ");
			else if (map[i][j] == 3)
			{
				strcat(str, "��");
			}
			//	printf("��");
			else if (map[i][j] == 4)
			{
				strcat(str, "��");
			}
			//	printf("��");
			else if (map[i][j] == 5)
			{
				strcat(str, "��");
			}
			//	printf("��");
			else if (map[i][j] == 6)
			{
				strcat(str, "��");
			}
			//	printf("��");
		}
		if (map[i][0] != -1)
			strcat(str, "\n");
		//printf("\n");
	}
	printf("%s", str);
	M_SetCursor(60, 1);
	printf("Time: %d s", time_test / 2000);
	M_SetCursor(60, 2);
	printf("Step: %d in total", step);
	M_SetCursor(60, 3);
	printf("��Esc�����ز˵�");
}
int move()
{
	int flag = 0;
	printmap();
	flag = 0;
	find();


	while (kbhit()) {
		switch (getch())//���հ�������
		{
		case 'w':flag = Up();break;
		case 'a':flag = Left();break;
		case 's':flag = Down();break;
		case 'd':flag = Right();break;
		case 27:system("cls");
			time_test = 0;
			step = 0;
			menu();

		}
		if (flag == 2)
			printmap();
		else if (flag == 1)
		{
			//ͨ��		
			level++;
			read_line(&list_p, read(time_test / 2000));
			fprintf(fp, "��%d�� ��ʱ%d��\n", level, time_test/2000);
			time_test = 0;
			step = 0;
			flag = 0;
			MessageBox(0, TEXT("��ϲ��ͨ������һ�Ѷ�"), TEXT("��ϲ"), NULL);
			Initialize();
			printmap();
		}
	}


}
int Up()
{
	if (my_x != 0)
	{
		if (map[my_x - 1][my_y] == 1)//����
		{
			map[my_x - 1][my_y] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//���߳ɹ�
		}
		else if (map[my_x - 1][my_y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Down()
{
	if (my_x != 25 - 1)
	{
		if (map[my_x + 1][my_y] == 1)//����
		{
			map[my_x + 1][my_y] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//���߳ɹ�
		}
		else if (map[my_x + 1][my_y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Right()
{
	if (my_y != 25 - 1)
	{
		if (map[my_x][my_y + 1] == 1)//����
		{
			map[my_x][my_y + 1] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//���߳ɹ�
		}
		else if (map[my_x][my_y + 1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Left()
{
	if (my_y != 0)
	{
		if (map[my_x][my_y - 1] == 1)//����
		{
			map[my_x][my_y - 1] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//���߳ɹ�
		}
		else if (map[my_x][my_y - 1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
void find()
{
	int i, j;
	for (i = 0;i < 25;i++)
		for (j = 0;j < 25;j++)
		{
			if (map[i][j] == 3)
			{
				my_x = i;
				my_y = j;
			}
		}
}

void menu()
{
	int flag = 0;
	int ch;
	char input[10];
	printf("�ֱ���wasd���������ƶ�\n");
	printf("��ʼ����Ϸ������1\n");
	printf("�鿴���а�������2\n");
	printf("�鿴��ʷ��¼������3\n");
	printf("�˳���Ϸ������0\n");
	printf("������ָ�");
	while (1)
	{
		scanf("%s", input);
		if (strlen(input) > 1)
		{
			printf("�������룬���������룺\n");
		}
		else {
			if (input[0] == '1') {
				start();
				break;
			}
			else if (input[0] == '2') {
				system("cls");
				M_SetCursor(0, 12);
				printf("����ESC������һ����\n");
				M_SetCursor(0, 0);
				phb();
				break;
			}
			else if (input[0] == '0') {
				exit(0);
			}
			else if (input[0] == '3') {
				read_txt();
				//break;
				while (!kbhit()) {
					switch (getch())//���հ�������
					{
					case 27:system("cls");
						menu();

					}
				}
				break;
			}
			else
				printf("�����������������\n");
		}
	}
	system("cls");
}

void gotoxy(int x, int y)//ÿ��ˢ����Ļ
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void M_SetCursor(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

void phb() {
	int score[10] = { 0 };
	int i;
	output(list_p, score);
	qsort(score, 10, sizeof(int), comp2);
	printf("�������У�\n");
	for (i = 0;i < 10;i++) {
		if (i < 9)
			printf("��%d��   %d��\n", i + 1, score[i]);
		if (i >= 9)
			printf("��%d��  %d��\n", i + 1, score[i]);
	}
	while (!kbhit()) {
		switch (getch())//���հ�������
		{
		case 'w': printf("0");break;
		case 27:system("cls");
			time_test = 0;
			step = 0;
			menu();

			//break;
		}
	}
}

void start() {
	int s[100][100] = { 0 };
	srand((unsigned)time(NULL));
	int flag = 0;
	Initialize(25);

	while (1)
	{
		time_test++;
		flag = move();
		if (flag == 1 || flag == -1)
			return 0;

	}

}
comp2(const void* i, const void* j)
{
	return *(const int*)j - *(const int*)i;
}

void read_txt() {
	system("cls");
	FILE* fp = fopen("score.txt", "r");
	//if (!fp)
	//	return;
	//while (1)
	//{
	//	//�ļ���ȡ����
	//	if (EOF == fscanf(fp, "%s", line))
	//		break;
	//	printf("%s\n", line);
	//}
	rewind(fp);
	char a[100];
	//���ļ��ж�ȡ���ݣ����浽boyb
	fscanf(fp, "%s", &a);
	printf("%s", a);
	fclose(fp);
}