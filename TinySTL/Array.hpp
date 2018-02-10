#ifndef ARRAY_H
#define ARRAY_H
#include <initializer_list>
template <typename T>
class Array;
template <typename T>
class ArrayIterator;

template <typename T>
class Array
{
public:
	Array();
	~Array();
	Array(int length);
	Array(std::initializer_list<T> args);

	Array(const Array<T>& other);
	Array<T>& operator=(const Array<T>& other);
	Array(Array<T>&& other);
    Array<T>& operator=(Array<T>&& other);

	int Length() const;
	int Count() const;

	T& At(int index) const;
	ArrayIterator<T> begin();
	ArrayIterator<T> end();
	friend class ArrayIterator<T>;

private:
	int length;
	T* items;
};

template <typename T>
class ArrayIterator
{
public:
	ArrayIterator(Array<T>& array, int index);
	ArrayIterator<T>& operator++();
	bool operator!=(ArrayIterator<T>& other);
	T& operator*() const;

private:
	Array<T>& array;
	int index;
};

template <typename T>
Array<T>::Array() : length{0}, items{nullptr}
{
}

template <typename T>
Array<T>::~Array()
{
    if (items)
	{
		delete[] items;
	}
}

template <typename T>
Array<T>::Array(int length) : length{length}, items{new T[length]}
{
}

template <typename T>
Array<T>::Array(std::initializer_list<T> args)
    : length{static_cast<int>(args.size())}, items{new T[length]}
{
	int i = 0;
    for (T item : args)
	{
        items[i] = item;
		i++;
	}
}

template <typename T>
Array<T>::Array(const Array<T>& other)
    : length{other.length}, items{new T[length]}
{
    for (int i = 0; i < length; i++)
	{
        items[i] = other.items[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    length = other.length;
    items = new T[length];
    for (int i = 0; i < length; i++)
	{
        items[i] = other.items[i];
	}
}

template <typename T>
Array<T>::Array(Array<T>&& other) : length{other.length}, items{other.items}
{
    other.items = nullptr;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
    length = other.length;
    items = other.items;
    other.items = nullptr;
    return *this;
}

template <typename T>
int Array<T>::Length() const
{
	return length;
}

template <typename T>
int Array<T>::Count() const
{
	return length;
}

template <typename T>
T& Array<T>::At(int index) const
{
	if (index >= 0 && index < length)
	{
		return items[index];
	}
	else
	{
        throw "index out of range";
	}
}

template <typename T>
ArrayIterator<T> Array<T>::begin()
{
	return ArrayIterator<T>(*this, 0);
}

template <typename T>
ArrayIterator<T> Array<T>::end()
{
	return ArrayIterator<T>(*this, length);
}

template <typename T>
ArrayIterator<T>::ArrayIterator(Array<T>& array, int index)
    : array{array}, index{index}
{
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator++()
{
	index++;
	return *this;
}

template <typename T>
bool ArrayIterator<T>::operator!=(ArrayIterator<T>& other)
{
    return index != other.index;
}

template <typename T>
T& ArrayIterator<T>::operator*() const
{
	return array.items[index];
}
#endif // ARRAY_H
