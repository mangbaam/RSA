/*
// d의 크기가 unsigned long long의 범위보다 큰 수가 되면 평문 깨짐
// 중국인의 나머지 정리 구현
// 큰 소수 구하기 -> prime[32]
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <Windows.h>
#include "EEA.h"
#include "fastExponentiation.h"
#include "largeOP.h"
#include "primeGenerator.h"

#define MSG 123;

using namespace std;
using ull = unsigned long long;


int main() {
	// p, q 구하는 로직 추후 추가 예정
	// 두 소수의 크기는 1024비트 이상을 권고한다.

	/*ull p = primeGeneration(700000000,800000000);
	Sleep(1000);
	ull q = primeGeneration(600000000, 700000000);*/
	string p = "700022731", q = "600023051";
	string p_1 = "700022730", q_1 = "600023051";
	string N, pN;
	N = largeProduct(p, q, 10);
	pN = largeProduct(p_1, q_1, 10);
	
	cout << "p\t: " << p << endl;
	cout << "q\t: " << q << endl;
	cout << "N\t: " << N << endl;
	cout << "pi(N)\t: " << pN << endl;

	// e 구하는 로직
	// 빠른 암호화를 위해서 e는 작으면 좋다.
	// 자주 사용하는 e = 3(11b), 17(10001b), 65537(10000000000000001b)
	// 모두 똑같은 e를 사용해도 d는 e가 아닌 p, q에 의존하므로 괜찮다.
	// 그러나 작은 e를 사용하면 d는 매우 커질 것이다 -> CRT 알고리즘 사용
	ull e = 0;
	ull d = 0;
	do {
		e = 0;
		d = 0;
		while (!e) {
			srand((ull)time(NULL));	// 랜덤 테이블 형성
			ull randVal = rand() % largePlus(pN, "2", 10);

			if (randVal < pN) {
				e = randVal;

				// e와 pi(N)이 서로소인지 검사
				if (gcd(e, pN) != 1)
					e = 0;
			}
		}

		// d 구하는 로직
		// d*e = mod pi(N)
		
		do {
			d = getScretKey(e, pN);
		} while (d <= 1);

	} while (e == d || d > 1844674407370);

	cout << "e\t: " << e << endl;
	cout << "d\t: " << d << endl;


	cout << endl << endl;

	cout << "공개키 : (e, N) = (" << e << ", " << N << ")" << endl;
	cout << "개인키 : (d, N) = (" << d << ", " << N << ")" << endl;

	// 평문의 크기는 N 보다 작아야 한다. N의 크기는 충분히 커야한다 (2048비트 정도) - 인수분해의 어려움을 위해
	// M을 쪼개는 방법이 있다.
	ull msg = MSG;
	cout << "입력된 평문: " << msg << endl;
	// 평문이 6개로 쪼개졌으면 암호문도 6개로 쪼개져서 나온다. (블록 암호)
	ull M = msg;
	// long long C = expo(M, e, N);
	// e나 d가 커지면 중국인의 나머지 정리로 속도를 향상시킬 수 있다.
	ull C = SNM(M, e, N);
	cout << "cipher text = " << C << endl;

	M = SNM(C, d, N);
	cout << "plain text = " << M << endl;

}
