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
	// 시작 지점.
	this->startNode = startNode;

	// 목표 지점
	this->goalNode = goalNode;

	// 시작 위치를 열린 리스트에 추가.
	openList.emplace_back(startNode);

	// 상하좌우 및 대각성 이동 방향 및 비용 계산
	std::vector<Direction> directions = {
		// 하
		{0,1,1.0f},
		// 상
		{0,-1,1.0f},
		// 우
		{1,0,1.0f},
		// 좌
		{-1,0,1.0f},
		// 대각선 이동.
		// 우하
		{1,1,1.414f},
		// 좌하
		{1,-1,1.414f},
		// 우상
		{-1,1,1.414f},
		// 우하
		{-1,-1,1.414f},
	};

	// 이웃 노드 탐색 (열린 리스트가 비어 있지 않으면 반복).
	while (!openList.empty())
	{
		// 현재 열린 리스트에서 비용이 가장 낮은 노드 검색.
		// 최적화 가능 (우선 순위 큐, 힙).
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}
		// 현재 노드를 최소 노드로 설정
		Node* currentNode = lowestNode;

		// 현재 노드가 목표 노드인지 확인.
		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		// 방문 처리를 위해 현재 노드를 열린 릿ㅡ트에서 제거.
		for (int i = 0; i < (int)openList.size(); ++i)
		{
			if (*openList[i] == *currentNode)
			{
				openList.erase(openList.begin() + i);
				break;
			}
		}
		// 방문 처리를 위해 닫힌 리스트에 추가.
	// 이미 추가된 노드는 제외.
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

		// 없으면
		closedList.emplace_back(currentNode);

		// 이웃 노드 방문 (하상우좌.. 차례로 방문)
		for (const Direction& direction : directions)
		{
			// 다음에 이동할 위치 확인.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// 그리드를 벗어나면 무시.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// 이동할 노드가 이동 가능한지 확인.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			// 이미 방문했는지 확인.
			if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
			{
				continue;
			}

			// 방문할 노드 생성 (비용 계산)
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// 열린 리스트에 추가.
			Node* openListNode = nullptr;

			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// 이웃 노드가 리스트에 없으면 바로 추가.
			// 리스트에 있으면 값을 비교해서 더 저렴하면 추가.
			if (openListNode == nullptr || neighborNode->gCost < openListNode->gCost || neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				// 리스트 추가 대상이 아니라면 메모리 해제.
				SafeDelete(neighborNode);
			}
		}
	}


	return {};
}

void AStar::DisplayGridWithPath(
	std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	// 경로에 있는 위치는 2로 표기.
	for (const Node* node : path)
	{
		grid[node->position.y][node->position.x] = 2;
	}

	// 맵 출력.
	for (int y = 0; y < (int)grid.size(); ++y)
	{
		for (int x = 0; x < (int)grid[0].size(); ++x)
		{
			// 장애물.
			if (grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			// 경로.
			else if (grid[y][x] == 2)
			{
				std::cout << "+ ";
			}

			// 맵.
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
	// 현재 노드에서 목표 노드까지의 차이 계산.
	Position diff = *currentNode - *goalNode;

	return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	// x, y 범위가 벗어나면 false 반환.
	if (x < 0 || x >= (int)grid[0].size() || y < 0 || y >= (int)grid.size())
	{
		return false;
	}

	// 벗어나지 않았으면 true 반환.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// 열린/닫힌 리스트에 이미 해당 위치가 있으면 방문한 것으로 판단.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// 위치도 같고, 비용이 더크면 방문할 이유 없음.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// 새 노드의 비용이 작은 경우에는 기존 노드 제거.
			openList.erase(openList.begin() + ix);
			SafeDelete(node);
		}
	}

	for (int ix = 0; ix < (int)closedList.size(); ++ix)
	{
		Node* node = closedList[ix];
		if (node->position.x == x && node->position.y == y)
		{
			// 위치도 같고, 비용이 더크면 방문할 이유 없음.
			if (gCost >= node->gCost)
			{
				return true;
			}

			// 새 노드의 비용이 작은 경우에는 기존 노드 제거.
			closedList.erase(closedList.begin() + ix);
			SafeDelete(node);
		}
	}

	// 리스트에 없으면 방문하지 않은 것으로 판단.
	return false;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}
