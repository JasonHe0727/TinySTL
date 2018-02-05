#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename TKey, typename TValue>
class Dictionary;
template <typename TValue>
class Dictionary<int, TValue>;
template <typename TKey, typename TValue>
class KeyValuePair;
template <typename TKey, typename TValue>
class DictionaryIterator;

template <typename TKey, typename TValue>
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    void Add(TKey key, TValue value);
    TValue& At(TKey key) const;
    DictionaryIterator<TKey, TValue> begin();
    DictionaryIterator<TKey, TValue> end();
    friend class KeyValuePair<TKey, TValue>;
    friend class DictionaryIterator<TKey, TValue>;

private:
    int capacity;
    int count;
    KeyValuePair<TKey, TValue>* items;
};

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::Dictionary() : capacity{0}, count{0}, items{nullptr}
{
}

template <typename TKey, typename TValue>
Dictionary<TKey, TValue>::~Dictionary()
{
    if (items)
    {
        delete[] items;
    }
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

template <typename TValue>
class Dictionary<int, TValue>
{
public:
    Dictionary();
    Dictionary(int capacity);
    ~Dictionary();

    Dictionary(const Dictionary<int, TValue>& other);
    Dictionary<int, TValue>& operator=(const Dictionary<int, TValue>& other);
    Dictionary(Dictionary<int, TValue>&& other);
    Dictionary<int, TValue>& operator=(Dictionary<int, TValue>&& other);

    void Add(int key, TValue value);
    void Remove(int key);
    TValue& At(int key) const;
    int Capacity() const;
    int Count() const;
    DictionaryIterator<int, TValue> begin();
    DictionaryIterator<int, TValue> end();
    friend class KeyValuePair<int, TValue>;
    friend class DictionaryIterator<int, TValue>;

private:
    int capacity;
    int count;
    KeyValuePair<int, TValue>** items;
    void AddToItems(int key, TValue value, int capacity,
                    KeyValuePair<int, TValue>** items);
    void Expand();
};

template <typename TValue>
Dictionary<int, TValue>::Dictionary() : capacity{0}, count{0}, items{nullptr}
{
}

template <typename TValue>
Dictionary<int, TValue>::Dictionary(int capacity)
    : capacity{0}, count{0}, items{new KeyValuePair<int, TValue>*[capacity]}
{
    for (int i = 0; i < capacity; i++)
    {
        items[i] = nullptr;
    }
}

template <typename TValue>
Dictionary<int, TValue>::~Dictionary()
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

template <typename TValue>
Dictionary<int, TValue>::Dictionary(const Dictionary<int, TValue>& other)
    : capacity{other.capacity}, count{other.count},
      items{new TValue[other.capacity]}
{
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = nullptr;
    }
    for (const KeyValuePair<int, TValue>& item : other)
    {
        AddToItems(item.key, item.value, capacity, items);
    }
}

template <typename TValue>
Dictionary<int, TValue>& Dictionary<int, TValue>::
    operator=(const Dictionary<int, TValue>& other)
{
    capacity = other.capacity;
    count = other.count;
    items = new TValue[other.capacity];
    for (int i = 0; i < other.capacity; i++)
    {
        items[i] = nullptr;
    }
    for (const KeyValuePair<int, TValue>& item : other)
    {
        AddToItems(item.key, item.value, capacity, items);
    }
}

template <typename TValue>
Dictionary<int, TValue>::Dictionary(Dictionary<int, TValue>&& other)
    : capacity{other.capacity}, count{other.count}, items{other.items}
{
    other.items = nullptr;
}

template <typename TValue>
Dictionary<int, TValue>& Dictionary<int, TValue>::
    operator=(Dictionary<int, TValue>&& other)
{
    capacity = other.capacity;
    count = other.count;
    items = other.items;
    other.items = nullptr;
}

template <typename TValue>
void Dictionary<int, TValue>::Add(int key, TValue value)
{
    if (count == capacity) /* load factor = 1 */
    {
        Expand();
    }
    AddToItems(key, value, capacity, items);
}

