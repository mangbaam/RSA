/*
// d�� ũ�Ⱑ unsigned long long�� �������� ū ���� �Ǹ� �� ����
// �߱����� ������ ���� ����
// ū �Ҽ� ���ϱ� -> prime[32]
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
	// p, q ���ϴ� ���� ���� �߰� ����
	// �� �Ҽ��� ũ��� 1024��Ʈ �̻��� �ǰ��Ѵ�.

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

	// e ���ϴ� ����
	// ���� ��ȣȭ�� ���ؼ� e�� ������ ����.
	// ���� ����ϴ� e = 3(11b), 17(10001b), 65537(10000000000000001b)
	// ��� �Ȱ��� e�� ����ص� d�� e�� �ƴ� p, q�� �����ϹǷ� ������.
	// �׷��� ���� e�� ����ϸ� d�� �ſ� Ŀ�� ���̴� -> CRT �˰��� ���
	ull e = 0;
	ull d = 0;
	do {
		e = 0;
		d = 0;
		while (!e) {
			srand((ull)time(NULL));	// ���� ���̺� ����
			ull randVal = rand() % largePlus(pN, "2", 10);

			if (randVal < pN) {
				e = randVal;

				// e�� pi(N)�� ���μ����� �˻�
				if (gcd(e, pN) != 1)
					e = 0;
			}
		}

		// d ���ϴ� ����
		// d*e = mod pi(N)
		
		do {
			d = getScretKey(e, pN);
		} while (d <= 1);

	} while (e == d || d > 1844674407370);

	cout << "e\t: " << e << endl;
	cout << "d\t: " << d << endl;


	cout << endl << endl;

	cout << "����Ű : (e, N) = (" << e << ", " << N << ")" << endl;
	cout << "����Ű : (d, N) = (" << d << ", " << N << ")" << endl;

	// ���� ũ��� N ���� �۾ƾ� �Ѵ�. N�� ũ��� ����� Ŀ���Ѵ� (2048��Ʈ ����) - �μ������� ������� ����
	// M�� �ɰ��� ����� �ִ�.
	ull msg = MSG;
	cout << "�Էµ� ��: " << msg << endl;
	// ���� 6���� �ɰ������� ��ȣ���� 6���� �ɰ����� ���´�. (��� ��ȣ)
	ull M = msg;
	// long long C = expo(M, e, N);
	// e�� d�� Ŀ���� �߱����� ������ ������ �ӵ��� ����ų �� �ִ�.
	ull C = SNM(M, e, N);
	cout << "cipher text = " << C << endl;

	M = SNM(C, d, N);
	cout << "plain text = " << M << endl;

}
