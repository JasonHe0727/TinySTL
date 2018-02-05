#ifndef LIST_H
#define LIST_H
#include <initializer_list>

template <typename T>
class List;

template <typename T>
class ListIterator;

template <typename T>
class List
{
public:
    List();
    ~List();
    List(int capacity);
    List(std::initializer_list<T> args);

    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);
    List(List<T>&& other);
    List<T>& operator=(List<T>&& other);

    int Count() const;
    void Add(T item);
    void Clear();
    int IndexOf(T item);
    T& At(int index) const;
    ListIterator<T> begin();
    ListIterator<T> end();
    friend class ListIterator<T>;

private:
    int capacity;
    int count;
    T* items;
    void Expand();
};

template <typename T>
List<T>::List() : capacity{0}, count{0}, items{nullptr}
{
}

template <typename T>
List<T>::~List()
{
    if (items)
    {
        delete[] items;
    }
}

template <typename T>
List<T>::List(int capacity)
    : capacity{capacity}, count{0}, items{new T[capacity]}
{
}

template <typename T>
List<T>::List(std::initializer_list<T> args)
    : capacity{static_cast<int>(args.size())}, count{capacity},
      items{new T[capacity]}
{
    int i = 0;
    for (T item : args)
    {
        items[i] = item;
        i++;
    }
}

template <typename T>
List<T>::List(const List<T>& other)
    : capacity{other.capacity}, count{other.count}, items{new T[other.capacity]}
{
    for (int i = 0; i < capacity; i++)
    {
        items[i] = other.items[i];
    }
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    capacity = other.capacity;
    count = other.count;
    items = new T[other.capacity];
    for (int i = 0; i < capacity; i++)
    {
        items[i] = other.items[i];
    }
    return *this;
}

template <typename T>
List<T>::List(List<T>&& other)
    : capacity{other.capacity}, count{other.count}, items{other.items}
{
    other.items = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& other)
{
    capacity = other.capacity;
    count = other.count;
    items = other.items;
    other.items = nullptr;
    return *this;
}

template <typename T>
int List<T>::Count() const
{
    return count;
}

template <typename T>
void List<T>::Add(T item)
{
    if (count == capacity)
    {
        Expand();
    }
    items[count] = item;
    count++;
}

template <typename T>
void List<T>::Clear()
{
    delete[] items;
    items = nullptr;
    capacity = 0;
    count = 0;
}

template <typename T>
int List<T>::IndexOf(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (items[i] == item)
        {
            return i;
        }
    }
    return (-1);
}

template <typename T>
T& List<T>::At(int index) const
{
    if (index >= 0 && index < count)
    {
        return items[index];
    }
    else
    {
        throw "index out of range";
    }
}

template <typename T>
ListIterator<T> List<T>::begin()
{
    return ListIterator<T>(*this, 0);
}

template <typename T>
ListIterator<T> List<T>::end()
{
    return ListIterator<T>(*this, count);
}

template <typename T>
void List<T>::Expand()
{
    if (capacity == 0)
    {
        items = new T[4];
        capacity = 4;
    }
    else
    {
        int newCapacity = capacity * 2;
        T* newItems = new T[newCapacity];
        for (int i = 0; i < capacity; i++)
        {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
        capacity = newCapacity;
    }
}

template <typename T>
class ListIterator
{
public:
    ListIterator(List<T>& list, int index);
    ListIterator& operator++();
    bool operator!=(ListIterator& other);
    T& operator*() const;

private:
    List<T>& list;
    int index;
};
template <typename T>
ListIterator<T>::ListIterator(List<T>& list, int index)
    : list{list}, index{index}
{
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++()
{
    index++;
    return *this;
}

template <typename T>
bool ListIterator<T>::operator!=(ListIterator<T>& other)
{
    return index != other.index;
}

template <typename T>
T& ListIterator<T>::operator*() const
{
    return list.items[index];
}
#endif // LIST_H
