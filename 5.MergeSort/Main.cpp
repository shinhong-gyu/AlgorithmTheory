#include <iostream>

// ���ҵ� �迭�� �ٽ� ��ĥ �� ����ϴ� ���� �Լ�.
void Merge(const char* array[], int arrayLength, const char* leftArray[], int leftArrayLength, const char* rightArray[], int rightArrayLength)
{
	// �ε��� ����.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// ����/������ �迭�� ��Ҹ� ���� �� ���� �迭�� ��Ҹ� ���� �迭 array�� ����.
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (strcmp(leftArray[leftIndex], rightArray[rightIndex]) <= 0)
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		++mergedIndex;
	}

	// ���� �������� ���� �迭�� ���� ��Ҹ� ���� �迭�� ����.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	// ������ �迭�� ���� ��Ҹ� ���� �迭�� ����.
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

void MergeSort(const char* array[], int length)
{
	// �迭�� �� �̻� ���� �� ���� ��쿡�� �Լ� ���� (��� �Լ� Ż�� ����).
	if (length <= 1)
	{
		return;
	}

	// �迭 ������.
	int mid = length / 2;
	const char** leftArray = new const char* [mid];
	const char** rightArray = new const char* [length - mid];

	// �迭 ����. memcpy �Լ��� �޸𸮸� ��°�� ����.
	// ���� �迭�� 0���� mid �ε������� ����.
	memcpy(leftArray, array, sizeof(const char*) * mid);

	// ������ �迭�� mid���� length - mid �ε������� ����.
	memcpy(rightArray, (array + mid), sizeof(const char*) * (length - mid));

	// ���� �迭�� ���� ���� ���� (���).
	MergeSort(leftArray, mid);

	// ������ �迭�� ���� ���� ���� (���).
	MergeSort(rightArray, length - mid);

	// ���ҵ� �迭 ��ġ��.
	Merge(array, length, leftArray, mid, rightArray, length - mid);

	// ���� �޸� ����.
	delete[] leftArray;
	delete[] rightArray;
}

// �迭 ��� �Լ�.
void PrintArray(const char* array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{
	// �迭.
	const char* array[] = { "banana", "apple", "orange", "grape", "kiwi", "mango" };

	// �迭 ����.
	int length = sizeof(array) / sizeof(array[0]);

	// ���� �� ���.
	std::cout << "���� �� �迭: ";
	PrintArray(array, length);

	// ����.
	MergeSort(array, length);

	// ���� �� ���.
	std::cout << "���� �� �迭: ";
	PrintArray(array, length);

	std::cin.get();
}