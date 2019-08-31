#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <initializer_list>

template <typename T>
class Array;

template <typename T>
class ArrayIterator;

template <typename T>
class Array {
private:
	int length;
	std::allocator<T> allocator;
	T* items;
public:
	Array(): length{0}, items{nullptr} {
	}

	explicit Array(int length): length{length}, items{allocator.allocate(length)} {
	}

	Array(const Array<T>& other) = delete;

	Array<T>& operator=(const Array<T>& other) = delete;

	Array(Array<T>&& other): length{other.length}, items{other.items} {
		other.length = 0;
		other.items = nullptr;
	}

	Array<T>& operator=(Array<T>&& other) {
		length = other.length;
		items = other.items;
		other.length = 0;
		other.items = nullptr;
		return *this;
	}
		
	Array(std::initializer_list<T> list): length{static_cast<int>(list.size())}, items{allocator.allocate(length)} {
		int index = 0;
		for(const T& item : list) {
			items[index] = item;
			index++;
		}
	}

	inline T& operator[](int index) {
		return items[index];
	}

	inline const T& operator[](int index) const {
		return items[index];
	}

	inline int Length() const {
		return length;
	}

	inline int Size() const {
		return length;
	}

	~Array() {
		if(items) {
			allocator.deallocate(items, length);
		}
	}

	ArrayIterator<T> begin() const {
		return ArrayIterator<T>(this, 0);
	}

	ArrayIterator<T> end() const {
		return ArrayIterator<T>(this, length);
	}

	friend class ArrayIterator<T>;
private:
	void Copy(const Array<T>& other) {
		length = other.length;
		items = allocator.allocate(length);
		for(int i = 0; i < other.length; i++) {
			items[i] = other.items[i];
		}
	}
};

template <typename T>
class ArrayIterator {
private:
	const Array<T>* array;
	int index;
public:
	ArrayIterator(const Array<T>* array, int index): array{array}, index{index} {
	}
	bool operator!=(ArrayIterator<T>& other) const {
		return index != other.index;
	}
	const T& operator*() const {
		return array->items[index];
	}
	T& operator*() {
		return array->items[index];
	}
	ArrayIterator<T>& operator++() {
		index++;
		return *this;
	}
};
#endif // ARRAY_HPP
