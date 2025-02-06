#include <iostream>

// 두 값을 서로 교환하는 함수.
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 버블 정렬 함수.
void BubbleSort(int* array, int length)
{
	// 정렬
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (array[j] > array[j + 1]) Swap(array[j], array[j + 1]);
		}
	}
}

// 출력함수
void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}

int main()
{
	// 배열 선언
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// 배열의 길이
	int length = sizeof(array) / sizeof(int);

	PrintArray(array, length);

	BubbleSort(array, length);

	PrintArray(array, length);
}
