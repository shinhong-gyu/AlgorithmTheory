#include <iostream>
#include <vector>

void Heapify(std::vector<int>& array, int length, int i)
{
	while (true)
	{
		// �� ������ ���� 
		int largest = i;

		// ���� �ڼ� �ε���
		int left = 2 * i + 1;

		// ������ �ڼ� �ε���
		int right = 2 * i + 2;

		if (left < length && array[left] > array[largest])
		{
			largest = left;
		}

		if (right < length && array[right] > array[largest])
		{
			largest = right;
		}

		if (largest == i)
		{
			break;
		}

		std::swap(array[i], array[largest]);
		i = largest;
	}
}

void HeapSort(std::vector<int>& array)
{
	int length = (int)array.size();

	// �� ����
	for (int i = length / 2 - 1; i >= 0; --i)
	{
		// �� �����
		Heapify(array, length, i);
	}

	// ����
	for (int i = length - 1; i > 0; --i)
	{
		std::swap(array[0], array[i]);
		Heapify(array, i, 0);
	}

	std::cin.get();
}

void PrintArray(std::vector<int>& array)
{
	for (int i = 0; i < (int)array.size(); i++)
	{
		std::cout << array[i] << (i < (int)array.size() - 1 ? "," : "");
	}
}

int main()
{
	// �迭.
	std::vector<int> array = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	HeapSort(array);
}