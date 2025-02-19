#include "RedBlackTree.h"

Node* RedBlackTree::nil = nullptr;

Node* RedBlackTree::CreateNode(int data, Color color = Color::Red)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);
	return newNode;
}



RedBlackTree::RedBlackTree()
{
	if (nil == nullptr)
	{
		nil = new Node(0, Color::Black);
	}

	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	// @Todo : 모든 노드 삭제.
	DestroyRecursive(root);
	SafeDelete(nil);
}

bool RedBlackTree::Find(int data, Node** outNode)
{
	if (root == nil)
	{
		return false;
	}

	return FindRecursive(root, outNode, data);

}

bool RedBlackTree::Insert(int data)
{
	// 트리에 중복되는 데이터가 있는지 확인
	Node* node = nullptr;
	if (Find(data, &node))
	{
		std::cout << "오류 -노드 추가 실패 : 이미 같은 값이 있습니다." << data << "\n";
		return false;
	}

	Insert(CreateNode(data, Color::Red));
	return true;
}



bool RedBlackTree::FindRecursive(Node* node, Node** outNode, int data)
{
	// 재귀 탈출 조건 (검색 실패)
	if (node == nil)
	{
		return false;
	}

	// 검색에 성공했으면 true 및 outNode 반환.
	if (node->Data() == data)
	{
		*outNode = node;
		return true;
	}

	// 검색할 데이터가 노드의 데이터보다 크다면 왼쪽 탐색
	if (node->Data() > data)
	{
		return FindRecursive(node->LeftChild(), outNode, data);
	}
	else
	{
		return FindRecursive(node->RightChild(), outNode, data);
	}

	return false;
}

void RedBlackTree::Insert(Node* newNode)
{
	// 트리가 비어있는 경우
	// 루트로 설정
	if (root == nil)
	{
		newNode->SetColor(Color::Black);
		root = newNode;
		return;
	}

	// 트리가 비어있지 않으면, 재귀적으로 위치 검색 후 삽입.
	InsertRecursive(root, newNode);

	// 삽입된 노드 값 정리.
	newNode->SetColor(Color::Red);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	// 삽입 후 재정렬 처리.
	RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// 새 노드의 데이터가 현재 노드보다 작으면 왼쪽 하위 트리로 삽입 진행.
	if (node->Data() > newNode->Data())
	{
		// 왼쪽 자손이 없다면, 삽입 처리.
		if (node->LeftChild() == nil)
		{
			node->SetLeftChild(newNode);
			newNode->SetParent(node);
			return;
		}

		// 자손이 있다면, 하위 트리로 삽입 과정 진행
		InsertRecursive(node->LeftChild(), newNode);
	}
	else
	{
		// 오른쪽 자손이 없다면, 삽입.
		if (node->RightChild() == nil)
		{
			node->SetRightChild(newNode);
			newNode->SetParent(node);
			return;
		}

		// 자손이 있으면 오른쪽 하위 트리로 삽입 과정 진행
		InsertRecursive(node->RightChild(), newNode);
	}
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// 부모 노드가 빨간색인 경우에는 
	// 빨간색 노드가 연속으로 나올 수 없다는 조건을 
	// 만족하지 않기 때문에 이를 해결하기 위해 재정렬 진행(Case2: Red-Red Conflict).
	while (newNode != root && newNode->Parent()->GetColor() == Color::Red)
	{
		// 해결 방법 (삼촌이 빨간색인 경우/삼촌이 검은색인 경우).
		// 삼촌 구하기 #1: 새 노드의 부모가 조부모의 왼쪽 자손인 경우.
		if (newNode->Parent() == newNode->Parent()->Parent()->LeftChild())
		{
			// 삼촌.
			Node* uncle = newNode->Parent()->Parent()->RightChild();

			// 삼촌 노드가 빨간색일 때.
			// 해결: 부모와 삼촌은 검은색으로 변경하고, 조부모를 빨간색으로 변경해서
			// 문제를 위로 올린다.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// 색상을 변경한 뒤에 위쪽 노드에서도 같은 문제가 발생하지는 않는지 확인.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// 삼촌 노드가 검은색일 때.
			// 해결: 부모, 조부모, 새 노드의 위치에 따라서 회전을 수행.
			// #1: 새 노드가 부모와 반대 위치일 때 -> 부모를 중심으로 1차 회전 후 다시 회전.
			// #2: 새 노드가 부모와 같은 위치일 때 -> 회전 및 색상 재설정을 통해 위치 재정렬.
			else
			{
				// 부모와 반대 위치인 경우 (추가 회전).
				// 부모와 새 노드의 위치를 맞추기 위해.
				if (newNode == newNode->Parent()->RightChild())
				{
					// 부모를 중심으로 회전 진행.
					newNode = newNode->Parent();
					RotateToLeft(newNode);
				}

				// 조부모를 중심으로 회전 및 색상 변경.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RotateToRight(newNode->Parent()->Parent());
			}
		}

		// 삼촌 구하기 #2: 새 노드의 부모가 조부모의 오른쪽 자손인 경우.
		else
		{
			// 삼촌.
			Node* uncle = newNode->Parent()->Parent()->LeftChild();

			// 삼촌 노드가 빨간색일 때.
			// 해결: 부모와 삼촌은 검은색으로 변경하고, 조부모를 빨간색으로 변경해서
			// 문제를 위로 올린다.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// 색상을 변경한 뒤에 위쪽 노드에서도 같은 문제가 발생하지는 않는지 확인.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// 삼촌 노드가 검은색일 때.
			// 해결: 부모, 조부모, 새 노드의 위치에 따라서 회전을 수행.
			// #1: 새 노드가 부모와 반대 위치일 때 -> 부모를 중심으로 1차 회전 후 다시 회전.
			// #2: 새 노드가 부모와 같은 위치일 때 -> 회전 및 색상 재설정을 통해 위치 재정렬.
			else
			{
				// 부모와 반대 위치인 경우 (추가 회전).
				// 부모와 새 노드의 위치를 맞추기 위해.
				if (newNode == newNode->Parent()->LeftChild())
				{
					// 부모를 중심으로 회전 진행.
					newNode = newNode->Parent();
					RotateToRight(newNode);
				}

				// 조부모를 중심으로 회전 및 색상 변경.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RotateToLeft(newNode->Parent()->Parent());
			}
		}
	}

	// 루트 노드를 블랙으로 설정.
	root->SetColor(Color::Black);
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
	if (node == nil)
	{
		return nullptr;
	}

	// 왼쪽 하위 노드가 더 이상 없으면 현재 노드 반환
	if (node->LeftChild() == nil)
	{
		return node;
	}

	return FindMinRecursive(node->LeftChild());

}

