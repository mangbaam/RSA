#include <iostream>
#include <string>
using namespace std;
using ull = unsigned long long;

// 매우 느린 방법
ull expo(ull  a, ull  b, ull n) {
	ull  result = 1;

	while (b > 0) {
		result = (result * a) % n;
		b--;
	}
	return result;
}

// 빠른 알고리즘
// text ^ key mod N
ull SNM(ull text, ull key, string N) {	// square-and-multiple algorithm
	ull r;
	int bin[64];
	int i;

	r = text;
	i = 0;

	// key를 2진수로 변경
	while (key > 0) {
		bin[i] = key % 2;
		key >>= 1;
		i++;
	}

	// 제곱 후 곱셈 알고리즘
	i--;
	while (i > 0) {
		r = (r * r) % N;
		if (bin[--i] == 1)
			r = (r * text) % N;
	}
	return r;
}