#include "AStar.h"
#include "Node.h"
#include <cmath>


AStar::AStar::AStar() : startNode(nullptr), goalNode(nullptr)
{
}

AStar::AStar::~AStar()
{
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
}

std::vector<Node*> AStar::AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid)
{
	// ���� ����.
	this->startNode = startNode;

	// ��ǥ ����
	this->goalNode = goalNode;

	// ���� ��ġ�� ���� ����Ʈ�� �߰�.
	openList.emplace_back(startNode);

	// �����¿� �� �밢�� �̵� ���� �� ��� ���
	std::vector<Direction> directions = {
		// ��
		{0,1,1.0f},
		// ��
		{0,-1,1.0f},
		// ��
		{1,0,1.0f},
		// ��
		{-1,0,1.0f},
		// �밢�� �̵�.
		// ����
		{1,1,1.414f},
		// ����
		{1,-1,1.414f},
		// ���
		{-1,1,1.414f},
		// ����
		{-1,-1,1.414f},
	};

	// �̿� ��� Ž�� (���� ����Ʈ�� ��� ���� ������ �ݺ�).
	while (!openList.empty())
	{
		// ���� ���� ����Ʈ���� ����� ���� ���� ��� �˻�.
		// ����ȭ ���� (�켱 ���� ť, ��).
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}
		// ���� ��带 �ּ� ���� ����
		Node* currentNode = lowestNode;

		// ���� ��尡 ��ǥ ������� Ȯ��.
		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����.
		for (int i = 0; i < (int)openList.size(); ++i)
		{
			if (*openList[i] == *currentNode)
			{
				openList.erase(openList.begin() + i);
				break;
			}
		}
		// �湮 ó���� ���� ���� ����Ʈ�� �߰�.
	// �̹� �߰��� ���� ����.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList)
		{
			continue;
		}

		// ������
		closedList.emplace_back(currentNode);

		// �̿� ��� �湮 (�ϻ����.. ���ʷ� �湮)
		for (const Direction& direction : directions)
		{
			// ������ �̵��� ��ġ Ȯ��.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// �׸��带 ����� ����.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// �̵��� ��尡 �̵� �������� Ȯ��.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			// �̹� �湮�ߴ��� Ȯ��.
			if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
			{
				continue;
			}

			// �湮�� ��� ���� (��� ���)
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// ���� ����Ʈ�� �߰�.
			Node* openListNode = nullptr;

			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// �̿� ��尡 ����Ʈ�� ������ �ٷ� �߰�.
			// ����Ʈ�� ������ ���� ���ؼ� �� �����ϸ� �߰�.
			if (openListNode == nullptr || neighborNode->gCost < openListNode->gCost || neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				// ����Ʈ �߰� ����� �ƴ϶�� �޸� ����.
				SafeDelete(neighborNode);
			}
		}
	}


	return {};
}

void AStar::DisplayGridWithPath(
	std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	// ��ο� �ִ� ��ġ�� 2�� ǥ��.
	for (const Node* node : path)
	{
		grid[node->position.y][node->position.x] = 2;
	}

	// �� ���.
	for (int y = 0; y < (int)grid.size(); ++y)
	{
		for (int x = 0; x < (int)grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			// ���.
			else if (grid[y][x] == 2)
			{
				std::cout << "+ ";
			}

			// ��.
			else if (grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	std::vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(), path.end());
	return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	// ���� ��忡�� ��ǥ �������� ���� ���.
	Position diff = *currentNode - *goalNode;

	return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	// x, y ������ ����� false ��ȯ.
	if (x < 0 || x >= (int)grid[0].size() || y < 0 || y >= (int)grid.size())
	{
		return false;
	}

	// ����� �ʾ����� true ��ȯ.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ����/���� ����Ʈ�� �̹� �ش� ��ġ�� ������ �湮�� ������ �Ǵ�.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// ��ġ�� ����, ����� ��ũ�� �湮�� ���� ����.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// �� ����� ����� ���� ��쿡�� ���� ��� ����.
			openList.erase(openList.begin() + ix);
			SafeDelete(node);
		}
	}

	for (int ix = 0; ix < (int)closedList.size(); ++ix)
	{
		Node* node = closedList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// ��ġ�� ����, ����� ��ũ�� �湮�� ���� ����.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// �� ����� ����� ���� ��쿡�� ���� ��� ����.
			closedList.erase(closedList.begin() + ix);
			SafeDelete(node);
		}
	}

	// ����Ʈ�� ������ �湮���� ���� ������ �Ǵ�.
	return false;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}
