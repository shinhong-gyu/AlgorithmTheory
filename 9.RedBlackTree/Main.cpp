#include <iostream>
#include "RedBlackTree.h"
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>

// ��� ������ ���� ������
enum class Command
{
	None,
	Insert,
	Delete,
	Find,
	Print,
	Quit,
};

// ȭ�� ����� �Լ�
void ClearScreen()
{
	system("cls");
}

void Initialization(const char* path, RedBlackTree* tree)
{
	if (tree == nullptr)
	{
		std::cout << "����: ���޵� Ʈ���� null �Դϴ�.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, path, "r");
	if (file == nullptr)
	{
		std::cout << "����: ���� �б� ����.\n";
		return;
	}

	char line[1024] = { };
	if (!fgets(line, 1024, file))
	{
		std::cout << "����: ���� �б� ����.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// ù ��� �б�.
	char* context = nullptr;
	char* splitString = strtok_s(line, ",", &context);
	if (splitString)
	{
		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// ������ ��� �б�.
	while (context)
	{
		splitString = strtok_s(nullptr, ",", &context);
		if (!splitString)
		{
			break;
		}

		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// Ʈ���� ������ �߰�.
	for (auto data : datas)
	{
		tree->Insert(data);
	}

	// �ʱ� �����͸� ������ ���� ������ ���.
	std::cout << "�ʱ� �����Ͱ� ����Ǿ����ϴ�.\n";
	tree->Print();
	std::cout << "\n";
}

void ProcessCommandInput(int& commandInput)
{
	// �Է� ó��.
	char inputBuffer[100] = {};

	while (true)
	{
		// �Է� �ȳ� ��� �� �Է� ����.
		std::cout << "��� ���ڸ� �Է��ϼ���.\n";
		std::cout << "(1)��� �߰�, (2)��� ����, (3)��� �˻�, (4)��� ���, (5)����\n";
		std::cin >> inputBuffer;

		// atoi: ascii to integer.
		if (commandInput = atoi(inputBuffer))
		{
			// ����ó��.
			if (commandInput <= (int)Command::None
				|| commandInput > (int)Command::Quit)
			{
				ClearScreen();
				std::cout << "����: �߸��� ���ڸ� �Է��߽��ϴ�.\n";
				continue;
			}

			break;
		}

		// ����ó��.
		ClearScreen();
		std::cout << "����: ����� ���ڸ� �Է��ؾ� �մϴ�.\n";
	}
}

void ProcessParamInput(int& param)
{
	// �Է� ó��.
	char inputBuffer[100] = {};

	while (true)
	{
		std::cout << "�Ķ���͸� �Է��ϼ��� (1-200). \n";
		std::cin >> inputBuffer;

		if (param = atoi(inputBuffer))
		{
			if (param < 1 || param > 200)
			{
				ClearScreen();
				std::cout << "���� : �Ķ���ʹ� 1-200 ������ ���ڸ� �Է��ؾ� �մϴ�.\n";
				continue;
			}
			break;
		}
		ClearScreen();
		std::cout << "���� : �Ķ���ʹ� ���ڸ� �Է��ؾ� �մϴ�.\n";
	}
}

// ��� ó�� �Լ�
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
	Command command = (Command)commandInput;

	if (command == Command::Print)
	{
		ClearScreen();

		tree.Print();

		return;
	}

	// ���α׷� ����.
	if (command == Command::Quit)
	{
		return;
	}

	int param = 0;
	ProcessParamInput(param);

	// 1/2/3 ��� ó��
	switch (command)
	{
		// Deprecated.
		// ��� �߰�. TBD(To Be Deleted).
	case Command::Insert:
	{
		ClearScreen();
		tree.Insert(param);
		break;
	}
	case Command::Delete:
	{
		// Todo:
		ClearScreen();
		tree.Remove(param);
		break;
	}
	case Command::Find:
	{
		ClearScreen();

		// �˻�.
		Node* result = nullptr;
		// �˻� ����
		if (!tree.Find(param, &result))
		{
			std::cout << "��带 ã�� ���߽��ϴ�. (�˻� ��: " << param << ")\\n";
			return;
		}

		if (result->GetColor() == Color::Red)
		{
			SetTextColor(TextColor::Red);
		}
		else
		{
			SetTextColor(TextColor::White);
		}

		// �˻� ��� ���
		std::cout << "�˻��� ���: " << result->Data() << "(Color:" << result->ColorString() << ")\n";

		// �ܼ� �ؽ�Ʈ ����
		SetTextColor(TextColor::White);
		break;
	}
	default:
		break;
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RedBlackTree tree;

	Initialization("../Assets/InitData.txt", &tree);

	while (true)
	{
		int commandInput = 0;
		ProcessCommandInput(commandInput);

		ProcessCommand(commandInput, tree);

		if (commandInput == 5) break;
	}

}
