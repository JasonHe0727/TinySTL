#include "StringAlgorithms.hpp"
#include <algorithm>

void LSD::Sort(Array<String>& array, int width, int radix) {
	int N = array.Length();
	Array<String> aux(N);

	Array<int> count(radix + 1);
	for(int d = width - 1; d >= 0; d--) {
		for(int i = 0; i < count.Length(); i++) {
			count[i] = 0;
		}

		for(int i = 0; i < N; i++) {
			count[array[i][d] + 1]++;
		}

		for(int r = 0; r < radix; r++) {
			count[r + 1] = count[r + 1] + count[r];
		}

		for(int i = 0; i < N; i++) {
			aux[count[array[i][d]]] = array[i];
			count[array[i][d]]++;
		}

		for(int i = 0; i < N; i++) {
			array[i] = aux[i];
		}
	}
}

void MSD::Sort(Array<String>& array, int radix) {
	int N = array.Size();
	Array<String> aux(N);
	Sort(array, 0, N - 1, 0, aux, radix);
}

int MSD::CharAt(const String& s, int width) {
	if(width < s.Size()) {
		return s[width];
	} else {
		return (-1);
	}
}

void MSD::Sort(Array<String>& array, int low, int high, int width, Array<String>& aux, int radix) {
	const int M = 15; // cutoff for small subarrays
	if(high <= low + M) {
		InsertionSort(array, low, high, width);
		return;
	} else {
		Array<int> count(radix + 2);
		for(int i = 0; i < count.Size(); i++) {
			count[i] = 0;
		}
		for(int i = low; i <= high; i++) {
			count[CharAt(array[i], width) + 2]++;
		}
		for(int r = 0; r < radix + 1; r++) {
			count[r + 1] = count[r + 1] + count[r];
		}
		for(int i = low; i <= high; i++) {
			aux[count[CharAt(array[i], width) + 1]] = array[i];
			count[CharAt(array[i], width) + 1]++;
		}
		for(int i = low; i <= high; i++) {
			array[i] = aux[i - low];
		}
		for(int r = 0; r < radix; r++) {
			Sort(array, low + count[r], low + count[r + 1] - 1, width + 1, aux, radix);
		}
	}
}

void MSD::InsertionSort(Array<String>& array, int low, int high, int width) {
	for(int i = low + 1; i < high; i++) {
		for(int j = i; j > 0 && (array[j][width] < array[j - 1][width]); j--) {
			std::swap(array[j], array[j - 1]);
		}
	}
}