Node* RedBlackTree::FindMaxRecursive(Node* node)
{
	if (node == nil)
	{
		return nullptr;
	}

	// 오른쪽 하위 노드가 더 이상 없으면 현재 노드 반환
	if (node->RightChild() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->RightChild());

}

void RedBlackTree::RemoveImpl(Node* node)
{
	// 삭제 대상 노드.
	Node* removed = nullptr;

	// 삭제할 위치의 대체 노드.
	Node* trail = nil;

	Node* target = node;

	// 자손이 하나 이하인 경우.
	if (target->LeftChild() == nil || target->RightChild() == nil)
	{
		removed = target;
	}

	// 자손이 모두 있는 경우.
	else
	{
		// 대체할 노드 검색.
		// (왼쪽 하위 트리에서 가장 큰값을 대체 노드로 설정).
		removed = FindMaxRecursive(target->LeftChild());

		// 대체 노드가 존재하면 해당 데이터 설정.
		//if (removed != nullptr && removed != nil)
		//{
		//    // 현재 노드의 값을 대상 노드의 값으로 변경.
		//    target->SetData(removed->Data());
		//}

		// 현재 노드의 값을 대상 노드의 값으로 변경.
		target->SetData(removed->Data());
	}

	// 자손이 하나만 있을 때.
	if (node->LeftChild() != nil && node->RightChild() == nil)
	{
		trail = node->LeftChild();
	}
	else if (node->RightChild() != nil && node->LeftChild() == nil)
	{
		trail = node->RightChild();
	}

	// 대상 노드가 있는 경우.
	if (trail != nil /*&& trail != nullptr*/)
	{
		trail->SetParent(removed->Parent());
	}

	// removed 노드가 root인 경우.
	if (removed->Parent() == nullptr)
	{
		root = trail;
	}
	// root가 아닐 때.
	else
	{
		// trail 노드를 removed의 원래 위치로 설정.
		if (removed == removed->Parent()->LeftChild())
		{
			removed->Parent()->SetLeftChild(trail);
		}
		else
		{
			removed->Parent()->SetRightChild(trail);
		}
	}

	// 재정렬 여부 확인후 진행.
	if (removed->GetColor() == Color::Black && trail != nil)
	{
		// 재정렬 진행.
	}

	// 노드 삭제.
	SafeDelete(removed);
}

