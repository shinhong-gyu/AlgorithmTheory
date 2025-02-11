#include <iostream>

// 분할된 배열을 다시 합칠 때 사용하는 병합 함수.
void Merge(const char* array[], int arrayLength, const char* leftArray[], int leftArrayLength, const char* rightArray[], int rightArrayLength)
{
	// 인덱스 시작.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// 왼쪽/오른쪽 배열의 요소를 비교해 더 작은 배열의 요소를 최종 배열 array에 복사.
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

	// 위의 과정에서 왼쪽 배열에 남은 요소를 최종 배열에 복사.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	// 오른쪽 배열에 남은 요소를 최종 배열에 복사.
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

void MergeSort(const char* array[], int length)
{
	// 배열을 더 이상 나눌 수 없는 경우에는 함수 종료 (재귀 함수 탈출 조건).
	if (length <= 1)
	{
		return;
	}

	// 배열 나누기.
	int mid = length / 2;
	const char** leftArray = new const char* [mid];
	const char** rightArray = new const char* [length - mid];

	// 배열 복사. memcpy 함수로 메모리를 통째로 복사.
	// 왼쪽 배열은 0부터 mid 인덱스까지 복사.
	memcpy(leftArray, array, sizeof(const char*) * mid);

	// 오른쪽 배열은 mid부터 length - mid 인덱스까지 복사.
	memcpy(rightArray, (array + mid), sizeof(const char*) * (length - mid));

	// 왼쪽 배열에 대해 병합 정렬 (재귀).
	MergeSort(leftArray, mid);

	// 오른쪽 배열에 대해 병합 정렬 (재귀).
	MergeSort(rightArray, length - mid);

	// 분할된 배열 합치기.
	Merge(array, length, leftArray, mid, rightArray, length - mid);

	// 동적 메모리 해제.
	delete[] leftArray;
	delete[] rightArray;
}

// 배열 출력 함수.
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
	// 배열.
	const char* array[] = { "banana", "apple", "orange", "grape", "kiwi", "mango" };

	// 배열 길이.
	int length = sizeof(array) / sizeof(array[0]);

	// 정렬 전 출력.
	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	// 정렬.
	MergeSort(array, length);

	// 정렬 후 출력.
	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();
}