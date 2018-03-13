#include <stdlib.h>

template<typename T>
class SortAlgorithm
{
public:
	static void bubbleSort(T arr[], const int length, bool order = true);
	static void insertionSort(T arr[], const int length, bool order = true);
	static void selectionSort(T arr[], const int length, bool order = true);
	static void quickSort(T arr[], int a, int b, bool order = true);
	static void quickSort2(T arr[], int a, int b, bool order = true);
	static void mergeSort(T arr[], const int length, bool order = true);
	static void mergeSort2(T arr[], const int length, bool order = true);

	static void swap(T arr[], int a, int b);

private:
	static T* merge(T arr1[], T arr2[], int length1, int length2, bool order);
	static T* divide(T arr[], int length, int index, bool start);
	static void mergeSortRecursive(T arr[], T reg[], int a, int b, bool order);
	static T* mergeSortRecursive2(T arr[], T reg[], int a, int b, bool order);

};

template<typename T>
inline void SortAlgorithm<T>::bubbleSort(T arr[], const int length, bool order)
{
	if (order) {
		for (int i = 1; i < length; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (arr[j + 1] < arr[j])
					swap(arr, j, j + 1);
			}
		}
	}
	else {
		for (int i = 1; i < length; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (arr[j + 1] > arr[j])
					swap(arr, j, j + 1);
			}
		}
	}
}