template <typename TValue>
void Dictionary<int, TValue>::Remove(int key)
{
    int index = key % capacity;
    KeyValuePair<int, TValue>* current = items[index];
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
        KeyValuePair<int, TValue>* previous = current;
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

template <typename TValue>
int Dictionary<int, TValue>::Capacity() const
{
    return capacity;
}

template <typename TValue>
int Dictionary<int, TValue>::Count() const
{
    return count;
}

template <typename TValue>
TValue& Dictionary<int, TValue>::At(int key) const
{
    int index = key % capacity;
    KeyValuePair<int, TValue>* current = items[index];
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

template <typename TValue>
DictionaryIterator<int, TValue> Dictionary<int, TValue>::begin()
{
    if (count == 0)
    {
        return DictionaryIterator<int, TValue>(*this, -1, nullptr);
    }
    else
    {
        for (int i = 0; i < capacity; i++)
        {
            if (items[i] != nullptr)
            {
                return DictionaryIterator<int, TValue>(*this, i, items[i]);
            }
        }
        return DictionaryIterator<int, TValue>(*this, -1, nullptr);
    }
}

template <typename TValue>
DictionaryIterator<int, TValue> Dictionary<int, TValue>::end()
{
    return DictionaryIterator<int, TValue>(*this, -1, nullptr);
}

template <typename TValue>
void Dictionary<int, TValue>::AddToItems(int key, TValue value, int capacity,
                                         KeyValuePair<int, TValue>** items)
{
    int index = key % capacity;
    KeyValuePair<int, TValue>* current = items[index];
    if (current == nullptr)
    {
        items[index] = new KeyValuePair<int, TValue>(key, value, nullptr);
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
        current->next = new KeyValuePair<int, TValue>(key, value, nullptr);
        count++;
    }
}

template <typename TValue>
void Dictionary<int, TValue>::Expand()
{
    if (capacity == 0)
    {
        capacity = 4;
        items = new KeyValuePair<int, TValue>*[capacity];
    }
    else if (count == capacity) /* load factor = 1 */
    {
        int newCapacity = capacity * 2;
        KeyValuePair<int, TValue>** newItems =
            new KeyValuePair<int, TValue>*[newCapacity];
        for (int i = 0; i < newCapacity; i++)
        {
            newItems[i] = nullptr;
        }
        for (int i = 0; i < capacity; i++)
        {
            KeyValuePair<int, TValue>* pair = items[i];
            if (pair != nullptr)
            {
                AddToItems(pair->key, pair->value, newCapacity, newItems);
                while (pair->next != nullptr)
                {
                    KeyValuePair<int, TValue>* next = pair->next;
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
class KeyValuePair
{
public:
    ~KeyValuePair();
    const TKey& Key() const;
    const TValue& Value() const;
    friend class Dictionary<TKey, TValue>;
    friend class DictionaryIterator<TKey, TValue>;
    KeyValuePair(const KeyValuePair<TKey, TValue>& other) = delete;
    KeyValuePair<TKey, TValue>&
        operator=(const KeyValuePair<TKey, TValue>& other) = delete;
    KeyValuePair(KeyValuePair<TKey, TValue>&& other);
    KeyValuePair<TKey, TValue>& operator=(KeyValuePair<TKey, TValue>&& other);

private:
    KeyValuePair(TKey key, TValue value, KeyValuePair* next);
    TKey key;
    TValue value;
    KeyValuePair* next;
};
template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::KeyValuePair(TKey key, TValue value,
                                         KeyValuePair* next)
    : key{key}, value{value}, next{next}
{
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::~KeyValuePair()
{
    if (next)
    {
        delete next;
    }
}

template <typename TKey, typename TValue>
const TKey& KeyValuePair<TKey, TValue>::Key() const
{
    return key;
}

template <typename TKey, typename TValue>
const TValue& KeyValuePair<TKey, TValue>::Value() const
{
    return value;
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::KeyValuePair(KeyValuePair<TKey, TValue>&& other)
    : key{other.key}, value{other.value}, next{other.next}
{
    other.next = nullptr;
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::
    operator=(KeyValuePair<TKey, TValue>&& other)
{
    key = other.key;
    value = other.value;
    next = other.next;
    other.next = nullptr;
    return *this;
}

template <typename TKey, typename TValue>
class DictionaryIterator
{
public:
    DictionaryIterator(Dictionary<TKey, TValue>& dictionary, int index,
                       KeyValuePair<TKey, TValue>* current);
    DictionaryIterator<TKey, TValue>& operator++();
    bool operator!=(DictionaryIterator<TKey, TValue>& other);
    KeyValuePair<TKey, TValue>& operator*();

private:
    Dictionary<TKey, TValue>& dictionary;
    int index;
    KeyValuePair<TKey, TValue>* current;
};

template <typename TKey, typename TValue>
DictionaryIterator<TKey, TValue>::DictionaryIterator(
    Dictionary<TKey, TValue>& dictionary, int index,
    KeyValuePair<TKey, TValue>* current)
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
KeyValuePair<TKey, TValue>& DictionaryIterator<TKey, TValue>::operator*()
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
