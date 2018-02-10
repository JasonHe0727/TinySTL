#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "Sorting.hpp"
template <typename TCollection, typename T>
T QuickSelect(TCollection& collection, int k);

template <typename TCollection, typename T>
T QuickSelect(TCollection& collection, int k)
{
    Shuffle(collection);
    int low  = 0;
    int high = collection.Count() - 1;
    while (high > low)
    {
        int j = Partition(collection, low, high);
        if (j < k)
        {
            low = j + 1;
        }
        else if (j > k)
        {
            high = j - 1;
        }
        else
        {
            return collection.At(k);
        }
    }
    return collection.At(k);
}

#endif // SELECTION_HPP
