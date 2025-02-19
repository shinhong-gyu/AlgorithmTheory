#pragma once

#include <Windows.h>
#include "Node.h"

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// ��� �˻� �Լ�
	bool Find(int data, Node** outNode);

	// ��� ���� �Լ�
	bool Insert(int data);

	// ��� ��� �Լ�
	void Print(int depth = 0, int blackCount = 0);

	// ��� ���� �Լ�
	void Remove(int data);

private:
	// ��� ���� �Լ�
	Node* CreateNode(int data, Color color);

	// ��� ��� �˻� �Լ�
	bool FindRecursive(Node* node, Node** outNode, int data);

	// ��� ���� �Լ� (�� ��� ����)
	void Insert(Node* newNode);

	// Ʈ���� ��带 �߰��ϴ� ����Լ�
	void InsertRecursive(Node* node, Node* newNode);

	// ��� ���� �� �������� ó���ϴ� �Լ�
	void RestructureAfterInsert(Node* newNode);

	// Ʈ������ �ּڰ��� ã�� �Լ�
	Node* FindMinRecursive(Node* node);

	// Ʈ������ �ִ��� ã�� �Լ�
	Node* FindMaxRecursive(Node* node);

	// ��� ���� �Լ�
	void RemoveImpl(Node* node);

	// ��� ���� �� ������ �Լ�
	void RestructureAfterRemove(Node* newNode);

	// ��ȸ�� �Լ�
	// node : ȸ���� ������ (pivot)
	void RotateToLeft(Node* pivot);

	//��ȸ�� �Լ�
	// node : ȸ���� ������ (pivot)
	void RotateToRight(Node* pivot);

	// ���� �Լ�
	void DestroyRecursive(Node* node);

	// ��� �Լ�
	void PrintRecursive(Node* node, int depth, int blackCount);

private:
	// ��Ʈ ���
	Node* root = nullptr;

	// Nil ���
	static Node* nil;
};

enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

// �ܼ� �ؽ�Ʈ ���� ���� �Լ�.
void SetTextColor(TextColor color);
