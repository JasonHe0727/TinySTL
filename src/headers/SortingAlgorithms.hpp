#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP
#include <algorithm>

class Insertion {
public:
	template <typename TCollection>
	static void Sort(TCollection& items) {
		int N = items.Size();
		for(int i = 1; i < N; i++) {
			for(int j = i; j > 0 && (items[j] < items[j - 1]); j--) {
				std::swap(items[j], items[j - 1]);
			}
		}
	}
};

#endif // SORTING_ALGORITHMS_HPP
