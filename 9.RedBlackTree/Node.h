#pragma once

#include <iostream>
#include <string>


// �޸� ���� �Լ�
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

// ��� ���� ������
enum class Color
{
	Red,
	Black,
};

class Node
{
public:
	//������
	Node(int data = 0, Color color = Color::Red);
	~Node() = default;


	// Getter/Setter.
	inline int Data() const { return data; }
	inline void SetData(int newData) { data = newData; }

	// ������ 
	int data = 0;

	// ����
	inline const Color GetColor() const { return color; }
	inline void SetColor(Color newColor) { color = newColor; }
	const char* ColorString() const;


	inline Node* Parent() const { return parent; }
	inline void SetParent(Node* newParent) { parent = newParent; }
	
	
	inline Node* LeftChild() const { return leftChild; }
	inline void SetLeftChild(Node* newChild) { leftChild = newChild; }


	inline Node* RightChild() const { return rightChild; }
	inline void SetRightChild(Node* newChild) { rightChild = newChild; }
private:
	Color color = Color::Red;

	// ������ �ڽ� ���
	Node* rightChild = nullptr;

	// ���� �ڽ� ���
	Node* leftChild = nullptr;

	// �θ� ���
	Node* parent = nullptr;


};