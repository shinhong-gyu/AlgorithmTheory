#include <iostream>
#include <vector>

#include "AStar.h"
#include "Node.h"

int main()
{
	// �׸��� ����.
	// 0: �̵� ����.
	// 1: �̵� �Ұ�(��ֹ�).
	// 2: ���� ��ġ.
	// 3: ��ǥ ��ġ.
	std::vector<std::vector<int>> grid =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	// �ʿ��� ���� ��ġ ��ǥ ��ġ �˻�.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;

	bool initialized = false;
	for (int y = 0; y < (int)grid.size(); ++y)
	{
		// �̹� ã������ ����.
		if (startNode && goalNode)
		{
			initialized = true;
			break;
		}

		for (int x = 0; x < (int)grid[0].size(); ++x)
		{
			// �̹� ã������ ����.
			if (startNode && goalNode)
			{
				initialized = true;
				break;
			}

			// ���� ����.
			if (grid[y][x] == 2)
			{
				startNode = new Node(x, y);
				grid[y][x] = 0;
				continue;
			}

			if (grid[y][x] == 3)
			{
				goalNode = new Node(x, y);
				grid[y][x] = 0;
				continue;
			}
		}
	}

	// AStar ��ü.
	AStar aStar;

	// ��� Ž��.
	std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

	// ��� Ȯ��.
	if (!path.empty())
	{
		std::cout << "��θ� ã�ҽ��ϴ�. Ž�� ���: \n";
		for (Node* node : path)
		{
			std::cout
				<< "(" << node->position.x
				<< ","
				<< node->position.y << ") -> ";
		}
		std::cout << "����\n";

		// �� ���.
		std::cout << "��θ� �ʿ� ǥ���� ���: \n";
		aStar.DisplayGridWithPath(grid, path);
	}
	else
	{
		std::cout << "��θ� ã�� ���߽��ϴ�.\n";
	}

	// ��ǥ ��常 ����.
	SafeDelete(goalNode);
}