void RedBlackTree::RestructureAfterRemove(Node* newNode)
{
	// 더블 블랙 문제 해결
	while (newNode->Parent() != nullptr && newNode->GetColor() == Color::Black)
	{
		if (newNode == newNode->Parent()->LeftChild())
		{
			Node* sibling = newNode->Parent()->RightChild();
			if (sibling == nil)
			{
				break;
			}

			// case 1 : 형제 노드가 빨간색.
			// 해결 : 형제 노드를 Black으로 변경하고
			// 부모를 Red로 바꾼 후 부모 기준으로 좌회전 또는 우회전
			if (sibling->GetColor() == Color::Red)
			{
				sibling->SetColor(Color::Black);
				newNode->Parent()->SetColor(Color::Red);

				// 좌회전
				RotateToLeft(newNode->Parent());
				continue;
			}

			// case 2  : 형제와 형제 두 자식 모두 검정색일 때.
			// 해결 :
			if (sibling->LeftChild()->GetColor() == Color::Black && sibling->RightChild()->GetColor() == Color::Black)
			{
				sibling->SetColor(Color::Red);
				newNode = newNode->Parent();
				continue;
			}

			// case 3 : 형제 노드 검정. 형제 노드의 왼쪽 자손이 빨간색.
			// 해결 : 형제의 왼쪽 자식을 Black으로 변경.
			// 형제를 Red로 변경 후 형제 기준 우회전
			if (sibling->LeftChild()->GetColor() == Color::Red)
			{
				sibling->LeftChild()->SetColor(Color::Black);
				sibling->SetColor(Color::Red);

				// 우회전
				RotateToRight(sibling);

				// 회전 후 형제 위치 업데이트
				sibling = newNode->Parent()->RightChild();
			}

			// case 4 : 형제 노드는 Black, 형제의 오른쪽 자식이 Red
			// 해결 : 형제를 부모와 같은 색으로 설정,
			// 부모를 Black으로 변경
			// 형제의 오른쪽 자식을 Black으로 변경 후 부모 기준 좌회전.
			if (sibling->RightChild()->GetColor() == Color::Red)
			{
				sibling->SetColor(sibling->Parent()->GetColor());
				sibling->Parent()->SetColor(Color::Black);
				sibling->RightChild()->SetColor(Color::Black);
				RotateToLeft(newNode->Parent());
			}
			continue;
		}
		else
		{
			Node* sibling = newNode->Parent()->LeftChild();
			if (sibling == nil)
			{
				break;
			}

			// case 1 : 형제 노드가 빨간색.
			// 해결 : 형제 노드를 Black으로 변경하고
			// 부모를 Red로 바꾼 후 부모 기준으로 좌회전 또는 우회전
			if (sibling->GetColor() == Color::Red)
			{
				sibling->SetColor(Color::Black);
				newNode->Parent()->SetColor(Color::Red);

				// 우회전
				RotateToRight(newNode->Parent());
				continue;
			}

			// case 2  : 형제와 형제 두 자식 모두 검정색일 때.
			// 해결 :
			if (sibling->RightChild()->GetColor() == Color::Black && sibling->LeftChild()->GetColor() == Color::Black)
			{
				sibling->SetColor(Color::Red);
				newNode = newNode->Parent();
				continue;
			}

			// case 3 : 형제 노드 검정. 형제 노드의 오른쪽 자손이 빨간색.
			// 해결 : 형제의 오른쪽 자식을 Black으로 변경.
			// 형제를 Red로 변경 후 형제 기준 좌회전
			if (sibling->RightChild()->GetColor() == Color::Red)
			{
				sibling->RightChild()->SetColor(Color::Black);
				sibling->SetColor(Color::Red);

				// 좌회저s
				RotateToLeft(sibling);

				// 회전 후 형제 위치 업데이트
				sibling = newNode->Parent()->LeftChild();
			}

			// case 4 : 형제 노드는 Black, 형제의 왼쪽 자식이 Red
			// 해결 : 형제를 부모와 같은 색으로 설정,
			// 부모를 Black으로 변경
			// 형제의 왼쪽 자식을 Black으로 변경 후 부모 기준 우회저ㄴ.
			if (sibling->LeftChild()->GetColor() == Color::Red)
			{
				sibling->SetColor(sibling->Parent()->GetColor());
				sibling->Parent()->SetColor(Color::Black);
				sibling->LeftChild()->SetColor(Color::Black);
				RotateToLeft(newNode->Parent());
			}
			continue;
		}
	}

	// 노드를 검은색으로 설정
	newNode->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* pivot)
{
	// 오른쪽 자식 노드.
	Node* rightChild = pivot->RightChild();

	// 오른쪽 자식 노드의 왼쪽 자식 노드를 부모의 오른쪽 자식으로 등록.
	pivot->SetRightChild(rightChild->LeftChild());

	// 하위 노드의 부모 처리.
	if (rightChild->LeftChild() != nil)
	{
		rightChild->LeftChild()->SetParent(pivot);
	}

	// 오른쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정.
	rightChild->SetParent(pivot->Parent());

	// 부모가 root인 경우
	if (rightChild->Parent() == nullptr)
	{
		root = rightChild;
	}

	// 부모가 root가 아닌 경우
	else
	{
		// 조부모 기준 원래의 자식 위치로 복구
		if (pivot == pivot->Parent()->LeftChild())
		{
			pivot->Parent()->SetLeftChild(rightChild);
		}
		else
		{
			pivot->Parent()->SetRightChild(rightChild);
		}
	}

	// 좌회전 마무리
	rightChild->SetLeftChild(pivot);
	pivot->SetParent(rightChild);
}

