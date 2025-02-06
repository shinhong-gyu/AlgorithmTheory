#include <iostream>

void SelectionSort(int* array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		// �ּҰ� ������ ����.
		int minIndex = i;

		for (int j = i + 1; j < length; j++)
		{
			// ��
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}
				// �� �ٲٱ�.
		std::swap<int>(array[i], array[minIndex]);
	}
}
// ����Լ�
void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}

int main()
{
	// �迭 ����
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// �迭�� ����
	int length = sizeof(array) / sizeof(int);

	PrintArray(array, length);

	SelectionSort(array, length);

	PrintArray(array, length);
}