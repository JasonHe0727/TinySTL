#ifndef List_HPP
#define List_HPP

#include <memory>
#include <limits>
#include <initializer_list>

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
		Ensure();
		items[count] = item;
		count++;
	}

	inline int Count() const {
		return count;
	}

	inline T& operator[](int index) {
		return items[index];
	}

	inline const T& operator[](int index) const {
		return items[index];
	}

private:
	void Ensure() {
		if(count == capacity) {
			if(capacity == 0) {
				capacity = 4;
			} else if(capacity >= std::numeric_limits<int>::max() / 2) {
				capacity = std::numeric_limits<int>::max();
			} else {
				capacity = capacity * 2;
			}
			T* newItems = allocator.allocate(capacity);
			for(int i = 0; i < count; i++) {
				newItems[i] = items[i];
			}
			if(items) {
				allocator.deallocate(items, count);
			}
			items = newItems;
		}
	}
};


#endif // List_HPP
