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
	// @Todo : ��� ��� ����.
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
	// Ʈ���� �ߺ��Ǵ� �����Ͱ� �ִ��� Ȯ��
	Node* node = nullptr;
	if (Find(data, &node))
	{
		std::cout << "���� -��� �߰� ���� : �̹� ���� ���� �ֽ��ϴ�." << data << "\n";
		return false;
	}

	Insert(CreateNode(data, Color::Red));
	return true;
}



bool RedBlackTree::FindRecursive(Node* node, Node** outNode, int data)
{
	// ��� Ż�� ���� (�˻� ����)
	if (node == nil)
	{
		return false;
	}

	// �˻��� ���������� true �� outNode ��ȯ.
	if (node->Data() == data)
	{
		*outNode = node;
		return true;
	}

	// �˻��� �����Ͱ� ����� �����ͺ��� ũ�ٸ� ���� Ž��
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
	// Ʈ���� ����ִ� ���
	// ��Ʈ�� ����
	if (root == nil)
	{
		newNode->SetColor(Color::Black);
		root = newNode;
		return;
	}

	// Ʈ���� ������� ������, ��������� ��ġ �˻� �� ����.
	InsertRecursive(root, newNode);

	// ���Ե� ��� �� ����.
	newNode->SetColor(Color::Red);
	newNode->SetLeftChild(nil);
	newNode->SetRightChild(nil);

	// ���� �� ������ ó��.
	RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// �� ����� �����Ͱ� ���� ��庸�� ������ ���� ���� Ʈ���� ���� ����.
	if (node->Data() > newNode->Data())
	{
		// ���� �ڼ��� ���ٸ�, ���� ó��.
		if (node->LeftChild() == nil)
		{
			node->SetLeftChild(newNode);
			newNode->SetParent(node);
			return;
		}

		// �ڼ��� �ִٸ�, ���� Ʈ���� ���� ���� ����
		InsertRecursive(node->LeftChild(), newNode);
	}
	else
	{
		// ������ �ڼ��� ���ٸ�, ����.
		if (node->RightChild() == nil)
		{
			node->SetRightChild(newNode);
			newNode->SetParent(node);
			return;
		}

		// �ڼ��� ������ ������ ���� Ʈ���� ���� ���� ����
		InsertRecursive(node->RightChild(), newNode);
	}
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// �θ� ��尡 �������� ��쿡�� 
	// ������ ��尡 �������� ���� �� ���ٴ� ������ 
	// �������� �ʱ� ������ �̸� �ذ��ϱ� ���� ������ ����(Case2: Red-Red Conflict).
	while (newNode != root && newNode->Parent()->GetColor() == Color::Red)
	{
		// �ذ� ��� (������ �������� ���/������ �������� ���).
		// ���� ���ϱ� #1: �� ����� �θ� ���θ��� ���� �ڼ��� ���.
		if (newNode->Parent() == newNode->Parent()->Parent()->LeftChild())
		{
			// ����.
			Node* uncle = newNode->Parent()->Parent()->RightChild();

			// ���� ��尡 �������� ��.
			// �ذ�: �θ�� ������ ���������� �����ϰ�, ���θ� ���������� �����ؼ�
			// ������ ���� �ø���.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// ������ ������ �ڿ� ���� ��忡���� ���� ������ �߻������� �ʴ��� Ȯ��.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// ���� ��尡 �������� ��.
			// �ذ�: �θ�, ���θ�, �� ����� ��ġ�� ���� ȸ���� ����.
			// #1: �� ��尡 �θ�� �ݴ� ��ġ�� �� -> �θ� �߽����� 1�� ȸ�� �� �ٽ� ȸ��.
			// #2: �� ��尡 �θ�� ���� ��ġ�� �� -> ȸ�� �� ���� �缳���� ���� ��ġ ������.
			else
			{
				// �θ�� �ݴ� ��ġ�� ��� (�߰� ȸ��).
				// �θ�� �� ����� ��ġ�� ���߱� ����.
				if (newNode == newNode->Parent()->RightChild())
				{
					// �θ� �߽����� ȸ�� ����.
					newNode = newNode->Parent();
					RotateToLeft(newNode);
				}

				// ���θ� �߽����� ȸ�� �� ���� ����.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RotateToRight(newNode->Parent()->Parent());
			}
		}

		// ���� ���ϱ� #2: �� ����� �θ� ���θ��� ������ �ڼ��� ���.
		else
		{
			// ����.
			Node* uncle = newNode->Parent()->Parent()->LeftChild();

			// ���� ��尡 �������� ��.
			// �ذ�: �θ�� ������ ���������� �����ϰ�, ���θ� ���������� �����ؼ�
			// ������ ���� �ø���.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// ������ ������ �ڿ� ���� ��忡���� ���� ������ �߻������� �ʴ��� Ȯ��.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// ���� ��尡 �������� ��.
			// �ذ�: �θ�, ���θ�, �� ����� ��ġ�� ���� ȸ���� ����.
			// #1: �� ��尡 �θ�� �ݴ� ��ġ�� �� -> �θ� �߽����� 1�� ȸ�� �� �ٽ� ȸ��.
			// #2: �� ��尡 �θ�� ���� ��ġ�� �� -> ȸ�� �� ���� �缳���� ���� ��ġ ������.
			else
			{
				// �θ�� �ݴ� ��ġ�� ��� (�߰� ȸ��).
				// �θ�� �� ����� ��ġ�� ���߱� ����.
				if (newNode == newNode->Parent()->LeftChild())
				{
					// �θ� �߽����� ȸ�� ����.
					newNode = newNode->Parent();
					RotateToRight(newNode);
				}

				// ���θ� �߽����� ȸ�� �� ���� ����.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RotateToLeft(newNode->Parent()->Parent());
			}
		}
	}

	// ��Ʈ ��带 ������ ����.
	root->SetColor(Color::Black);
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
	if (node == nil)
	{
		return nullptr;
	}

	// ���� ���� ��尡 �� �̻� ������ ���� ��� ��ȯ
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

	// ������ ���� ��尡 �� �̻� ������ ���� ��� ��ȯ
	if (node->RightChild() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->RightChild());

}

