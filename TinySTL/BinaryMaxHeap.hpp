#ifndef BINARYMAXHEAP_HPP
#define BINARYMAXHEAP_HPP
#include "KeyValuePair.hpp"
#include "List.hpp"
template <typename TKey, typename TValue>
class BinaryMaxHeap;

template <typename TKey, typename TValue>
class BinaryMaxHeap
{
public:
    BinaryMaxHeap();
    void Insert(TKey key, TValue value);
    void DeleteMax();
    List<KeyValuePair<TKey, TValue>>& GetHeap();
    KeyValuePair<TKey, TValue> GetMax();

private:
    List<KeyValuePair<TKey, TValue>> heap;
    void Swim(int k);
    bool Less(int k1, int k2);
    void Exchange(int k1, int k2);
    void Sink(int k);
};

template <typename TKey, typename TValue>
BinaryMaxHeap<TKey, TValue>::BinaryMaxHeap()
{
}

template <typename TKey, typename TValue>
void BinaryMaxHeap<TKey, TValue>::Insert(TKey key, TValue value)
{
    int n = heap.Count();
    heap.Add(KeyValuePair<TKey, TValue>(key, value));
    Swim(n);
}

template <typename TKey, typename TValue>
void BinaryMaxHeap<TKey, TValue>::DeleteMax()
{
    Exchange(0, heap.Count() - 1);
    heap.Pop();
    Sink(0);
}

template <typename TKey, typename TValue>
List<KeyValuePair<TKey, TValue>>& BinaryMaxHeap<TKey, TValue>::GetHeap()
{
    return heap;
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue> BinaryMaxHeap<TKey, TValue>::GetMax()
{
    return heap.At(0);
}

template <typename TKey, typename TValue>
void BinaryMaxHeap<TKey, TValue>::Swim(int k)
{
    /* The binary heap is counting from zero */
    while (k > 0 && Less((k - 1) / 2, k))
    {
        Exchange(k, (k - 1) / 2);
        k = (k - 1) / 2;
    }
}

template <typename TKey, typename TValue>
bool BinaryMaxHeap<TKey, TValue>::Less(int k1, int k2)
{
    return heap.At(k1).Key() < heap.At(k2).Key();
}

template <typename TKey, typename TValue>
void BinaryMaxHeap<TKey, TValue>::Exchange(int k1, int k2)
{
    KeyValuePair<TKey, TValue> t = heap.At(k1);
    heap.At(k1) = heap.At(k2);
    heap.At(k2) = t;
}

template <typename TKey, typename TValue>
void BinaryMaxHeap<TKey, TValue>::Sink(int k)
{
    int n = heap.Count();
    while (2 * k + 1 < n)
    {
        int j = 2 * k + 1;
        if (j < n && Less(j, j + 1))
        {
            j++;
        }
        if (!Less(k, j))
        {
            break;
        }
        else
        {
            Exchange(k, j);
            k = j;
        }
    }
}
#endif // BINARYMAXHEAP_HPP
