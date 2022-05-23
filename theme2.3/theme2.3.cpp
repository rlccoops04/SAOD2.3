#include <iostream>
#include <string>

using namespace std;
struct ListItem
{
	int data;
	ListItem* pNext;
};
void pushItem(ListItem* Item, int data)
{
	while (Item->pNext != nullptr)
	{
		Item = Item->pNext;
	}
	Item->pNext = new ListItem;
	Item->pNext->data = data;
	Item->pNext->pNext = nullptr;
}
void ClearList(ListItem* head)
{
	while (head != NULL)
	{
		ListItem* tmp = head;
		head = head->pNext;
		delete tmp;
	}
}
void displayarr(int* MainArr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << MainArr[i] << " ";
	}
	std::cout << endl;
}
int searchMaxElement(int* arr, int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}
void displayBucket(ListItem* arr, int size)
{
	cout << "Отсортированный массив: " << endl;
	for (int i = 0; i < size; i++)
	{
		ListItem* pCurrent = arr[i].pNext;
		while (pCurrent != nullptr)
		{
			cout << pCurrent->data << " ";
			pCurrent = pCurrent->pNext;
		}
	}
	cout << endl;
}
void randomArray(int* currentArray, int size)
{
	int temp;
	for (int i = 0; i < size; i++)
	{
		int k = rand() % size;
		temp = currentArray[k];
		currentArray[k] = currentArray[i];
		currentArray[i] = temp;
	}
}
void fillunic(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i;
	}
	randomArray(arr, size);
}
void BucketSortingWithArr(int* mainArr, int size, int& exchanges)
{
	int* SortedArr = new int[size];
	for (int i = 0; i < size; i++)
	{
		SortedArr[mainArr[i]] = mainArr[i];
		exchanges++;
	}
	std::cout << "Отсортированный массив: " << endl;
	displayarr(SortedArr, size);
	cout << endl;
}
void BucketSorting(int* SortedArr, int size, int& exchanges, int& compares)
{
	int temp;
	for (int i = 0; i < size; i++)
	{
		while (SortedArr[i] != i)
		{
			compares++;
			temp = SortedArr[i];
			SortedArr[i] = SortedArr[SortedArr[i]];
			SortedArr[temp] = temp;
			exchanges++;
		}
		compares++;
	}
	std::cout << "Отсортированный массив: " << endl;
	displayarr(SortedArr, size);
	cout << endl;
}
void GeneralBucketSorting(int* MainArr, int size, int& exchanges, int& compares)
{
	ListItem* SortedArr = new ListItem[size];
	for (int i = 0; i < size; i++)
	{
		SortedArr[i].pNext = nullptr;
	}
	for (int i = 0; i < size; i++)
	{
		pushItem(&SortedArr[MainArr[i]], MainArr[i]);
		exchanges++;
	}
	displayBucket(SortedArr, size);
	for (int i = 0; i < size; i++)
	{
		ClearList(SortedArr[i].pNext);
	}
	delete[] SortedArr;
}
void RadixSorting(int* arr, int& countExchanges, int size)
{
	ListItem* SortedArr = new ListItem[10];
	ListItem* pCurrent;
	int k = 0;
	int max = searchMaxElement(arr, size);
	while (max >= 1)
	{
		max /= 10;
		k++;
	}
	int pow = 1;
	for (int i = 0; i < k; i++, pow *= 10)
	{
		for (int j = 0; j < 10; j++)
		{
			SortedArr[j].pNext = nullptr;
		}
		for (int m = 0; m < size; m++)
		{
			pushItem(&SortedArr[arr[m] % (pow * 10) / pow], arr[m]);
			countExchanges++;
		}
		int j = 0;
		for (int z = 0; z < 10; z++)
		{
			pCurrent = SortedArr[z].pNext;
			while (pCurrent != nullptr)
			{
				arr[j] = pCurrent->data;
				pCurrent = pCurrent->pNext;
				j++;
			}
		}
	}
	displayarr(arr, size);
}
void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int compares, exchanges;
	bool menu = true;
	int choicemenu, choicesimplesort;
	int size;
	int* MainArr = NULL;
	int max;
	while (menu)
	{
		compares = 0; exchanges = 0;
		cout << "1. Простейшая карманная сортировка с использованием второго массива.\n";
		cout << "2. Простейшая карманная сортировка без использованием второго массива.\n";
		cout << "3. Обобщённая карманная сортировка.\n";
		cout << "4. Поразрядная сортировка.\n";
		cout << "5. Выход\n";
		cout << "Ввод: ";
		cin >> choicemenu;
		switch (choicemenu)
		{
		case 1:
			std::cout << "Введите размер массива: ";
			cin >> size;
			MainArr = new int[size];
			fillunic(MainArr, size);
			std::cout << "\nСгенерированный массив : " << endl;
			displayarr(MainArr, size);
			BucketSortingWithArr(MainArr, size, exchanges);
			cout << "Количество сравнений " << compares << ", количество перессылок " << exchanges << endl << endl;
			delete[] MainArr;
			break;
		case 2:
			std::cout << "Введите размер массива: ";
			cin >> size;
			MainArr = new int[size];
			fillunic(MainArr, size);
			std::cout << "\nСгенерированный массив : " << endl;
			displayarr(MainArr, size);
			BucketSorting(MainArr, size, exchanges, compares);
			cout << "Количество сравнений " << compares << ", количество перессылок " << exchanges << endl << endl;
			delete[] MainArr;
			break;
		case 3:
			std::cout << "Введите размер массива: ";
			cin >> size;
			MainArr = new int[size];
			for (int i = 0; i < size; i++)
			{
				MainArr[i] = rand() % size;
			}
			std::cout << "\nСгенерированный массив : " << endl;
			displayarr(MainArr, size);
			GeneralBucketSorting(MainArr, size, exchanges, compares);
			cout << "Количество сравнений " << compares << ", количество перессылок " << exchanges << endl << endl;
			break;
		case 4:
			std::cout << "Введите размер массива: ";
			cin >> size;
			MainArr = new int[size];
			std::cout << "Введите наибольший элемент: ";
			cin >> max;
			for (int i = 0; i < size; i++)
			{
				MainArr[i] = rand() % max;
			}
			std::cout << "\nСгенерированный массив : " << endl;
			displayarr(MainArr, size);
			RadixSorting(MainArr, exchanges, size);
			cout << "Количество сравнений " << compares << ", количество перессылок " << exchanges << endl << endl;
			break;
		default:
			menu = false;
			break;
		}
	}
}