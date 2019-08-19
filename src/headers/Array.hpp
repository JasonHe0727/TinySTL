#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>

template <typename T>
class Array {
private:
	int length;
	std::allocator<T> allocator;
	T* items;
public:
	Array(): length{0}, items{nullptr} {
	}

	Array(int length): length{length}, items{allocator.allocate(length)} {
	}

	Array(const Array<T>& other) {
		Copy(other);
	}

	Array<T>& operator=(const Array<T>& other) {
		Copy(other);
		return *this;
	}

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
		

	inline T& operator[](int index) {
		return items[index];
	}

	inline const T& operator[](int index) const {
		return items[index];
	}

	inline int Length() const {
		return length;
	}

	~Array() {
		if(items) {
			allocator.deallocate(items, length);
		}
	}

private:
	void Copy(const Array<T>& other) {
		length = other.length;
		items = allocator.allocate(length);
		for(int i = 0; i < other.length; i++) {
			items[i] = other.items[i];
		}
	}
};

#endif // ARRAY_HPP
