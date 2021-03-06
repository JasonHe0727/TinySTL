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
			count[array[i][d].ToInt() + 1]++;
		}

		for(int r = 0; r < radix; r++) {
			count[r + 1] = count[r + 1] + count[r];
		}

		for(int i = 0; i < N; i++) {
			aux[count[array[i][d].ToInt()]] = array[i];
			count[array[i][d].ToInt()]++;
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
		return s[width].ToInt();
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
			int n = CharAt(array[i], width) + 1;
			aux[count[n]] = array[i];
			count[n]++;
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
	for(int i = low; i <= high; i++) {
		for(int j = i; j > low && Less(array[j], array[j - 1], width); j--) {
			std::swap(array[j], array[j - 1]);
		}
	}
}

bool MSD::Less(const String& v, const String& w, int width) {
	return v.Slice(width, v.Length()) < w.Slice(width, w.Length());
}

KMP::KMP(): pattern(), dfa() {
}

KMP::KMP(const String& pattern, int radix): pattern{pattern}, dfa(radix) {
	int M = pattern.Length();
	for(int i = 0; i < radix; i++) {
		dfa[i] = Array<int>(M);
		for(int j = 0; j < M; j++) {
			dfa[i][j] = 0;
		}
	}
	dfa[pattern[0].ToInt()][0] = 1;
	for(int X = 0, j = 1; j < M; j++) {
		for(int c = 0; c < radix; c++) {
			dfa[c][j] = dfa[c][X];
		}
		dfa[pattern[j].ToInt()][j] = j + 1;
		X = dfa[pattern[j].ToInt()][X];
	}
}

int KMP::Search(const String& text) const {
	int i = 0;
	int j = 0;
	int N = text.Length();
	int M = pattern.Length();
	for(; i < N and j < M; i++) {
		j = dfa[text[i].ToInt()][j];
	}
	if(j == M) {
		return i - M;
	} else {
		return N;
	}
}

BoyerMoore::BoyerMoore(): pattern{}, right{} {
}

BoyerMoore::BoyerMoore(const String& pattern, int radix)
	: pattern{pattern}, right(radix) {
	int M = pattern.Length();
	for(int c = 0; c < radix; c++) {
		right[c] = -1;
	}
	for(int j = 0; j < M; j++) {
		right[pattern[j].ToInt()] = j;
	}
}

int BoyerMoore::Search(const String& text) const {
	int N = text.Length();
	int M = pattern.Length();
	int skip = 0;
	for(int i = 0; i <= N - M; i = i + skip) {
		skip = 0;
		for (int j = M - 1; j >= 0; j--) {
			if(pattern[j] != text[i + j]) {
				skip = j - right[text[i + j].ToInt()];
				if(skip < 1) {
					skip = 1;
				}
				break;
			}
		}
		if(skip == 0) {
			return i;
		}
	}
	return N;
}

//RabinKarp::RabinKarp(const String pattern, int radix)
//	: pattern{pattern}, patternHash{0}, M{pattern.Length()}, Q{LongRandomPrime()}, RM{1} {
//	for(int i = 1; i <= M - 1; i++) {
//		RM = (R * RM) % Q;
//	}
//	patternHash = Hash(pattern, M);
//}
//
//bool RabinKarp::Check(int i) {
//	return true;
//}
//long RabinKarp::Hash(const String& key, int M) {
//}
//int RabinKarp::Search(const String& text) {
//	int N = text.Length();
//	long textHash = Hash(text, M);
//	if(patternHash == textHash) {
//		return 0;
//	}
//	for(int i = M; i < N; i++) {
//		textHash = (textHash + Q - RM * text[i - M].ToInt() % Q) % Q;
//		textHash = (textHash * R + text[i]) % Q;
//		if(patternHash == textHash) {
//			if(Check(i - M + 1)) {
//				return i - M + 1;
//			}
//		}
//	}
//	return N;
//}
