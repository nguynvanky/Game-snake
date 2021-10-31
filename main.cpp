#include <iostream>
#include <stdio.h>
#include "Windows.h"
#include <conio.h>
using namespace std;
#define Width   50
#define Height  22
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
enum  Status
{
	DOWN, UP, LEFT, RIGHT
};

struct ToaDo {
	int x;
	int y;
};
struct Snake {
	int n = 3;
	ToaDo* Dodai = new ToaDo[31];
	Status tt = RIGHT;
};
struct Fruit {
	ToaDo TD;
};
int score = 0;
int speed;
Snake snake;
Fruit fruit;
void Map()
{
	TextColor(2);
	gotoxy(Width + 1, 0);
	cout << "1. Cham bien la thua" << endl;
	gotoxy(Width + 1, 1);
	cout << "2. Can trung nguoi la thua" << endl;
	gotoxy(Width + 1, 2);
	cout << "3. 30 diem la thang" << endl;
	gotoxy(Width + 1, 3);
	cout << "4. Nhan P de Pause." << endl;
	TextColor(7);
	TextColor(6);
	gotoxy(0, 0);
	cout << static_cast <char>(218);
	for (int i = 1; i < Width; i++)
	{
		gotoxy(i, 0);
		cout << static_cast <char>(196);
	}
	gotoxy(Width, 0);
	cout << static_cast <char>(191);
	for (int i = 1; i < Height - 1; i++)
	{
		gotoxy(Width, i);
		cout << static_cast <char>(179);
	}
	gotoxy(Width, Height - 1);
	cout << static_cast <char>(217);
	for (int i = 1; i < Height - 1; i++)
	{
		gotoxy(0, i);
		cout << static_cast <char>(179);
	}
	gotoxy(0, Height - 1);
	cout << static_cast <char>(192);
	for (int i = 1; i < Width; i++)
	{
		gotoxy(i, Height - 1);
		cout << static_cast <char>(196);
	}
	gotoxy(15, Height - 1);
	cout << "W,A,S,D de di chuyen";
	gotoxy(18, 0);
	cout << "Score : " << score << " ";
	TextColor(7);
}
void Ran()
{
	snake.Dodai[2].x = 3;
	snake.Dodai[2].y = 3;
	snake.Dodai[1].x = 4;
	snake.Dodai[1].y = 3;
	snake.Dodai[0].x = 5;
	snake.Dodai[0].y = 3;
}
void HoaQua()
{
	srand((int)time(0));
	fruit.TD.x = (rand() % 37) + 2;
	fruit.TD.y = (rand() % 18) + 2;
}
void VeSnake()
{
	for (int i = 0; i < snake.n; i++)
	{
		gotoxy(snake.Dodai[i].x, snake.Dodai[i].y);
		TextColor(i + 1);
		cout << static_cast <char>(248);
	}
	TextColor(7);
}
void Creat_Fruit()
{
	gotoxy(fruit.TD.x, fruit.TD.y);
	TextColor(4);
	cout << static_cast <char>(15);
	TextColor(7);
}
void Move()
{
	if (snake.tt == UP)
		snake.Dodai[0].y--;
	else if (snake.tt == DOWN)
		snake.Dodai[0].y++;
	else if (snake.tt == LEFT)
		snake.Dodai[0].x--;
	else if (snake.tt == RIGHT)
		snake.Dodai[0].x++;
}
void Control()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a' :
		case 'A' :
			snake.tt = LEFT;
			break;
		case 'd':
		case 'D':
			snake.tt = RIGHT;
			break;
		case 's':
		case 'S':
			snake.tt = DOWN;
			break;
		case 'w':
		case 'W':
			snake.tt = UP;
			break;
		case 'p':
		case 'P':
			gotoxy(Height + 1, 10);
			system("pause");
			break;
		
		}
	}
}
void Update()
{
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.Dodai[i] = snake.Dodai[i - 1];
	}
	if (snake.Dodai[0].x == fruit.TD.x && snake.Dodai[0].y == fruit.TD.y)
	{
		srand((int)time(0));
		HoaQua();
		snake.n++;
		score++;
	}
}
bool Win_Lose()
{
	if (snake.Dodai[0].y == 0)
	{
		return true;
	}
	else if (snake.Dodai[0].y == Height)
	{
		return true;
	}
	else if (snake.Dodai[0].x == 0)
	{
		return true;
	}
	else if (snake.Dodai[0].x == Width)
	{
		return true;
	}
	for (int i = 1; i < snake.n; i++)
	{
		if (snake.Dodai[0].x == snake.Dodai[i].x && snake.Dodai[0].y == snake.Dodai[i].y)
			return true;
	}
	if (score == 30)
		return false;
}
void Win()
{
	gotoxy(Width + 2, Height / 2);

	cout << "Ban da thang ";
	cout << "Voi so diem : " << score << endl;
	Map();
	gotoxy(Width + 2, Height / 2 + 1);

}
void Lose()
{
	gotoxy(Width + 2, Height / 2);
	cout << "Ban da thua" << endl;
	Map();
	gotoxy(Width + 2, Height / 2 + 1);

}

int main()
{
	cout << " Speed 10 - 200: ";
	cin >> speed;
	Ran();
	HoaQua();
	while (true)
	{
		clrscr();
		Map();
		VeSnake();
		Creat_Fruit();
		Update();
		Control();
		Move();
		if (Win_Lose() == true)
		{
			Lose();
			break;
		}
		if (Win_Lose() == false)
		{
			Win();
			break;
		}
		Sleep(speed); // Dung 1 nhip game
	}
	system("pause");
	return 0;
}