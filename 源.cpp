#include"stdafx.h" //置顶，加目录
#include<conio.h>
#include<mmsystem.h>
#include<Windows.h>
#pragma comment(lib, "winmm.lib")
#include <graphics.h> 
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<resource.h>

int map[10][8] = {
	1,1,1,1,1,1,1,1,
	1,0,0,5,0,0,1,1,
	1,0,4,0,4,0,0,1,
	1,0,0,4,0,4,0,1,
	1,1,1,4,1,1,1,1,
	1,0,3,0,3,3,1,1,
	1,0,0,0,0,0,1,1,
	1,0,0,1,0,3,1,1,
	1,0,0,3,0,0,1,1,
	1,1,1,1,1,1,1,1
};
IMAGE backImage;  //背景

IMAGE Wall;       //墙

IMAGE People;//人物
IMAGE kongdi;
IMAGE Box;      //箱子

IMAGE Boom;     //箱子+目的地
IMAGE over;
IMAGE Destination; //目的地
//加载图片
//
void zuihou()
{

	initgraph(640,400);
	loadimage(&over, "JPG", MAKEINTRESOURCE(IDB_BITMAP7));
	putimage(0, 0, &over);
	MessageBox(GetHWnd(), "你再一次打败了猪", "BOB", MB_OK);
	getchar();
}
void gamejiazai()
{
	loadimage(&Wall, "JPG", MAKEINTRESOURCE(IDB_BITMAP4));//墙
	loadimage(&People, "JPG", MAKEINTRESOURCE(IDB_BITMAP3));//ren
	loadimage(&Box,"JPG", MAKEINTRESOURCE(IDB_BITMAP5));//箱子
	loadimage(&Boom, "JPG", MAKEINTRESOURCE(IDB_BITMAP1));//箱子+mudi
	loadimage(&Destination, "JPG", MAKEINTRESOURCE(IDB_BITMAP2));//目的
	loadimage(&backImage, "JPG", MAKEINTRESOURCE(IDB_BITMAP7));//结束
	loadimage(&kongdi, "JPG", MAKEINTRESOURCE(IDB_BITMAP6));//结束
}
void gamepaint()
{
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (map[j][i])
			{
			case 0:putimage(i * 45, j * 45, &kongdi); break;
			case 1:putimage(i * 45, j * 45, &Wall); break;
			case 3:putimage(i * 45, j * 45, &Destination); break;
			case 4:putimage(i * 45, j * 45, &Box); break;
			case 5:putimage(i * 45, j * 45, &People); break;
			case 7:putimage(i * 45, j * 45, &Boom); break;
			case 8:putimage(i * 45, j * 45, &People); break;
			}
		}
	}
}
int GameWin()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == 4)
			{
				return 1;
			}
		}
	}
	return 0;
}
void gameplay()
{
	char c;
	int x, y;
	BeginBatchDraw();
	while (1)
	{
		if (!GameWin())
		{
			gamejiazai();
			FlushBatchDraw();
			break;
		}
		cleardevice();
		gamepaint();
		FlushBatchDraw();
		for (x = 0; x < 10; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if (map[x][y] == 5 || map[x][y] == 8)
					break;
			}
			if (map[x][y] == 5 || map[x][y] == 8)
				break;
		}
		c = _getch();
		switch (c)
		{
		case 'w':case 'W':case '72':
			if (map[x - 1][y] == 0 || map[x - 1][y] == 3)
			{
				map[x][y] -= 5;
				map[x - 1][y] += 5;
			}
			else if (map[x - 1][y] == 4 || map[x - 1][y] == 7)
			{
				if (map[x - 2][y] == 0 || map[x - 2][y] == 3)
				{
					map[x - 2][y] += 4;
					map[x - 1][y] += 1;
					map[x][y] -= 5;
				}
			}
			break;
		case  80:
		case 'S':
		case 's':
			if (map[x + 1][y] == 0 || map[x + 1][y] == 3)
			{
				map[x][y] -= 5;
				map[x + 1][y] += 5;
			}

			else if (map[x + 1][y] == 4 || map[x + 1][y] == 7)
			{
				if (map[x + 2][y] == 0 || map[x + 2][y] == 3)
				{
					map[x + 2][y] += 4;
					map[x + 1][y] += 1;
					map[x][y] -= 5;
				}
			}
			break;

		case 75:
		case 'a':
		case 'A':
			if (map[x][y - 1] == 0 || map[x][y - 1] == 3)
			{
				map[x][y] -= 5;
				map[x][y - 1] += 5;
			}

			else if (map[x][y - 1] == 4 || map[x][y - 1] == 7)
			{
				if (map[x][y - 2] == 0 || map[x][y - 2] == 3)
				{
					map[x][y - 2] += 4;
					map[x][y - 1] += 1;
					map[x][y] -= 5;
				}
			}
			break;
		case 77:
		case 'd':
		case 'D':
			if (map[x][y + 1] == 0 || map[x][y + 1] == 3)
			{
				map[x][y] -= 5;
				map[x][y + 1] += 5;
			}

			else if (map[x][y + 1] == 4 || map[x][y + 1] == 7)
			{
				if (map[x][y + 2] == 0 || map[x][y + 2] == 3)
				{
					map[x][y + 2] += 4;
					map[x][y + 1] += 1;
					map[x][y] -= 5;
				}
			}
			break;
		}
	}
	EndBatchDraw();
	gamepaint();
	Sleep(3000);
	zuihou();
}
		
int main()
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	initgraph(45*8, 45*10);
	
	gamejiazai();
	gamepaint();
	gameplay();
	while (1); 
	return 0;
	
}