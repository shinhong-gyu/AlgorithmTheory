#include <iostream>

void SelectionSort(int* array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		// 최소값 저장할 변수.
		int minIndex = i;

		for (int j = i + 1; j < length; j++)
		{
			// 비교
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}
				// 값 바꾸기.
		std::swap<int>(array[i], array[minIndex]);
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

	SelectionSort(array, length);

	PrintArray(array, length);
}