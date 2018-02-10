#ifndef DICTIONARY_H
#define DICTIONARY_H
template <typename TKey, typename TValue>
class Dictionary;
template <typename TKey, typename TValue>
class DictionaryKeyValuePair;
template <typename TKey, typename TValue>
class DictionaryIterator;

int GetHashCode(int key);

template <typename TKey, typename TValue>
class Dictionary
{
public:
    Dictionary();
    Dictionary(int capacity);
    ~Dictionary();

    Dictionary(const Dictionary<TKey, TValue>& other);
    Dictionary<TKey, TValue>& operator=(const Dictionary<TKey, TValue>& other);
    Dictionary(Dictionary<TKey, TValue>&& other);
    Dictionary<TKey, TValue>& operator=(Dictionary<TKey, TValue>&& other);

    void Add(TKey key, TValue value);
    void Remove(TKey key);
    TValue& At(TKey key) const;
    int Capacity() const;
    int Count() const;
    bool ContainsKey(TKey key);
    DictionaryIterator<TKey, TValue> begin();
    DictionaryIterator<TKey, TValue> end();
    friend class DictionaryKeyValuePair<TKey, TValue>;
    friend class DictionaryIterator<TKey, TValue>;

private:
    int capacity;
    int count;
    DictionaryKeyValuePair<TKey, TValue>** items;
    void AddToItems(TKey key, TValue value, int capacity,
                    DictionaryKeyValuePair<TKey, TValue>** items);
    void Expand();
};

template <typename TKey, typename TValue>
class DictionaryKeyValuePair
{
public:
    ~DictionaryKeyValuePair();
    const TKey& Key() const;
    const TValue& Value() const;
    friend class Dictionary<TKey, TValue>;
    friend class DictionaryIterator<TKey, TValue>;
    DictionaryKeyValuePair(const DictionaryKeyValuePair<TKey, TValue>& other) =
        delete;
    DictionaryKeyValuePair<TKey, TValue>&
        operator=(const DictionaryKeyValuePair<TKey, TValue>& other) = delete;
    DictionaryKeyValuePair(DictionaryKeyValuePair<TKey, TValue>&& other);
    DictionaryKeyValuePair<TKey, TValue>&
        operator=(DictionaryKeyValuePair<TKey, TValue>&& other);

private:
    DictionaryKeyValuePair(TKey key, TValue value,
                           DictionaryKeyValuePair* next);
    TKey key;
    TValue value;
    DictionaryKeyValuePair* next;
};

