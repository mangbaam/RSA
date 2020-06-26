using ull = unsigned long long;

ull gcd(ull a, ull b) {
	ull r1 = a, r2 = b, r;
	while (r2) {
		r = r1 % r2;
		r1 = r2;
		r2 = r;
	}
	return r1;
}

// e와 pi(N) 입력 (순서 지켜서)
ull getScretKey(ull e, ull pN) {
	ull r1 = e, t1 = 1, t2 = 0;
	ull r, t, q;
	ull r2 = pN;
	while (r2) {
		q = r1 / r2;
		// gcd 계산
		r = r1 % r2;
		r1 = r2, r2 = r;

		// t 계산
		t = t1 - q * t2;
		t1 = t2, t2 = t;
	}
	t = t1;

	if (t < 0)
		t += pN;
	return t;
}

