// SomeSimpleAlgorithms.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SortAlgorithm.h"
#include <time.h>
#include <Windows.h>


void showSort();

int main()
{
	bool exit = false;
	do
	{
		std::cout << "Menu\n1. Sort algorithm\n2. Graph\n3. Search algorithmOther. Exit\n";
		int option;
		exit = false;
		std::cin >> option;
		switch (option)
		{
		case 1:
			showSort();
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			exit = true;
			break;
		}
	} while (!exit);

    return 0;
}

void showSort() {
	srand((unsigned)time(NULL));
	int length;
	std::cout << "Enter the count of random numbers: ";
	std::cin >> length;
	int *arr = new int[length];
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 100000;
		//std::cout << arr[i] << " ";
	}

	DWORD timeStart, timeStop;
	int *arr2 = new int[length];
	for (int i = 0; i < length; i++) {
		arr2[i] = arr[i];
	}
	std::cout << "\n Bubble Sort: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::bubbleSort(arr2, length);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr2[i] << " ";
	//}

	int *arr1 = new int[length];
	for (int i = 0; i < length; i++) {
		arr1[i] = arr[i];
	}
	std::cout << "\n Insertion Sort: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::insertionSort(arr1, length);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr1[i] << " ";
	//}

	int *arr3 = new int[length];
	for (int i = 0; i < length; i++) {
		arr3[i] = arr[i];
	}
	std::cout << "\n Selection Sort: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::selectionSort(arr3, length);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr3[i] << " ";
	//}

	int *arr4 = new int[length];
	for (int i = 0; i < length; i++) {
		arr4[i] = arr[i];
	}
	std::cout << "\n Quick Sort: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::quickSort(arr4, 0, length - 1);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr4[i] << " ";
	//}

	int *arr5 = new int[length];
	for (int i = 0; i < length; i++) {
		arr5[i] = arr[i];
	}
	std::cout << "\n Quick Sort2: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::quickSort2(arr5, 0, length - 1);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr5[i] << " ";
	//}

	int *arr6 = new int[length];
	for (int i = 0; i < length; i++) {
		arr6[i] = arr[i];
	}
	std::cout << "\n Merge Sort: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::mergeSort(arr6, length);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr6[i] << " ";
	//}

	int *arr7 = new int[length];
	for (int i = 0; i < length; i++) {
		arr7[i] = arr[i];
	}
	std::cout << "\n Merge Sort2: \n";
	timeStart = GetTickCount();
	SortAlgorithm<int>::mergeSort2(arr7, length);
	timeStop = GetTickCount();
	std::cout << (timeStop - timeStart) << "ms\n";
	//for (int i = 0; i < length; i++) {
	//	std::cout << arr7[i] << " ";
	//}

	std::cin.get();
	std::cin.get();
	delete[] arr;
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;
}

