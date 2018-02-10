#ifndef KEYVALUEPAIR_HPP
#define KEYVALUEPAIR_HPP

template <typename TKey, typename TValue>
class KeyValuePair;
template <typename TKey, typename TValue>
class KeyValuePair
{
public:
    KeyValuePair();
    KeyValuePair(TKey key, TValue value);
    KeyValuePair(const KeyValuePair<TKey, TValue>& other);
    KeyValuePair<TKey, TValue>&
        operator=(const KeyValuePair<TKey, TValue>& other);
    const TKey& Key() const;
    const TValue& Value() const;

private:
    TKey key;
    TValue value;
};
template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::KeyValuePair()
{
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::KeyValuePair(TKey key, TValue value)
    : key{key}, value{value}
{
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>::KeyValuePair(
    const KeyValuePair<TKey, TValue>& other)
    : key{other.key}, value{other.value}
{
}

template <typename TKey, typename TValue>
KeyValuePair<TKey, TValue>& KeyValuePair<TKey, TValue>::
    operator=(const KeyValuePair<TKey, TValue>& other)
{
    key = other.key;
    value = other.value;
    return *this;
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
#endif // KEYVALUEPAIR_HPP
