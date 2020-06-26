#include <iostream>
#include <string>
using namespace std;
using ull = unsigned long long;

// �ſ� ���� ���
ull expo(ull  a, ull  b, ull n) {
	ull  result = 1;

	while (b > 0) {
		result = (result * a) % n;
		b--;
	}
	return result;
}

// ���� �˰���
// text ^ key mod N
ull SNM(ull text, ull key, string N) {	// square-and-multiple algorithm
	ull r;
	int bin[64];
	int i;

	r = text;
	i = 0;

	// key�� 2������ ����
	while (key > 0) {
		bin[i] = key % 2;
		key >>= 1;
		i++;
	}

	// ���� �� ���� �˰���
	i--;
	while (i > 0) {
		r = (r * r) % N;
		if (bin[--i] == 1)
			r = (r * text) % N;
	}
	return r;
}