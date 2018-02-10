#ifndef SORTING_H
#define SORTING_H
#include "Array.hpp"
#include <chrono>
#include <random>

template <typename TCollection>
void SelectionSort(TCollection& collection);

template <typename TCollection>
void Swap(TCollection& collection, int i, int j);

template <typename TCollection>
void InsertionSort(TCollection& collection);

template <typename TCollection>
void ShellSort(TCollection& collection);

template <typename TCollection>
void Shuffle(TCollection& collection);

template <typename TCollection, typename T>
void MergeSort(TCollection& collection);

template <typename TCollection, typename T>
void MergeSortSubarray(TCollection& collection, Array<T>& aux, int low,
                       int high);

template <typename TCollection, typename T>
void Merge(TCollection& collection, Array<T>& aux, int low, int middle,
           int high);

template <typename TCollection, typename T>
void BottomUpMergeSort(TCollection& collection);

template <typename TCollection>
int Partition(TCollection& collection, int low, int high);

template <typename TCollection>
void QuickSortSubarray(TCollection& collection, int low, int high);

template <typename TCollection>
void QuickSort(TCollection& collection);

template <typename TCollection>
void SelectionSort(TCollection& collection)
{
    int n = collection.Count();
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (collection.At(j) < collection.At(min))
            {
                min = j;
            }
        }
		if (min != i)
		{
			Swap(collection, i, min);
		}
    }
}

template <typename TCollection>
void Swap(TCollection& collection, int i, int j)
{
    auto temp		 = collection.At(i);
    collection.At(i) = collection.At(j);
    collection.At(j) = temp;
}

template <typename TCollection>
void InsertionSort(TCollection& collection)
{
	int n = collection.Count();
    for (int i = 0; i < n; i++)
	{
        for (int j = i; j > 0; j--)
		{
            if (collection[j] < collection[j - 1])
			{
                Swap(collection, j, j - 1);
			}
			else
			{
				break;
			}
		}
	}
}

template <typename TCollection>
void ShellSort(TCollection& collection)
{
    int n = collection.Count();
    int h = 1;
    while (h < n / 3)
	{
        h = 3 * h + 1;
	}
    while (h >= 1)
	{
        for (int i = h; i < n; i++)
		{
            for (int j = i; j >= h && collection[j] < collection[j - h]; j -= h)
			{
                Swap(collection, j, j - h);
			}
		}
        h = h / 3;
	}
}

template <typename TCollection>
void Shuffle(TCollection& collection)
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution;
    int n = collection.Count();
    for (int i = 0; i < n; i++)
    {
        int choice = distribution(generator) % (i + 1);
        Swap(collection, i, choice);
    }
}

template <typename TCollection, typename T>
void MergeSort(TCollection& collection)
{
    Array<T> aux(collection.Count());
    MergeSortSubarray(collection, aux, 0, collection.Count() - 1);
}

template <typename TCollection, typename T>
void MergeSortSubarray(TCollection& collection, Array<T>& aux, int low,
                       int high)
{
    if (high <= low)
	{
		return;
	}
	else
	{
        int middle = low + (high - low) / 2;
        MergeSortSubarray(collection, aux, low, middle);
        MergeSortSubarray(collection, aux, middle + 1, high);
        Merge(collection, aux, low, middle, high);
	}
}

template <typename TCollection, typename T>
void Merge(TCollection& collection, Array<T>& aux, int low, int middle,
           int high)
{
    for (int k = low; k <= high; k++)
	{
        aux.At(k) = collection.At(k);
	}
    int i = low;
    int j = middle + 1;
    for (int k = low; k <= high; k++)
	{
        if (i > middle)
		{
            collection.At(k) = aux.At(j);
			j++;
		}
        else if (j > high)
		{
            collection.At(k) = aux.At(i);
			i++;
		}
        else if (aux.At(j) < aux.At(i))
		{
            collection.At(k) = aux.At(j);
			j++;
		}
		else
		{
            collection.At(k) = aux.At(i);
			i++;
		}
	}
}

template <typename TCollection, typename T>
void BottomUpMergeSort(TCollection& collection)
{
    auto min = [](int x, int y) {
        if (x < y)
        {
            return x;
        }
        else
        {
            return y;
        }
    };
    int n = collection.Count();
    Array<T> aux(n);
    for (int size = 1; size < n; size = size + size)
    {
        for (int low = 0; low < n - size; low += (size + size))
        {
            Merge(collection, aux, low, low + size - 1,
                  min(low + size + size - 1, n - 1));
        }
    }
}

template <typename TCollection>
int Partition(TCollection& collection, int low, int high)
{
    int i = low;
    int j = high + 1;
    while (true)
    {
        i++;
        while (collection.At(i) < collection.At(low))
        {
            if (i == high)
            {
                break;
            }
            else
            {
                i++;
            }
        }
        j--;
        while (collection.At(low) < collection.At(j))
        {
            if (j == low)
            {
                break;
            }
            else
            {
                j--;
            }
        }
        if (i >= j)
        {
            break;
        }
        else
        {
            Swap(collection, i, j);
        }
    }
    Swap(collection, low, j);
    return j;
}

template <typename TCollection>
void QuickSortSubarray(TCollection& collection, int low, int high)
{
    if (high <= low)
    {
        return;
    }
    else
    {
        int j = Partition(collection, low, high);
        QuickSortSubarray(collection, low, j - 1);
        QuickSortSubarray(collection, j + 1, high);
    }
}

template <typename TCollection>
void QuickSort(TCollection& collection)
{
    Shuffle(collection);
    QuickSortSubarray(collection, 0, collection.Count() - 1);
}
#endif // SORTING_H
