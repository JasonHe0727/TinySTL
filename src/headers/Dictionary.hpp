#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include "Option.hpp"
#include "Exception.hpp"
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
struct Hash {
	int operator()(const T& input) const;
};

template <>
struct Hash<int> {
	int operator()(const int& input) const {
		if(input >= 0) {
			return input;
		} else {
			return -input;
		}
	}
};

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

	void Add(const TKey& key, const TValue& value) {
		cout << "add 1" << endl;
		if(count >= capacity) {
			if(capacity == 0) {
				Resize(4);
			} else {
				Resize(capacity * 2);
			}
		}
		cout << "add 2" << endl;
		cout << "try to compute hash code" << endl;
		cout << "key = " << endl;
		int keyInt = key;
		cout << keyInt << endl;
		int hashCode = hash(key);
		cout << "hash code = " << hashCode << endl;
		for(int i = 0; i < capacity; i++) {
			int index = (hashCode + i) % capacity;
			cout << "index = " << index << ", capacity = " << capacity << endl;
			if(items[index] == nullptr) {
				items[index] = new KeyValuePair<TKey, TValue>(key, value);
				count++;
				cout << "add 3" << endl;
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

#endif // DICTIONARY_HPP