void RedBlackTree::RotateToRight(Node* pivot)
{
	// 왼쪽 자식 노드.
	Node* leftChild = pivot->LeftChild();

	// 왼쪽 자식의 오른쪽 자식을 부모의 왼쪽 자식으로 등록
	pivot->SetLeftChild(leftChild->RightChild());

	// 하위 노드의 부모 처리.
	if (leftChild->RightChild() != nil)
	{
		leftChild->RightChild()->SetParent(pivot);
	}

	// 오른쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정.
	leftChild->SetParent(pivot->Parent());

	// 부모가 root인 경우
	if (leftChild->Parent() == nullptr)
	{
		root = leftChild;
	}

	// 부모가 root가 아닌 경우
	else
	{
		// 조부모 기준 원래의 자식 위치로 복구
		if (pivot == pivot->Parent()->LeftChild())
		{
			pivot->Parent()->SetLeftChild(leftChild);
		}
		else
		{
			pivot->Parent()->SetRightChild(leftChild);
		}
	}

	// 좌회전 마무리
	leftChild->SetRightChild(pivot);
	pivot->SetParent(leftChild);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// 재귀 탈출 조건
	if (node == nil)
	{
		return;
	}

	// 왼쪽/오른쪽 자손
	Node* left = node->LeftChild();
	Node* right = node->RightChild();

	DestroyRecursive(left);
	DestroyRecursive(right);

	SafeDelete(node);

}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
}

void RedBlackTree::Remove(int data)
{
	Node* deleted = nullptr;
	if (!Find(data, &deleted))
	{
		std::cout << "오류: 노드 삭제 실패. 삭제할 노드를 찾지 못했습니다. (검색값:" << data << ")\n";
		return;
	}
	RemoveImpl(deleted);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// 탈출 조건
	if (node == nil)
	{
		return;
	}

	// 노드 색상이 검정이면 blackCount 가 증가
	// 닐노드를 세지 않기 떄문에 Root 를 포함해서 새기
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// 부모 표기 문자열 설정
	int parentData = 0;
	const char* position = "Root";

	// 부모 노드가 있는지 확인.
	if (node->Parent())
	{
		// 부모 노드의 데이터 저장.
		parentData = node->Parent()->Data();

		// 부모 노드로부터 현재 노드의 위치 설정.
		if (node == node->Parent()->LeftChild())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// 검은색 수 출력을 위한 문자열.
	char blackCountString[50]{};

	// 자손이 없으면 현재까지의 검은색 노드 수 설정.
	if (node->LeftChild() == nil && node->RightChild() == nil)
	{
		// Unreal FString::Format()
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth 출력
	for (int i = 0; i < depth; ++i)
	{
		std::cout << "  ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout << node->Data() << " " << node->ColorString() << " [" << position << ", " << parentData << "] " << blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->LeftChild(), depth + 1, blackCount);
	PrintRecursive(node->RightChild(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
	static HANDLE consoloe = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoloe, (int)color);
}
