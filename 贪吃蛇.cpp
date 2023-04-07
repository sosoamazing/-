#include<iostream>
#include<time.h>
#include<cstdlib>
#include<conio.h>
#include<vector>
using namespace std;
class board {
public:
	char Map[21][21];
	int n;
	board()
	{
		n = 20;
		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				
				Map[i][j] = ' ';
			}
		}
		for (int i = 0; i <= 20; i++)Map[0][i] = Map[20][i] = '#';
		for (int i = 0; i <= 20; i++)Map[i][0] = Map[i][20] = '#';
		food();
	}
	void food()
	{
		srand((unsigned)time(NULL));
		int a = 1, b = 1;
		while (Map[a][b] != ' ')
		{
			a = rand() % n;
			b = rand() % n;
			if (a == 0)a++;
			if (b == 0)b++;
		}
		Map[a][b] = '$';
	}
};
class snake :public board
{
public:
	vector<pair<int, int>> body;
	int score, speed, length, tail;
	snake()
	{
		system("cls");
		length = 5; tail = 0;
		score = 0; speed = 500;
		for (int i = 1; i < 5; i++)
		{
			body.push_back({ 1,i });
			Map[1][i] = '*';
		}
		body.push_back({ 1,5 });
		Map[1][5] = '@';
		cout << "the game is about to begin !!!" << endl;
		int start = clock();
		while (clock() - start <= 1000);
		system("cls");
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				cout << Map[i][j];
			}cout << endl;
		}
	}
	void move()
	{
		int  x = 0, y = 5, direction = 77, t = 0;
		for (;;)
		{
			int start = clock(); 
			bool timeover = true;
			while (!_kbhit() && timeover) {
				timeover = (clock() - start <= speed);
			}
			if (timeover)
			{
				direction = _getch();
				direction = _getch();
			}
			switch (direction)
			{
			case 72:x = body.back().first - 1; y = body.back().second; break;
			case 80:x = body.back().first + 1; y = body.back().second; break;
			case 75:x = body.back().first; y = body.back().second - 1; break;
			case 77:x = body.back().first; y = body.back().second + 1; break;
			}
			x = (x + n) % n; y = (y + n) % n;
			if (x == 0)x++;
			if (y == 0)y++;
			if (Map[x][y] == '*')
			{
				cout << endl;
				cout << "game is over ,and your score is " << score;
				while (clock() - start <= 1000);
				system("cls");
				return;
			}
			if (Map[x][y] == ' ')
			{
				Map[body[tail].first][body[tail].second] = ' ';
				tail++;
			}
			else if (Map[x][y] == '$')
			{
				food(); score += 100; length++;
				if (length >= 8)
				{
					speed -= 50;
					length -= 8;
				}
			}
			Map[body.back().first][body.back().second] = '*';
			Map[x][y] = '@';body.push_back({ x,y });
			system("cls");
			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
					cout << Map[i][j];
				}cout << endl;
			}
		}
	}
};
int main()
{
	snake s;
	s.move();
	return 0;
	
}