#include <stack>
#include <vector>
#include <iostream>

struct Location2D
{
	Location2D(int row = 0, int col = 0) :row(row), col(col) {};


	int row = 0;

	int col = 0;
};

const int mapSize = 6;

std::vector<std::vector<char>> map
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

bool IsValidLocation(int row, int col)
{
	if (row >= mapSize || col >= mapSize || row <= 0 || col <= 0)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

// ������ ���� �˻� �Լ�.
void FindStartLocation(int& row, int& col)
{
	for (int i = 0; i < mapSize; ++i)
	{
		for (int j = 0; j < mapSize; ++j)
		{
			if (map[i][j] == 'e')
			{
				row = i;
				col = j;
				return;
			}
		}
		std::cout << "\n";
	}
}


int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

// �̷� Ż�� �Լ�
void EscapeMaze()
{
	int row = 0;
	int col = 0;

	FindStartLocation(row, col);

	std::stack<Location2D> s;

	s.push({ row,col });

	while (!s.empty())
	{
		Location2D curLoc = s.top();
		s.pop();

		std::cout << "(" << curLoc.row << "," << curLoc.col << ")" << std::endl;

		for (int i = 0; i < 4; i++)
		{
			int ny = curLoc.row + dy[i];
			int nx = curLoc.col + dx[i];


			if (IsValidLocation(ny, nx) && map[ny][nx] != '.')
			{
				if (map[ny][nx] == 'x')
				{
					std::cout << "�̷�Ž������" << std::endl;
					return;
				}

				s.push({ ny,nx });
				// �湮�� ���� ��ġ�� ��湮 ������ ���� ǥ��
				map[ny][nx] = '.';
			}
		}
	}
	std::cout << "�̷�Ž�� ����\n";
}

int main()
{
	EscapeMaze();

	std::cin.get();
}