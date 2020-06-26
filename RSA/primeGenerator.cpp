#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include "fastExponentiation.h"
using namespace std;
using ull = unsigned long long;

vector<ull> alist;

/***** 밀러-라빈 테스트 *****/
// 합성수이면 return false
// probabley prime 이면 return true
// d는 d * 2^r = n - 1 (r >= 1) 을 만족하는 홀수
bool millerRabin(ull n, ull d, ull a) {
	// tmp가 1이거나 n - 1이면 return true
	ull tmp = SNM(a, d, n);
	if (tmp == n - 1 || tmp == 1) {
		return true;
	}

	// r - 1회 반복
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

// count의 수가 크면 정확도 올라감
bool isPrime(ull n, int count = 10) {
	// n < 3 인 경우 처리
	if (n <= 1 || n == 4)	return false;
	if (n <= 3) return true;

	// n 이 짝수이면 return false
	if (!n % 2) return false;

	// d * 2^r = n - 1 을 만족하는 d와 r을 찾는다.
	// d는 홀수, r > 0
	int d = n - 1;
	while (!d % 2)
		d /= 2;
	
	// a 결정 -> 위키 참고
	if (n < 1373653)
		alist = { 2, 3 };
	else if (n < 9080191)
		alist = { 31, 73 };
	else if (n < 4759123141)
		alist = { 2, 7, 61 };
	else
		alist = { 2, 3, 5, 7, 11 };

	// 밀러-라빈 테스트로 소수성 확인
	for (int i = 0; i < count; i++) {
		for (ull a : alist) {
			if (!millerRabin(n, d, a))
				return false;
		}
	}
	// 모든 테스트 통과하면 소수라고 판정
	return true;
}

// 소수 생성 범위
ull primeGeneration(ull start = 101, ull end = 997) {
	ull tPrime = 2;
	 do {
		srand((unsigned)time(NULL));	// 랜덤 테이블 형성
		tPrime = rand() % (end - start) + start;
	 } while (isPrime(tPrime) == false);
	return tPrime;
}