template <typename TKey, typename TValue>
class DictionaryIterator
{
public:
    DictionaryIterator(Dictionary<TKey, TValue>& dictionary, int index,
                       DictionaryKeyValuePair<TKey, TValue>* current);
    DictionaryIterator<TKey, TValue>& operator++();
    bool operator!=(DictionaryIterator<TKey, TValue>& other);
    DictionaryKeyValuePair<TKey, TValue>& operator*();

private:
    Dictionary<TKey, TValue>& dictionary;
    int index;
    DictionaryKeyValuePair<TKey, TValue>* current;
};

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::Dictionary() : capacity{0}, count{0}, items{nullptr}
{
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::Dictionary(int capacity)
    : capacity{0}, count{0},
      items{new DictionaryKeyValuePair<TKey, TValue>*[capacity]}
{
    for (int i = 0; i < capacity; i++)
    {
        items[i] = nullptr;
    }
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::~Dictionary()
{
    if (items)
    {
        for (int i = 0; i < capacity; i++)
        {
            if (items[i])
            {
                delete items[i];
            }
        }
        delete[] items;
    }
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::Dictionary(const Dictionary<TKey, TValue>& other)
    : capacity{other.capacity}, count{other.count},
      items{new TValue[other.capacity]}
{
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = nullptr;
    }
    for (const DictionaryKeyValuePair<TKey, TValue>& item : other)
    {
        AddToItems(item.key, item.value, capacity, items);
    }
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>& Dictionary<TKey, TValue>::
    operator=(const Dictionary<TKey, TValue>& other)
{
    capacity = other.capacity;
    count = other.count;
    items = new TValue[other.capacity];
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = nullptr;
    }
    for (const DictionaryKeyValuePair<TKey, TValue>& item : other)
    {
        AddToItems(item.key, item.value, capacity, items);
    }
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::Dictionary(Dictionary<TKey, TValue>&& other)
    : capacity{other.capacity}, count{other.count}, items{other.items}
{
    other.items = nullptr;
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>& Dictionary<TKey, TValue>::
    operator=(Dictionary<TKey, TValue>&& other)
{
    capacity = other.capacity;
    count = other.count;
    items = other.items;
    other.items = nullptr;
}

template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Add(TKey key, TValue value)
{
    if (count == capacity) /* load factor = 1 */
    {
        Expand();
    }
    AddToItems(key, value, capacity, items);
}

template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Remove(TKey key)
{
    int index = GetHashCode(key) % capacity;
    DictionaryKeyValuePair<TKey, TValue>* current = items[index];
    if (current == nullptr)
    {
        throw "key is not found";
    }
    else if (current->key == key)
    {
        items[index] = current->next;
        delete current;
    }
    else
    {
        DictionaryKeyValuePair<TKey, TValue>* previous = current;
        current = previous->next;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                previous->next = current->next;
                delete current;
                return;
            }
        }
        throw "key is not found";
    }
}

template <typename TKey, typename TValue>
int Dictionary<TKey, TValue>::Capacity() const
{
    return capacity;
}

template <typename TKey, typename TValue>
int Dictionary<TKey, TValue>::Count() const
{
    return count;
}

template <typename TKey, typename TValue>
bool Dictionary<TKey, TValue>::ContainsKey(TKey key)
{
    int index = GetHashCode(key) % capacity;
    DictionaryKeyValuePair<TKey, TValue>* current = items[index];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }
    return false;
}

template <typename TKey, typename TValue>
TValue& Dictionary<TKey, TValue>::At(TKey key) const
{
    int index = GetHashCode(key) % capacity;
    DictionaryKeyValuePair<TKey, TValue>* current = items[index];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current->value;
        }
        else
        {
            current = current->next;
        }
    }
    throw "The key does not exist";
}

template <typename TKey, typename TValue>
DictionaryIterator<TKey, TValue> Dictionary<TKey, TValue>::begin()
{
    if (count == 0)
    {
        return DictionaryIterator<TKey, TValue>(*this, -1, nullptr);
    }
    else
    {
        for (int i = 0; i < capacity; i++)
        {
            if (items[i] != nullptr)
            {
                return DictionaryIterator<TKey, TValue>(*this, i, items[i]);
            }
        }
        return DictionaryIterator<TKey, TValue>(*this, -1, nullptr);
    }
}

template <typename TKey, typename TValue>
DictionaryIterator<TKey, TValue> Dictionary<TKey, TValue>::end()
{
    return DictionaryIterator<TKey, TValue>(*this, -1, nullptr);
}

template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::AddToItems(
    TKey key, TValue value, int capacity,
    DictionaryKeyValuePair<TKey, TValue>** items)
{
    int index = GetHashCode(key) % capacity;
    DictionaryKeyValuePair<TKey, TValue>* current = items[index];
    if (current == nullptr)
    {
        items[index] =
            new DictionaryKeyValuePair<TKey, TValue>(key, value, nullptr);
        count++;
    }
    else if (current->key == key)
    {
        throw "duplicative key";
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
            if (current->key == key)
            {
                throw "duplicative key";
            }
        }
        current->next =
            new DictionaryKeyValuePair<TKey, TValue>(key, value, nullptr);
        count++;
    }
}

