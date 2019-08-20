#include "StringAlgorithms.hpp"

void LSD::sort(Array<String>& array, int width) {
	int N = array.Length();
	int R = 256;
	Array<String> aux(N);

	Array<int> count(R + 1);
	for(int d = width - 1; d >= 0; d--) {
		for(int i = 0; i < count.Length(); i++) {
			count[i] = 0;
		}

		for(int i = 0; i < N; i++) {
			count[a[i][d] + 1]++;
		}

		for(int r = 0; r < R; r++) {
			count[r + 1] = count[r + 1] + count[r];
		}

		for(int i = 0; i < N; i++) {
			aux[count[array[i][d]]] = array[i];
			count[array[i][d]]++;
		}

		for(int i = 0; i < N; i++) {
			a[i] = aux[i];
		}
	}
}
