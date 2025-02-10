#include <iostream>

using namespace std;

// 삽입 정렬 함수.
void InsertionSort(int* array, int length)
{
	for (int i = 1; i < length; i++)
	{
		// 키 뽑기
		int keyValue = array[i];
		int j = i - 1;

		// 셔플링(교환).
		while (j >= 0 && array[j] > keyValue)
		{
			array[j + 1] = array[j];
			--j;
		}
		// 값 끼우기.
		array[j + 1] = keyValue;
	}
}

void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << (i < length - 1 ? "," : "");
	}
	cout << "\n";
}

int main()
{
	int array[] = { 5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16 };

	int length =sizeof(array)/sizeof(int);
	
	cout << "정렬 전: ";
	PrintArray(array,length);

	InsertionSort(array,length);

	cout << "정렬 후: ";
	PrintArray(array, length);

}