template <typename TKey, typename TValue>
void Dictionary<TKey, TValue>::Expand()
{
    if (capacity == 0)
    {
        capacity = 4;
        items = new DictionaryKeyValuePair<TKey, TValue>*[capacity];
    }
    else if (count == capacity) /* load factor = 1 */
    {
        int newCapacity = capacity * 2;
        DictionaryKeyValuePair<TKey, TValue>** newItems =
            new DictionaryKeyValuePair<TKey, TValue>*[newCapacity];
        for (int i = 0; i < newCapacity; i++)
        {
            newItems[i] = nullptr;
        }
        for (int i = 0; i < capacity; i++)
        {
            DictionaryKeyValuePair<TKey, TValue>* pair = items[i];
            if (pair != nullptr)
            {
                AddToItems(pair->key, pair->value, newCapacity, newItems);
                while (pair->next != nullptr)
                {
                    DictionaryKeyValuePair<TKey, TValue>* next = pair->next;
                    AddToItems(next->key, next->value, newCapacity, newItems);
                    pair = next;
                }
            }
        }
        capacity = newCapacity;
        delete[] items;
        items = newItems;
    }
}

template <typename TKey, typename TValue>
DictionaryKeyValuePair<TKey, TValue>::DictionaryKeyValuePair(
    TKey key, TValue value, DictionaryKeyValuePair* next)
    : key{key}, value{value}, next{next}
{
}

template <typename TKey, typename TValue>
DictionaryKeyValuePair<TKey, TValue>::~DictionaryKeyValuePair()
{
    if (next)
    {
        delete next;
    }
}

template <typename TKey, typename TValue>
const TKey& DictionaryKeyValuePair<TKey, TValue>::Key() const
{
    return key;
}

template <typename TKey, typename TValue>
const TValue& DictionaryKeyValuePair<TKey, TValue>::Value() const
{
    return value;
}

template <typename TKey, typename TValue>
DictionaryKeyValuePair<TKey, TValue>::DictionaryKeyValuePair(
    DictionaryKeyValuePair<TKey, TValue>&& other)
    : key{other.key}, value{other.value}, next{other.next}
{
    other.next = nullptr;
}

template <typename TKey, typename TValue>
DictionaryKeyValuePair<TKey, TValue>& DictionaryKeyValuePair<TKey, TValue>::
    operator=(DictionaryKeyValuePair<TKey, TValue>&& other)
{
    key = other.key;
    value = other.value;
    next = other.next;
    other.next = nullptr;
    return *this;
}

template <typename TKey, typename TValue>
DictionaryIterator<TKey, TValue>::DictionaryIterator(
    Dictionary<TKey, TValue>& dictionary, int index,
    DictionaryKeyValuePair<TKey, TValue>* current)
    : dictionary{dictionary}, index{index}, current{current}
{
}

template <typename TKey, typename TValue>
DictionaryIterator<TKey, TValue>& DictionaryIterator<TKey, TValue>::operator++()
{
    if (index == -1)
    {
        return *this;
    }
    else if (current->next != nullptr)
    {
        current = current->next;
        return *this;
    }
    else
    {
        index++;
        if (index == dictionary.capacity)
        {
            index = -1;
            current = nullptr;
            return *this;
        }
        else
        {
            while (index < dictionary.capacity)
            {
                if (dictionary.items[index] != nullptr)
                {
                    current = dictionary.items[index];
                    return *this;
                }
                index++;
            }
            index = -1;
            current = nullptr;
            return *this;
        }
    }
}

template <typename TKey, typename TValue>
bool DictionaryIterator<TKey, TValue>::
    operator!=(DictionaryIterator<TKey, TValue>& other)
{
    return index != other.index || current != other.current;
}

template <typename TKey, typename TValue>
DictionaryKeyValuePair<TKey, TValue>& DictionaryIterator<TKey, TValue>::
    operator*()
{
    if (index == -1)
    {
        throw "cannot get key value pair";
    }
    else
    {
        return *current;
    }
}
#endif // DICTIONARY_H