void RedBlackTree::RemoveImpl(Node* node)
{
	// ���� ��� ���.
	Node* removed = nullptr;

	// ������ ��ġ�� ��ü ���.
	Node* trail = nil;

	Node* target = node;

	// �ڼ��� �ϳ� ������ ���.
	if (target->LeftChild() == nil || target->RightChild() == nil)
	{
		removed = target;
	}

	// �ڼ��� ��� �ִ� ���.
	else
	{
		// ��ü�� ��� �˻�.
		// (���� ���� Ʈ������ ���� ū���� ��ü ���� ����).
		removed = FindMaxRecursive(target->LeftChild());

		// ��ü ��尡 �����ϸ� �ش� ������ ����.
		//if (removed != nullptr && removed != nil)
		//{
		//    // ���� ����� ���� ��� ����� ������ ����.
		//    target->SetData(removed->Data());
		//}

		// ���� ����� ���� ��� ����� ������ ����.
		target->SetData(removed->Data());
	}

	// �ڼ��� �ϳ��� ���� ��.
	if (node->LeftChild() != nil && node->RightChild() == nil)
	{
		trail = node->LeftChild();
	}
	else if (node->RightChild() != nil && node->LeftChild() == nil)
	{
		trail = node->RightChild();
	}

	// ��� ��尡 �ִ� ���.
	if (trail != nil /*&& trail != nullptr*/)
	{
		trail->SetParent(removed->Parent());
	}

	// removed ��尡 root�� ���.
	if (removed->Parent() == nullptr)
	{
		root = trail;
	}
	// root�� �ƴ� ��.
	else
	{
		// trail ��带 removed�� ���� ��ġ�� ����.
		if (removed == removed->Parent()->LeftChild())
		{
			removed->Parent()->SetLeftChild(trail);
		}
		else
		{
			removed->Parent()->SetRightChild(trail);
		}
	}

	// ������ ���� Ȯ���� ����.
	if (removed->GetColor() == Color::Black && trail != nil)
	{
		// ������ ����.
	}

	// ��� ����.
	SafeDelete(removed);
}

