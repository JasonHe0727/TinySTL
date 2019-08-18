#ifndef List_HPP
#define List_HPP

#include <memory>
#include <limits>
#include <initializer_list>

template <typename T>
class List {
private:
	int count; // the count of elements
	int realLength; // the length of the array
	T* items;
	std::allocator<T> allocator;
public:
	List(): count{0}, realLength{0}, items{nullptr} {
	}

	List(std::initializer_list<T> list) {
		count = static_cast<int>(list.size());
		realLength = count;
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
		if(count == realLength) {
			if(realLength == 0) {
				realLength = 4;
			} else if(realLength >= std::numeric_limits<int>::max() / 2) {
				realLength = std::numeric_limits<int>::max();
			} else {
				realLength = realLength * 2;
			}
			T* newItems = allocator.allocate(realLength);
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
