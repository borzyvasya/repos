#include "Array.h"

void Array::init(double* pa, int m, int n) {
	int i, j;
	size = m * n;

	p = new double[size];
	assert(p != 0);

	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j)
			p[i * n + j - 1] = (pa != 0) ? pa[i * n + j - 1] : 0;
		}
	}

Array::Array() {
	init(0, 0, 0);
}

Array::Array(int m) {
	if (m < 0) {
		cerr << "Illegal size of vector" << endl;;
		exit(EXIT_FAILURE);
	}

	init(0, m, 1);
}

Array::Array(int m, int n) {
	if (m < 0 || n < 0) {
		cerr << "\nIllegal size of matrix" << endl;
		exit(EXIT_FAILURE);
	}

	init(0, m, n);
}

Array::~Array() {
	delete[] p;
}
