#pragma once

#include <iostream>
#include <string>


// 메모리 삭제 함수
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

// 노드 색상 열거형
enum class Color
{
	Red,
	Black,
};

class Node
{
public:
	//생성자
	Node(int data = 0, Color color = Color::Red);
	~Node() = default;


	// Getter/Setter.
	inline int Data() const { return data; }
	inline void SetData(int newData) { data = newData; }

	// 데이터 
	int data = 0;

	// 색상
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

	// 오른쪽 자식 노드
	Node* rightChild = nullptr;

	// 왼쪽 자식 노드
	Node* leftChild = nullptr;

	// 부모 노드
	Node* parent = nullptr;


};