#ifndef STACK_HPP
#define STACK_HPP
#include <memory>
#include <limits>

template <typename T>
class Stack {
private:
	int count;
	int capacity;
	T* items;
	std::allocator<T> allocator;
public:
	Stack(): count{0}, capacity{0}, items{nullptr} {
	}

	~Stack() {
		if(items) {
			allocator.deallocate(items, capacity);
		}
	}

	void Push(const T& item) {
		if(count == capacity) {
			if(capacity == 0) {
				items = allocator.allocate(4);
				capacity = 4;
			} else {
				if(capacity >= std::numeric_limits<int>::max() / 2) {
					Resize(std::numeric_limits<int>::max());
				} else {
					Resize(capacity);
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

	inline T& Top() {
		return items[count - 1];
	}

	const T& Top() const {
		return items[count - 1];
	}

	inline bool IsEmpty() {
		return count == 0;
	}

	inline int Size() {
		return count;
	}
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

#endif // STACK_HPP
