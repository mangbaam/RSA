#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include "fastExponentiation.h"
using namespace std;
using ull = unsigned long long;

vector<ull> alist;

/***** �з�-��� �׽�Ʈ *****/
// �ռ����̸� return false
// probabley prime �̸� return true
// d�� d * 2^r = n - 1 (r >= 1) �� �����ϴ� Ȧ��
bool millerRabin(ull n, ull d, ull a) {
	// tmp�� 1�̰ų� n - 1�̸� return true
	ull tmp = SNM(a, d, n);
	if (tmp == n - 1 || tmp == 1) {
		return true;
	}

	// r - 1ȸ �ݺ�
	// 1) x = (x * x) mod n
	// 2) if (x == 1) return false
	// 3) if (x == n-1) return true
	while (d != n - 1) {
		tmp = (tmp * tmp) % n;
		d *= 2;

		if (tmp == 1) return false;
		if (tmp == n - 1) return true;
	}

	return false;
}

// count�� ���� ũ�� ��Ȯ�� �ö�
bool isPrime(ull n, int count = 10) {
	// n < 3 �� ��� ó��
	if (n <= 1 || n == 4)	return false;
	if (n <= 3) return true;

	// n �� ¦���̸� return false
	if (!n % 2) return false;

	// d * 2^r = n - 1 �� �����ϴ� d�� r�� ã�´�.
	// d�� Ȧ��, r > 0
	int d = n - 1;
	while (!d % 2)
		d /= 2;
	
	// a ���� -> ��Ű ����
	if (n < 1373653)
		alist = { 2, 3 };
	else if (n < 9080191)
		alist = { 31, 73 };
	else if (n < 4759123141)
		alist = { 2, 7, 61 };
	else
		alist = { 2, 3, 5, 7, 11 };

	// �з�-��� �׽�Ʈ�� �Ҽ��� Ȯ��
	for (int i = 0; i < count; i++) {
		for (ull a : alist) {
			if (!millerRabin(n, d, a))
				return false;
		}
	}
	// ��� �׽�Ʈ ����ϸ� �Ҽ���� ����
	return true;
}

// �Ҽ� ���� ����
ull primeGeneration(ull start = 101, ull end = 997) {
	ull tPrime = 2;
	 do {
		srand((unsigned)time(NULL));	// ���� ���̺� ����
		tPrime = rand() % (end - start) + start;
	 } while (isPrime(tPrime) == false);
	return tPrime;
}