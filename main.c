#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include"list.h"

#define N 2	//关卡数目
#define M N*50	//地图大小	M*M
int level = 0;//游戏次数
int map[M + 1][M + 1] = { 0 };
//int 25;//地图大小
int my_x, my_y;//我的位置
int step = 0;
int time_test = 0;
char c;
char line[1024] = { 0 };
char str[2 * (M + 1) * (M + 1)] = { '\0' };
//
int score_time1 = 0;
int score_time2 = 0;
//计分
FILE* fp;

void Initialize();//初始化地图
void printmap();//打印函数
void find();//找到自己
int move();//控制移动
int Up();//上移
int Down();//下移
int Right();//右移
int Left();//左移
void menu();//菜单，选择难度和大小
int IsHaveNeighbor(int X_index, int Y_index);//判断当前方块处是否有邻居
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
			if (map[i][j] == 6)//还存在蓝色方块
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
				//如果目前剩余1个蓝色方块
				if (flag == 1)
					rand_point = 0;
				else
					rand_point = rand() % flag;//2个   0  1	随机一个小于flag的数，用于随机选取蓝色方块
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
				if (map[x + 1][y] == 5)//往上
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
				else if (map[x - 1][y] == 5)//向下
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
				else if (map[x][y + 1] == 5)//向左
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
				else if (map[x][y - 1] == 5)//向右
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
	for (i = 0;i < 25;i++)	//通过后将地图初始化成全0的
		for (j = 0;j < 25;j++)
			map[i][j] = 0;
	//将所需地图以外的初始化为空白,其余空地和墙壁间隔
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
//打印函数
void printmap()
{
	gotoxy(0, 0);//清屏
	int i = 0, j = 0;
	str[0] = '\0';
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			if (map[i][j] == 0)
			{
				strcat(str, "■");
			}
			//printf("■");
			else if (map[i][j] == -1)
				break;
			else if (map[i][j] == 1)
			{
				strcat(str, "  ");
			}
			//printf("  ");
			else if (map[i][j] == 3)
			{
				strcat(str, "⊙");
			}
			//	printf("⊙");
			else if (map[i][j] == 4)
			{
				strcat(str, "☆");
			}
			//	printf("☆");
			else if (map[i][j] == 5)
			{
				strcat(str, "◇");
			}
			//	printf("◇");
			else if (map[i][j] == 6)
			{
				strcat(str, "○");
			}
			//	printf("○");
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
	printf("按Esc键返回菜单");
}
int move()
{
	int flag = 0;
	printmap();
	flag = 0;
	find();


	while (kbhit()) {
		switch (getch())//接收按键输入
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
			//通过		
			level++;
			read_line(&list_p, read(time_test / 2000));
			fprintf(fp, "第%d次 用时%d秒\n", level, time_test/2000);
			time_test = 0;
			step = 0;
			flag = 0;
			MessageBox(0, TEXT("恭喜你通过了这一难度"), TEXT("恭喜"), NULL);
			Initialize();
			printmap();
		}
	}


}
int Up()
{
	if (my_x != 0)
	{
		if (map[my_x - 1][my_y] == 1)//可走
		{
			map[my_x - 1][my_y] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//行走成功
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
		if (map[my_x + 1][my_y] == 1)//可走
		{
			map[my_x + 1][my_y] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//行走成功
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
		if (map[my_x][my_y + 1] == 1)//可走
		{
			map[my_x][my_y + 1] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//行走成功
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
		if (map[my_x][my_y - 1] == 1)//可走
		{
			map[my_x][my_y - 1] = 3;
			map[my_x][my_y] = 1;
			step++;
			return 2;//行走成功
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
	printf("分别用wasd控制人物移动\n");
	printf("开始新游戏请输入1\n");
	printf("查看排行榜请输入2\n");
	printf("查看历史记录请输入3\n");
	printf("退出游戏请输入0\n");
	printf("请输入指令：");
	while (1)
	{
		scanf("%s", input);
		if (strlen(input) > 1)
		{
			printf("错误输入，请重新输入：\n");
		}
		else {
			if (input[0] == '1') {
				start();
				break;
			}
			else if (input[0] == '2') {
				system("cls");
				M_SetCursor(0, 12);
				printf("输入ESC返回上一界面\n");
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
					switch (getch())//接收按键输入
					{
					case 27:system("cls");
						menu();

					}
				}
				break;
			}
			else
				printf("输入错误，请重新输入\n");
		}
	}
	system("cls");
}

void gotoxy(int x, int y)//每次刷新屏幕
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//第二个值为0表示隐藏光标
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
	printf("分数排行：\n");
	for (i = 0;i < 10;i++) {
		if (i < 9)
			printf("第%d名   %d秒\n", i + 1, score[i]);
		if (i >= 9)
			printf("第%d名  %d秒\n", i + 1, score[i]);
	}
	while (!kbhit()) {
		switch (getch())//接收按键输入
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
	//	//文件读取结束
	//	if (EOF == fscanf(fp, "%s", line))
	//		break;
	//	printf("%s\n", line);
	//}
	rewind(fp);
	char a[100];
	//从文件中读取数据，保存到boyb
	fscanf(fp, "%s", &a);
	printf("%s", a);
	fclose(fp);
}