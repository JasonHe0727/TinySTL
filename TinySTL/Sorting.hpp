#ifndef SORTING_H
#define SORTING_H
template <typename TCollection>
void SelectionSort(TCollection& collection);

template <typename TCollection>
void Swap(TCollection& collection, int i, int j);

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
        Swap(collection, i, min);
    }
}

template <typename TCollection>
void Swap(TCollection& collection, int i, int j)
{
    auto temp = collection.At(i);
    collection.At(i) = collection.At(j);
    collection.At(j) = temp;
}
#endif // SORTING_H
