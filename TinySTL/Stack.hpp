#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack;

template <typename T>
class StackIterator;

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();

    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);
    Stack(Stack<T>&& other);
    Stack<T>& operator=(Stack<T>&& other);

    void Push(T item);
    T Pop();
    T& Peek() const;
    StackIterator<T> begin();
    StackIterator<T> end();
    int Count() const;
    friend class StackIterator<T>;

private:
    int capacity;
    int pointer;
    T* items;
    void Expand();
};
template <typename T>
Stack<T>::Stack() : capacity{0}, pointer{-1}, items{nullptr}
{
}

template <typename T>
Stack<T>::~Stack()
{
    if (items)
    {
        delete[] items;
    }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
    : capacity{other.capacity}, pointer{other.pointer},
      items{new T[other.capacity]}
{
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = other.items[i];
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    capacity = other.capacity;
    pointer = other.pointer;
    items = new T[other.capacity];
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = other.items[i];
    }
}

template <typename T>
Stack<T>::Stack(Stack<T>&& other)
    : capacity{other.capacity}, pointer{other.pointer}, items{other.items}
{
    other.items = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other)
{
    capacity = other.capacity;
    pointer = other.pointer;
    items = other.items;
    other.items = nullptr;
}

template <typename T>
void Stack<T>::Push(T item)
{
    pointer++;
    if (pointer == capacity)
    {
        Expand();
    }
    items[pointer] = item;
}

template <typename T>
T Stack<T>::Pop()
{
    T&& item = items[pointer];
    pointer--;
    return item;
}

template <typename T>
T& Stack<T>::Peek() const
{
    return items[pointer];
}

template <typename T>
StackIterator<T> Stack<T>::begin()
{
    return StackIterator<T>(*this, pointer);
}
template <typename T>
StackIterator<T> Stack<T>::end()
{
    return StackIterator<T>(*this, -1);
}

template <typename T>
int Stack<T>::Count() const
{
    return pointer + 1;
}
template <typename T>
void Stack<T>::Expand()
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
class StackIterator
{
public:
    StackIterator(Stack<T>& stack, int index);
    StackIterator<T>& operator++();
    bool operator!=(StackIterator<T>& other);
    T& operator*() const;

private:
    Stack<T>& stack;
    int index;
};
template <typename T>
StackIterator<T>::StackIterator(Stack<T>& stack, int index)
    : stack{stack}, index{index}
{
}

template <typename T>
StackIterator<T>& StackIterator<T>::operator++()
{
    index--;
    return *this;
}

template <typename T>
bool StackIterator<T>::operator!=(StackIterator<T>& other)
{
    return index != other.index;
}

template <typename T>
T& StackIterator<T>::operator*() const
{
    return stack.items[index];
}
#endif // STACK_H
