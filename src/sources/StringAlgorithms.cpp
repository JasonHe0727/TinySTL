#include "StringAlgorithms.hpp"

void LSD::sort(Array<String>& array, int width, int radix) {
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
