#include <iostream>

// �ǹ�(Pivot) ���� �Լ�
int Partition(int* array, int left, int right)
{
	int first = left;
	int pivot = array[first];

	++left;

	// ���� �Ǳ� ������ �ݺ�
	while (left <= right)
	{
		// left �� pivot ���� ū �� �˻�
		while (array[left] < pivot)
		{
			++left;
		}

		// right �� pivot ���� ���� �� �˻�
		while (array[right] > pivot)
		{
			--right;
		}

		// left�� right �� �������� �ʾ��� ���� �� ��ȯ 
		if (left < right)
		{
			std::swap(array[left], array[right]);
		}
		else
		{
			break;
		}
	}

	std::swap(array[right], array[first]);
	return right;
}

// �� ���� �Լ�.
void QuickSort(int* array, int left, int right)
{
	if (left < right)
	{
		// ����
		int partition = Partition(array, left, right);
		// ���� �迭 �� ����
		QuickSort(array, left, partition - 1);
		// ������ �迭  �� ����
		QuickSort(array, partition + 1, right);
	}
}

void PrintArray(int array[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << array[i] << (length - 1 > i ? " " : "");
	}
	std::cout << "\n";
}

// ���� �Լ� (������)
int main()
{
	// �迭 ����
	int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25 };

	// �迭�� ����
	int length = sizeof(array) / sizeof(int);

	// int length = _countof(array)

	std::cout << "���� �� : ";
	PrintArray(array, length);

	QuickSort(array, 0, length - 1);

	std::cout << "���� �� : ";
	PrintArray(array, length);

	std::cin.get();
}