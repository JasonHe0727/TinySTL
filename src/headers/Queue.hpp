#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <memory>
#include <limits>

template <typename T>
class Queue {
private:
	int head;
	int tail;
	int count;
	int capacity;
	T* items;
	std::allocator<T> allocator;
public:
	Queue(): head{0}, tail{0}, count{0}, capacity{0}, items{nullptr} {
	}

	~Queue() {
		if(items) {
			allocator.deallocate(items, capacity);
		}
	}

	void Enqueue(const T& item) {
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
		items[tail] = item;
		tail = (tail + 1) % capacity;
		count++;
	}

	void Dequeue() {
		items[head] = T();
		head = (head + 1) % capacity;
		count--;
		if(count > 0 && count == capacity / 4) {
			Resize(capacity / 2);
		}
	}

	inline bool IsEmpty() const {
		return count == 0;
	}

	inline T& Top() {
		return items[head];
	}

	inline const T& Top() const {
		return items[head];
	}

	inline int Size() const {
		return count;
	}
private:
	void Resize(int maxSize) {
		T* array = allocator.allocate(maxSize);
		int n = count;
		int index = 0;
		while(n > 0) {
			array[index] = items[head];
			head = (head + 1) % capacity;
			index++;
			n--;
		}
		head = 0;
		tail = count;
		allocator.deallocate(items, capacity);
		items = array;
		capacity = maxSize;
	}
};

#endif // QUEUE_HPP
