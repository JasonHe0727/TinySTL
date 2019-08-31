#ifndef List_HPP
#define List_HPP

#include <memory>
#include <limits>
#include <initializer_list>

template <typename T>
class ListIterator;

template <typename T>
class List {
private:
	int count; // the count of elements
	int capacity; // the length of the array
	T* items;
	std::allocator<T> allocator;
public:
	List(): count{0}, capacity{0}, items{nullptr} {
	}

	explicit List(int capacity): count{0}, capacity{capacity}, items(allocator.allocate(count)) {
	}

	List(const List<T>& other) = delete;

	List<T>& operator=(const List<T>& other) = delete;

	List(List<T>&& other): count{other.count}, capacity{other.capacity},
		items(other.items) {
		other.count = 0;
		other.capacity = 0;
		other.items = nullptr;
	}

	List<T>& operator=(List<T>&& other) {
		count = other.count;
		capacity = other.capacity;
		items = other.items;
		other.count = 0;
		other.capacity = 0;
		other.items = nullptr;
		return *this;
	}

	List(std::initializer_list<T> list) {
		count = static_cast<int>(list.size());
		capacity = count;
		items = allocator.allocate(count);
		int index = 0;
		for(const T& item : list) {
			items[index] = item;
			index++;
		}
	}

	void Add(const T& item) {
		if(count == capacity) {
			if(capacity == 0) {
				items = allocator.allocate(4);
				capacity = 4;
			} else {
				if(capacity >= std::numeric_limits<int>::max() / 2) {
					Resize(std::numeric_limits<int>::max());
				} else {
					Resize(capacity * 2);
				}
			}
		}
		items[count] = item;
		count++;
	}

	void Pop() {
		count--;
		items[count] = T();
		if(count > 0 && count == capacity / 4) {
			Resize(capacity / 2);
		}
	}

	inline int Count() const {
		return count;
	}

	inline int Size() const {
		return count;
	}

	inline T& operator[](int index) {
		return items[index];
	}

	inline const T& operator[](int index) const {
		return items[index];
	}

	ListIterator<T> begin() const {
		return ListIterator<T>(this, 0);
	}

	ListIterator<T> end() const {
		return ListIterator<T>(this, count);
	}

	friend class ListIterator<T>;
private:
	void Resize(int maxSize) {
		T* array = allocator.allocate(maxSize);
		for(int i = 0; i < count; i++) {
			array[i] = items[i];
		}
		allocator.deallocate(items, capacity);
		items = array;
		capacity = maxSize;
	}
};

template <typename T>
class ListIterator {
private:
	const List<T>* list;
	int index;
public:
	ListIterator(const List<T>* list, int index): list{list}, index{index} {
	}
	bool operator!=(ListIterator<T>& other) const {
		return index != other.index;
	}
	const T& operator*() const {
		return list->items[index];
	}
	T& operator*() {
		return list->items[index];
	}
	ListIterator<T>& operator++() {
		index++;
		return *this;
	}
};

#endif // List_HPP
