#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

// num1 x num2 (base = ����)
// multiple-precision multiplication
string largeProduct(string num1, string num2, int base = 2) {
	string x = num1;
	string y = num2;
	int x_len = x.length();
	int y_len = y.length();

	// ����
	int b = base;

	// x, y �迭 ���� �Ҵ�
	int* x_arr = new int[x_len];
	int* y_arr = new int[y_len];

	// x_arr, y_arr �ʱ�ȭ
	for (int i = 1; i <= x_len; i++)
		x_arr[i - 1] = x.at(x_len - i) - '0';	// char to int
	for (int i = 1; i <= y_len; i++)
		y_arr[i - 1] = y.at(y_len - i) - '0';	// char to int

	// n+1 : x�� ����
	// t+1 : y�� ����
	int n = x_len - 1;
	int t = y_len - 1;

	// �����(x �� y�� ��) w �迭 ���� �Ҵ�
	int* w = new int[x_len + y_len];

	int c = 0;	// carry
	int sum = 0;	// if sum = 23 then u = 2, v = 3
	int u, v;

	// w �ʱ�ȭ
	for (int i = 0; i <= n + t + 1; i++)
		w[i] = 0;

	// �� ���
	for (int i = 0; i <= t; i++) {
		c = 0;
		for (int j = 0; j <= n; j++) {
			sum = w[i + j] + x_arr[j] * y_arr[i] + c;
			w[i + j] = v = sum % b;	// ��
			c = u = sum / b;	// carry
		}
		w[i + n + 1] = u;
	}

	// w�� ����� �������� �ԷµǾ� �����Ƿ�
	// result�� �迭�� �ڿ������� ����
	string result = "";

	// ���� ����� len_x + len_y - 1 �� ���
	if (!w[n + t + 1]) {
		for (int i = n + t; i >= 0; i--)
			result += to_string(w[i]);
	}
	// ���� ����� len_x + len_y �� ���
	else {
		for (int i = n + t + 1; i >= 0; i--)
			result += to_string(w[i]);
	}
	
	delete[] x_arr, y_arr, w;

	return result;
}

// x + y (d����)
string largePlus(string x, string y, int d = 2) {
	int x_len = x.length();
	int y_len = y.length();

	// x_len�� y_len �� ū �� count�� ����
	int count = x_len >= y_len ? x_len : y_len;

	int* x_arr = new int[count];
	int* y_arr = new int[count];
	int* w = new int[count + 1];

	// x_arr, y_arr, w �ʱ�ȭ
	for (int i = 0; i < count; i++) {
		w[i] = 0;
		x_arr[i] = 0;
		y_arr[i] = 0;
	}
	w[count] = 0;
	
	// x_arr, y_arr �� x, y �� �������� ����
	for (int i = 1; i <= x_len; i++)
		x_arr[i - 1] = x.at(x_len - i) - '0';	// char to int
	for (int i = 1; i <= y_len; i++)
		y_arr[i - 1] = y.at(y_len - i) - '0';	// char to int

	int c = 0, sum = 0;
	int u, v;

	for (int i = 0; i < count; i++) {
		sum = x_arr[i] + y_arr[i] + c;
		c = u = sum / d;
		w[i] = v = sum % d;
	}
	w[count] = c;

	string result;
	// ���� ����� len_x + len_y - 1 �� ���
	if (!w[count]) {
		for (int i = count - 1; i >= 0; i--)
			result += to_string(w[i]);
	}
	// ���� ����� len_x + len_y �� ���
	else {
		for (int i = count; i >= 0; i--)
			result += to_string(w[i]);
	}

	delete[] x_arr, y_arr, w;

	return result;
}

// x - y (d����)
string largeMinus(string x, string y, int d = 2) {
	int x_len = x.length();
	int y_len = y.length();
	int type = 0;
	// ũ�� ��
	// x > y : 0, x < y : 1
	if (x_len > y_len)
		type = 0;
	else if (y_len > x_len)
		type = 1;
	else if (x_len == y_len) {
		for (int i = 0; i < x_len; i++) {
			if (x[i] > y[i]) {
				type = 0;
				break;
			}
			else if (y[i] > x[i]) {
				type = 1;
				break;
			}
			else
				return "0";
		}
	}

	// x_len�� y_len �� ū �� count�� ����
	int count = x_len >= y_len ? x_len : y_len;

	int* num1 = new int[count];
	int* num2 = new int[count];
	int* w = new int[count];

	// x_arr, y_arr, w �ʱ�ȭ
	for (int i = 0; i < count; i++) {
		w[i] = 0;
		num1[i] = 0;
		num2[i] = 0;
	}

	// num1, num2�� x, y �� �������� ���� (ū ���� num1)
	if (type == 0) {
		for (int i = 1; i <= x_len; i++)
			num1[i - 1] = x.at(x_len - i) - '0';	// char to int
		for (int j = 1; j <= y_len; j++)
			num2[j - 1] = y.at(y_len - j) - '0';	// char to int
	}
	else if (type == 1) {
		for (int i = 1; i <= x_len; i++)
			num2[i - 1] = x.at(x_len - i) - '0';	// char to int
		for (int j = 1; j <= y_len; j++)
			num1[j - 1] = y.at(y_len - j) - '0';	// char to int
	}

	int sub;
	for (int i = 0; i < count - 1; i++) {
		sub = num1[i] - num2[i];
		if (sub < 0) {
			num1[i + 1] -= num1[i + 1];
			sub += d;
		}
		w[i] = sub;
	}
	w[count - 1] = num1[count - 1];

	string result;
	for (int i = count - 1; i >= 0; i--) {
		result += to_string(w[i]);
	}

	// 0 ����
	int i = 0;
	while (result[i] == '0' or i < count) {
		result.erase(0, 1);
		i++;
	}
	// - ���̱�
	if (type == 1)
		result.insert(0, "-");

	delete[] num1, num2, w;

	return result;
}

// num mod N
string largeMod(string num, string N, int d = 2) {
	int num_len = num.length();
	int N_len = N.length();

	int* num_arr = new int[num_len];
	int* N_arr = new int[N_len];

	string result;
	while (true) {
		result = largeMinus(num, N, d);
		if (result[0] == '-')
			break;
	}
	result = largePlus(result, N, d);

	delete[] num_arr, N_arr;
}