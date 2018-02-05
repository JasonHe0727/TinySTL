#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue;
template <typename T>
class QueueIterator;

template <typename T>
class Queue
{
public:
    Queue();
    ~Queue();

    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    Queue(Queue<T>&& other);
    Queue<T>& operator=(Queue<T>&& other);

    void Enqueue(T item);
    T Dequeue();
    bool IsEmpty() const;
    bool IsFull() const;
    int Count() const;
    T& Peek() const;
    QueueIterator<T> begin();
    QueueIterator<T> end();
    friend class QueueIterator<T>;

private:
    int capacity;
    int front;
    int rear;
    T* items;
    void Expand();
};

template <typename T>
Queue<T>::Queue() : capacity{0}, front{0}, rear{0}, items{nullptr}
{
}

template <typename T>
Queue<T>::~Queue()
{
    if (items)
    {
        delete[] items;
    }
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other)
    : capacity{other.capacity}, front{other.front}, rear{other.rear},
      items{new T[other.capacity]}
{
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = other.items[i];
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    capacity = other.capacity;
    front = other.front;
    rear = other.rear;
    items = new T[other.capacity];
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = other.items[i];
    }
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other)
    : capacity{other.capacity}, front{other.front}, rear{other.rear},
      items{other.items}
{
    other.items = nullptr;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other)
{
    capacity = other.capacity;
    front = other.front;
    rear = other.rear;
    items = other.items;
    other.items = nullptr;
}

template <typename T>
void Queue<T>::Enqueue(T item)
{
    if (capacity == 0 || IsFull())
    {
        Expand();
    }
    items[rear] = item;
    rear = (rear + 1) % capacity;
}

template <typename T>
T Queue<T>::Dequeue()
{
    if (IsEmpty())
    {
        throw "The queue is empty";
    }
    else
    {
        T item = items[front];
        front = (front + 1) % capacity;
        return item;
    }
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

template <typename T>
bool Queue<T>::IsFull() const
{
    return ((rear + 1) % capacity) == front;
}

template <typename T>
int Queue<T>::Count() const
{
    return (rear - front + capacity) % capacity;
}

template <typename T>
T& Queue<T>::Peek() const
{
    return items[rear];
}

template <typename T>
QueueIterator<T> Queue<T>::begin()
{
    return QueueIterator<T>(*this, front);
}

template <typename T>
QueueIterator<T> Queue<T>::end()
{
    return QueueIterator<T>(*this, rear);
}

template <typename T>
void Queue<T>::Expand()
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
class QueueIterator
{
public:
    QueueIterator(Queue<T>& queue, int index);
    QueueIterator<T>& operator++();
    bool operator!=(QueueIterator<T>& other);
    T& operator*() const;

private:
    Queue<T>& queue;
    int index;
};
template <typename T>
QueueIterator<T>::QueueIterator(Queue<T>& queue, int index)
    : queue{queue}, index{index}
{
}

template <typename T>
QueueIterator<T>& QueueIterator<T>::operator++()
{
    index = (index + 1) % queue.capacity;
    return *this;
}

template <typename T>
bool QueueIterator<T>::operator!=(QueueIterator<T>& other)
{
    return index != other.index;
}

template <typename T>
T& QueueIterator<T>::operator*() const
{
    return queue.items[index];
}

#endif // QUEUE_H
