#pragma once

#include <Windows.h>
#include "Node.h"

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// 노드 검색 함수
	bool Find(int data, Node** outNode);

	// 노드 삽입 함수
	bool Insert(int data);

	// 노드 출력 함수
	void Print(int depth = 0, int blackCount = 0);

	// 노드 삭제 함수
	void Remove(int data);

private:
	// 노드 생성 함수
	Node* CreateNode(int data, Color color);

	// 노드 재귀 검색 함수
	bool FindRecursive(Node* node, Node** outNode, int data);

	// 노드 삽입 함수 (새 노드 전달)
	void Insert(Node* newNode);

	// 트리에 노드를 추가하는 재귀함수
	void InsertRecursive(Node* node, Node* newNode);

	// 노드 삽입 후 재정렬을 처리하는 함수
	void RestructureAfterInsert(Node* newNode);

	// 트리에서 최솟값을 찾는 함수
	Node* FindMinRecursive(Node* node);

	// 트리에서 최댓값을 찾는 함수
	Node* FindMaxRecursive(Node* node);

	// 노드 삭제 함수
	void RemoveImpl(Node* node);

	// 노드 삭제 후 재정렬 함수
	void RestructureAfterRemove(Node* newNode);

	// 좌회전 함수
	// node : 회전의 기준점 (pivot)
	void RotateToLeft(Node* pivot);

	//우회전 함수
	// node : 회전의 기준점 (pivot)
	void RotateToRight(Node* pivot);

	// 삭제 함수
	void DestroyRecursive(Node* node);

	// 출력 함수
	void PrintRecursive(Node* node, int depth, int blackCount);

private:
	// 루트 노드
	Node* root = nullptr;

	// Nil 노드
	static Node* nil;
};

enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

// 콘솔 텍스트 색상 설정 함수.
void SetTextColor(TextColor color);
