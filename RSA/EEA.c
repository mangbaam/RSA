#include <stdio.h>

int EEA(int a, int b) {
	int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	int r, s, t, q;
	while (r2) {
		q = r1 / r2;
		// gcd ���
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s ���
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t ���
		t = t1 - q * t2;
		t1 = t2, t2 = t;
	}
	r = r1, s = s1, t = t1;
	//printf("gcd(%d, %d) = %d, s = %d, t = %d \n", a, b, r, s, t);
	//printf("%d x %d + %d x %d = %d \n", a, s, b, t, r);

	if (r == 1) {
		if (t < 0) {
			t += a;
		}
		return t;
	}
	else return NULL;
}