void RedBlackTree::RestructureAfterRemove(Node* newNode)
{
	// ���� �� ���� �ذ�
	while (newNode->Parent() != nullptr && newNode->GetColor() == Color::Black)
	{
		if (newNode == newNode->Parent()->LeftChild())
		{
			Node* sibling = newNode->Parent()->RightChild();
			if (sibling == nil)
			{
				break;
			}

			// case 1 : ���� ��尡 ������.
			// �ذ� : ���� ��带 Black���� �����ϰ�
			// �θ� Red�� �ٲ� �� �θ� �������� ��ȸ�� �Ǵ� ��ȸ��
			if (sibling->GetColor() == Color::Red)
			{
				sibling->SetColor(Color::Black);
				newNode->Parent()->SetColor(Color::Red);

				// ��ȸ��
				RotateToLeft(newNode->Parent());
				continue;
			}

			// case 2  : ������ ���� �� �ڽ� ��� �������� ��.
			// �ذ� :
			if (sibling->LeftChild()->GetColor() == Color::Black && sibling->RightChild()->GetColor() == Color::Black)
			{
				sibling->SetColor(Color::Red);
				newNode = newNode->Parent();
				continue;
			}

			// case 3 : ���� ��� ����. ���� ����� ���� �ڼ��� ������.
			// �ذ� : ������ ���� �ڽ��� Black���� ����.
			// ������ Red�� ���� �� ���� ���� ��ȸ��
			if (sibling->LeftChild()->GetColor() == Color::Red)
			{
				sibling->LeftChild()->SetColor(Color::Black);
				sibling->SetColor(Color::Red);

				// ��ȸ��
				RotateToRight(sibling);

				// ȸ�� �� ���� ��ġ ������Ʈ
				sibling = newNode->Parent()->RightChild();
			}

			// case 4 : ���� ���� Black, ������ ������ �ڽ��� Red
			// �ذ� : ������ �θ�� ���� ������ ����,
			// �θ� Black���� ����
			// ������ ������ �ڽ��� Black���� ���� �� �θ� ���� ��ȸ��.
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

			// case 1 : ���� ��尡 ������.
			// �ذ� : ���� ��带 Black���� �����ϰ�
			// �θ� Red�� �ٲ� �� �θ� �������� ��ȸ�� �Ǵ� ��ȸ��
			if (sibling->GetColor() == Color::Red)
			{
				sibling->SetColor(Color::Black);
				newNode->Parent()->SetColor(Color::Red);

				// ��ȸ��
				RotateToRight(newNode->Parent());
				continue;
			}

			// case 2  : ������ ���� �� �ڽ� ��� �������� ��.
			// �ذ� :
			if (sibling->RightChild()->GetColor() == Color::Black && sibling->LeftChild()->GetColor() == Color::Black)
			{
				sibling->SetColor(Color::Red);
				newNode = newNode->Parent();
				continue;
			}

			// case 3 : ���� ��� ����. ���� ����� ������ �ڼ��� ������.
			// �ذ� : ������ ������ �ڽ��� Black���� ����.
			// ������ Red�� ���� �� ���� ���� ��ȸ��
			if (sibling->RightChild()->GetColor() == Color::Red)
			{
				sibling->RightChild()->SetColor(Color::Black);
				sibling->SetColor(Color::Red);

				// ��ȸ��s
				RotateToLeft(sibling);

				// ȸ�� �� ���� ��ġ ������Ʈ
				sibling = newNode->Parent()->LeftChild();
			}

			// case 4 : ���� ���� Black, ������ ���� �ڽ��� Red
			// �ذ� : ������ �θ�� ���� ������ ����,
			// �θ� Black���� ����
			// ������ ���� �ڽ��� Black���� ���� �� �θ� ���� ��ȸ����.
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

	// ��带 ���������� ����
	newNode->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* pivot)
{
	// ������ �ڽ� ���.
	Node* rightChild = pivot->RightChild();

	// ������ �ڽ� ����� ���� �ڽ� ��带 �θ��� ������ �ڽ����� ���.
	pivot->SetRightChild(rightChild->LeftChild());

	// ���� ����� �θ� ó��.
	if (rightChild->LeftChild() != nil)
	{
		rightChild->LeftChild()->SetParent(pivot);
	}

	// ������ �ڽ� ����� �θ� �θ��� �θ�(���θ�)�� ����.
	rightChild->SetParent(pivot->Parent());

	// �θ� root�� ���
	if (rightChild->Parent() == nullptr)
	{
		root = rightChild;
	}

	// �θ� root�� �ƴ� ���
	else
	{
		// ���θ� ���� ������ �ڽ� ��ġ�� ����
		if (pivot == pivot->Parent()->LeftChild())
		{
			pivot->Parent()->SetLeftChild(rightChild);
		}
		else
		{
			pivot->Parent()->SetRightChild(rightChild);
		}
	}

	// ��ȸ�� ������
	rightChild->SetLeftChild(pivot);
	pivot->SetParent(rightChild);
}

void RedBlackTree::RotateToRight(Node* pivot)
{
	// ���� �ڽ� ���.
	Node* leftChild = pivot->LeftChild();

	// ���� �ڽ��� ������ �ڽ��� �θ��� ���� �ڽ����� ���
	pivot->SetLeftChild(leftChild->RightChild());

	// ���� ����� �θ� ó��.
	if (leftChild->RightChild() != nil)
	{
		leftChild->RightChild()->SetParent(pivot);
	}

	// ������ �ڽ� ����� �θ� �θ��� �θ�(���θ�)�� ����.
	leftChild->SetParent(pivot->Parent());

	// �θ� root�� ���
	if (leftChild->Parent() == nullptr)
	{
		root = leftChild;
	}

	// �θ� root�� �ƴ� ���
	else
	{
		// ���θ� ���� ������ �ڽ� ��ġ�� ����
		if (pivot == pivot->Parent()->LeftChild())
		{
			pivot->Parent()->SetLeftChild(leftChild);
		}
		else
		{
			pivot->Parent()->SetRightChild(leftChild);
		}
	}

	// ��ȸ�� ������
	leftChild->SetRightChild(pivot);
	pivot->SetParent(leftChild);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// ��� Ż�� ����
	if (node == nil)
	{
		return;
	}

	// ����/������ �ڼ�
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
		std::cout << "����: ��� ���� ����. ������ ��带 ã�� ���߽��ϴ�. (�˻���:" << data << ")\n";
		return;
	}
	RemoveImpl(deleted);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// Ż�� ����
	if (node == nil)
	{
		return;
	}

	// ��� ������ �����̸� blackCount �� ����
	// �ҳ�带 ���� �ʱ� ������ Root �� �����ؼ� ����
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// �θ� ǥ�� ���ڿ� ����
	int parentData = 0;
	const char* position = "Root";

	// �θ� ��尡 �ִ��� Ȯ��.
	if (node->Parent())
	{
		// �θ� ����� ������ ����.
		parentData = node->Parent()->Data();

		// �θ� ���κ��� ���� ����� ��ġ ����.
		if (node == node->Parent()->LeftChild())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// ������ �� ����� ���� ���ڿ�.
	char blackCountString[50]{};

	// �ڼ��� ������ ��������� ������ ��� �� ����.
	if (node->LeftChild() == nil && node->RightChild() == nil)
	{
		// Unreal FString::Format()
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth ���
	for (int i = 0; i < depth; ++i)
	{
		std::cout << "  ";
	}

	// ��� ���� ���� �ܼ� ����.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// ���� ��� �� ���.
	std::cout << node->Data() << " " << node->ColorString() << " [" << position << ", " << parentData << "] " << blackCountString << "\n";

	// ��带 ����� �ڿ��� �ܼ� �������.
	SetTextColor(TextColor::White);

	// ���� ��� ���.
	PrintRecursive(node->LeftChild(), depth + 1, blackCount);
	PrintRecursive(node->RightChild(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
	static HANDLE consoloe = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoloe, (int)color);
}
