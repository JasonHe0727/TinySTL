#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include "Option.hpp"
#include "Exception.hpp"
#include "Hash.hpp"

template <typename TKey, typename TValue>
class DictionaryKeyIterator;

template <typename TKey, typename TValue>
class DictionaryKeyCollection;

template <typename TKey, typename TValue>
class KeyValuePair {
private:
	TKey key;
	TValue value;
public:
	KeyValuePair(const TKey& key, const TValue& value)
		: key{key}, value{value} {
	}

	inline const TKey& Key() const {
		return key;
	}

	inline const TValue& Value() const {
		return value;
	}

	inline TValue& Value() {
		return value;
	}
};

template <typename TKey, typename TValue>
class Dictionary {
private:
	int count;
	int capacity;
	KeyValuePair<TKey, TValue>** items;
	Hash<TKey> hash;
public:
	Dictionary(): count{0}, capacity{0}, items{nullptr} {
	}

	~Dictionary() {
		for(int i = 0; i < capacity; i++) {
			if(items[i] != nullptr) {
				delete items[i];
				items[i] = nullptr;
			}
		}
		delete[] items;
	}

	void Add(const TKey& key, const TValue& value) {
		if(count >= capacity) {
			if(capacity == 0) {
				Resize(4);
			} else {
				Resize(capacity * 2);
			}
		}
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] == nullptr) {
				items[index] = new KeyValuePair<TKey, TValue>(key, value);
				count++;
				return;
			} else if(items[index]->Key() == key) {
				throw DuplicateKeyException();
			}
		}
	}

	bool Remove(const TKey& key) {
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] != nullptr) {
				if(items[index]->Key() == key) {
					delete items[index];
					items[index] = nullptr;
					count--;
					if(count > 0 && count == capacity / 4) {
						Resize(capacity / 2);
					}
					return true;
				}
			}
		}
		return false;
	}

	const TValue& operator[](const TKey& key) const {
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] != nullptr) {
				if(items[index]->Key() == key) {
					return items[index]->Value();
				}
			}
		}
		throw KeyNotFoundException();
	}

	TValue& operator[](const TKey& key) {
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] != nullptr) {
				if(items[index]->Key() == key) {
					return items[index]->Value();
				}
			}
		}
		throw KeyNotFoundException();
	}

	Option<TValue> TryGetValue(const TKey& key) const {
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] != nullptr) {
				if(items[index]->Key() == key) {
					return Option<TValue>(items[index]->Value());
				}
			}
		}
		return Option<TValue>();
	}

	bool ContainsKey(const TKey& key) const {
		int hashCode = hash(key);
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			if(items[index] != nullptr) {
				if(items[index]->Key() == key) {
					return true;
				}
			}
		}
		return false;
	}

	inline int Size() const {
		return count;
	}

	DictionaryKeyCollection<TKey, TValue> Keys() const {
		return DictionaryKeyCollection<TKey, TValue>(this);
	}

	friend class DictionaryKeyIterator<TKey, TValue>;
	friend class DictionaryKeyCollection<TKey, TValue>;

private:
	void Resize(int newCapacity) {
		KeyValuePair<TKey, TValue>** newArray = new KeyValuePair<TKey, TValue>*[newCapacity];
		for(int i = 0; i < newCapacity; i++) {
			newArray[i] = nullptr;
		}
		KeyValuePair<TKey, TValue>** oldArray = items;
		int oldCapacity = capacity;
		int oldCount = count;
		capacity = newCapacity;
		items = newArray;
		count = 0;
		for(int i = 0; i < oldCount; i++) {
			if(oldArray[i] != nullptr) {
				Add(oldArray[i]->Key(), oldArray[i]->Value());
				delete oldArray[i];
			}
		}
		delete[] oldArray;
	}
};

template <typename TKey, typename TValue>
class DictionaryKeyCollection {
private:
	const Dictionary<TKey, TValue>* dictionary;
public:
	DictionaryKeyCollection(const Dictionary<TKey, TValue>* dictionary): dictionary{dictionary} {
	}

	DictionaryKeyIterator<TKey, TValue> begin() const {
		return DictionaryKeyIterator<TKey, TValue>(dictionary, 0);
	}

	DictionaryKeyIterator<TKey, TValue> end() const {
		return DictionaryKeyIterator<TKey, TValue>(dictionary, dictionary->capacity);
	}
};

template <typename TKey, typename TValue>
class DictionaryKeyIterator {
private:
	const Dictionary<TKey, TValue>* dictionary;
	int index;
public:
	DictionaryKeyIterator(const Dictionary<TKey, TValue>* dictionary, int index)
		: dictionary{dictionary}, index{index} {
	}
	bool operator!=(DictionaryKeyIterator<TKey, TValue>& other) {
		while(index < dictionary->capacity && dictionary->items[index] == nullptr) {
			index++;
		}
		return index != other.index;
	}
	const TKey& operator*() const {
		return dictionary->items[index]->Key();
	}
	DictionaryKeyIterator<TKey, TValue>& operator++() {
		index++;
		return *this;
	}
};

#endif // DICTIONARY_HPP
