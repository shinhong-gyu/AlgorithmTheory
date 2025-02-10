#include <iostream>

// 피벗(Pivot) 선택 함수
int Partition(int* array, int left, int right)
{
	int first = left;
	int pivot = array[first];

	++left;

	// 교차 되기 전까지 반복
	while (left <= right)
	{
		// left 는 pivot 보다 큰 값 검색
		while (array[left] < pivot)
		{
			++left;
		}

		// right 는 pivot 보다 작은 값 검색
		while (array[right] > pivot)
		{
			--right;
		}

		// left와 right 가 교차하지 않았을 때만 값 교환 
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

// 퀵 정렬 함수.
void QuickSort(int* array, int left, int right)
{
	if (left < right)
	{
		// 분할
		int partition = Partition(array, left, right);
		// 왼쪽 배열 퀵 정렬
		QuickSort(array, left, partition - 1);
		// 오른쪽 배열  퀵 정렬
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

// 메인 함수 (진입점)
int main()
{
	// 배열 선언
	int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25 };

	// 배열의 길이
	int length = sizeof(array) / sizeof(int);

	// int length = _countof(array)

	std::cout << "정렬 전 : ";
	PrintArray(array, length);

	QuickSort(array, 0, length - 1);

	std::cout << "정렬 후 : ";
	PrintArray(array, length);

	std::cin.get();
}