template<typename T>
inline void SortAlgorithm<T>::insertionSort(T arr[], const int length, bool order)
{
	if (order) {
		for (int i = 1, j = 0; i < length; i++) {
			int key = arr[i];
			for (j = i - 1; j >= 0 && key < arr[j]; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = key;
		}
	}
	else {
		for (int i = 1, j = 0; i < length; i++) {
			int key = arr[i];
			for (j = i - 1; j >= 0 && key > arr[j]; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = key;
		}
	}
}

template<typename T>
inline void SortAlgorithm<T>::selectionSort(T arr[], const int length, bool order)
{
	if (order) {
		for (int i = 0; i < length; i++) {
			int min = arr[i];
			int index = i;
			for (int j = i; j < length; j++) {
				if (arr[j] < min) {
					min = arr[j];
					index = j;
				}
			}
			swap(arr, i, index);
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			int max = arr[i];
			int index = i;
			for (int j = i; j < length; j++) {
				if (arr[j] > max) {
					max = arr[j];
					index = j;
				}
			}
			swap(arr, i, index);
		}
	}
}

template<typename T>
inline void SortAlgorithm<T>::quickSort(T arr[], int a, int b, bool order)
{
	if (a >= b) return;
	T key = arr[(a + b) / 2];
	int i = a, j = b;
	if (order) {
		while (i < j) {
			while (arr[i] < key) {
				i++;
			}
			while (arr[j] > key) {
				j--;
			}
			if (i <= j) {
				swap(arr, i, j);
				i++;
				j--;
			}
		}
	}
	else {
		while (i < j) {
			while (arr[i] > key) {
				i++;
			}
			while (arr[j] < key) {
				j--;
			}
			if (i <= j) {
				swap(arr, i, j);
				i++;
				j--;
			}
		}
	}

	quickSort(arr, a, j, order);
	quickSort(arr, i, b, order);
}

template<typename T>
inline void SortAlgorithm<T>::quickSort2(T arr[], int a, int b, bool order)
{
	if (a >= b) return;
	T key = arr[b];
	int i = a, j = b - 1;
	if (order) {
		while (i < j) {
			while (arr[i] < key && i < j) {
				i++;
			}
			while (arr[j] >= key && i < j) {
				j--;
			}
			swap(arr, i, j);
		}
		if (arr[i] >= arr[b])
			swap(arr, i, b);
		else
			i++;
	}
	else {
		while (i < j) {
			while (arr[i] > key && i < j) {
				i++;
			}
			while (arr[j] <= key && i < j) {
				j--;
			}
			swap(arr, i, j);
		}
		if (arr[i] <= arr[b])
			swap(arr, i, b);
		else
			i++;
	}

	quickSort2(arr, a, i - 1, order);
	quickSort2(arr, i + 1, b, order);
}

template<typename T>
inline void SortAlgorithm<T>::mergeSort(T arr[], const int length, bool order)
{
	T *reg = new T[length];
	mergeSortRecursive(arr, reg, 0, length - 1, order);
	delete[] reg;
}

template<typename T>
inline void SortAlgorithm<T>::mergeSort2(T arr[], const int length, bool order)
{
	T *reg = new T[length];
	mergeSortRecursive2(arr, reg, 0, length - 1, order);
	for (int i = 0; i < length; i++) {
		arr[i] = reg[i];
	}
	delete[] reg;
}

template<typename T>
inline void SortAlgorithm<T>::swap(T arr[], int a, int b)
{
	T temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

template<typename T>
inline T* SortAlgorithm<T>::merge(T arr1[], T arr2[], int length1, int length2, bool order)
{
	T *temp = new T[length1 + length2];
	int i = 0, j = 0, k = 0;
	if (order) {
		while (i < length1 && j < length2) {
			temp[k++] = arr1[i] < arr2[j] ? arr1[i++] : arr2[j++];
		}
	}
	else {
		while (i < length1 && j < length2) {
			temp[k++] = arr1[i] > arr2[j] ? arr1[i++] : arr2[j++];
		}
	}
	for (; i < length1; i++, k++) {
		temp[k] = arr1[i];
	}
	for (; j < length2; j++, k++) {
		temp[k] = arr2[j];
	}
	delete[] arr1;
	delete[] arr2;
	//std::cout << "Merge: ";
	//for (int i = 0; i < length1 + length2; i++) {
	//	std::cout << temp[i] << " ";
	//}
	//std::cout << "\n";
	return temp;
}

template<typename T>
inline T* SortAlgorithm<T>::divide(T arr[], int length, int index, bool start)
{
	if (start) {
		T *temp = new T[index];
		for (int i = 0; i < index; i++) {
			temp[i] = arr[i];
		}
		return temp;
	}
	else {
		T *temp = new T[length - index];
		for (int i = 0; i < length - index; i++) {
			temp[i] = arr[index + i];
		}
		return temp;
	}
}

template<typename T>
inline void SortAlgorithm<T>::mergeSortRecursive(T arr[], T reg[], int a, int b, bool order)
{
	if (a >= b) return;
	int length = b - a;
	int mid = length / 2 + a;
	int left1 = a, right1 = mid;
	int left2 = mid + 1, right2 = b;
	mergeSortRecursive(arr, reg, left1, right1, order);
	mergeSortRecursive(arr, reg, left2, right2, order);
	int i = a;
	if (order) {
		while (left1 <= right1 && left2 <= right2) {
			if (arr[left1] < arr[left2]) {
				reg[i] = arr[left1];
				left1++;
			}
			else {
				reg[i] = arr[left2];
				left2++;
			}
			i++;
		}
	}
	else {
		while (left1 <= right1 && left2 <= right2) {
			if (arr[left1] > arr[left2]) {
				reg[i] = arr[left1];
				left1++;
			}
			else {
				reg[i] = arr[left2];
				left2++;
			}
			i++;
		}
	}
	while (left1 <= right1) {
		reg[i] = arr[left1];
		left1++;
		i++;
	}
	while (left2 <= right2) {
		reg[i] = arr[left2];
		left2++;
		i++;
	}
	for (i = a; i <= b; i++) {
		arr[i] = reg[i];
	}
}

template<typename T>
inline T* SortAlgorithm<T>::mergeSortRecursive2(T arr[], T reg[], int a, int b, bool order)
{
	if (a >= b) return arr;
	int length = b - a + 1;
	int mid = a + length / 2 - 1;
	T *temp1 = divide(arr, length, length / 2, true);
	T *temp2 = divide(arr, length, length / 2, false);
	//std::cout << a << " " << b << " " << length / 2 - 1 << " " << mid - a<< "\n";
	temp1 = mergeSortRecursive2(temp1, reg, a, mid, order);
	temp2 = mergeSortRecursive2(temp2, reg, mid + 1, b, order);
	T *merge1 = merge(temp1, temp2, length / 2, length - length / 2, order);
	for (int i = 0; i < b - a + 1; i++) {
		reg[a + i] = merge1[i];
	}
	return merge1;
}
